#include <TETextureLoaderPNG.h>
#include <png.h>
#include <assert.h>
#include <iostream>




TE::Resources::TextureLoaderPNG::TextureLoaderPNG()
{

}


TE::Resources::TextureInfo TE::Resources::TextureLoaderPNG::LoadTexture( std::vector<uint8_t>& dataInOut ) const
{
	// Set here so it can be referenced in error code below. Used further down
	png_bytep* rowPtrs = NULL;
	char* data = NULL;
	
	//Check png file signature
	assert(png_check_sig(&dataInOut[0], SIGNATURE_LENGTH) && "PNG file expected");

	//Create needed structures
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0,0,0);
	if(!png_ptr)
	{
		std::clog << "png_ptr invalid." << std::endl;
		exit(1);
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		std::clog << "png info_ptr invalid." << std::endl;
		exit(1);
	}

	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr,NULL);
		exit(1);
	}

	//Error handling. PNG will jump here.
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		//An error occured, so clean up what we have allocated so far...
		png_destroy_read_struct(&png_ptr, &info_ptr,(png_infopp)0);
		if (rowPtrs != NULL) delete [] rowPtrs;
		if (data != NULL) delete [] data;

		std::clog << "ERROR: An error occured while reading PNG file";

		exit(1);
	}

	//Set custom read function
	PNGData datastruct;
	datastruct.data = static_cast<png_bytep>(&dataInOut[0]);
	datastruct.size = static_cast<png_uint_32>(dataInOut.size());
	png_set_read_fn(png_ptr, static_cast<png_voidp>(&datastruct), ReadDataResourceVector);

	//Read info
	png_read_info(png_ptr, info_ptr);
	png_uint_32 width = png_get_image_width(png_ptr, info_ptr);
	png_uint_32 height = png_get_image_height(png_ptr, info_ptr);
	png_uint_32 bitDepth = png_get_bit_depth(png_ptr, info_ptr);
	png_uint_32 channels   = png_get_channels(png_ptr, info_ptr);
	png_uint_32 color_type = png_get_color_type(png_ptr, info_ptr);

	//Change how the file is loaded if it has some invalid info
	switch(color_type)
	{
	case PNG_COLOR_TYPE_PALETTE:
		png_set_palette_to_rgb(png_ptr);
		channels = 3;
		break;
	case PNG_COLOR_TYPE_GRAY:
		if (bitDepth < 8) png_set_expand_gray_1_2_4_to_8(png_ptr);
		bitDepth = 8;
		break;
	}
	bool alphaAdded = false;
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
	{
		png_set_tRNS_to_alpha(png_ptr);
		channels+=1;
		alphaAdded = true;
	}
	if (bitDepth == 16)
	{
		png_set_strip_16(png_ptr);
	}

	//allocate space for storing data
	rowPtrs = new png_bytep[height];
	int dataSize = width * height * bitDepth * channels / 8;
	data = new char[dataSize];
	const unsigned int stride = width * bitDepth * channels / 8;

	for (size_t i = 0; i < height; i++)
	{
		png_uint_32 q = (height - i - 1) * stride;
		rowPtrs[i] = (png_bytep)data + q;
	}

	//Read actual image data
	png_read_image(png_ptr, rowPtrs);

	//Clean up
	delete[] (png_bytep)rowPtrs;
	png_destroy_read_struct(&png_ptr, &info_ptr,static_cast<png_infopp>(NULL));

	//Move data into resource data
	dataInOut.clear();
	dataInOut.insert(dataInOut.begin(), data, data+dataSize);

	//Setup texture info
	TextureInfo textureInfo;
	textureInfo.width = width;
	textureInfo.height = height;
	textureInfo.bitDepth = bitDepth;
	
	switch(color_type)
	{
	case PNG_COLOR_TYPE_PALETTE:
	case PNG_COLOR_TYPE_RGB:
	case PNG_COLOR_TYPE_GRAY:
		textureInfo.colorType = TextureInfo::COLORTYPE_RGB;
		break;
	case PNG_COLOR_TYPE_RGBA:
		textureInfo.colorType = TextureInfo::COLORTYPE_RGBA;
		break;
	default:
		std::clog << "Unsuported color_type" << std::endl;
	}

	if(alphaAdded)
	textureInfo.colorType = TextureInfo::COLORTYPE_RGBA;

	return textureInfo;
}
