#include <TEImage.h>

TE::Images::Image::Image(const std::string& filename)

{
	
}

TE::Images::Image::~Image()
{

}

uint8_t* TE::Images::Image::GetDataPtr()
{
	return &GetData()[0];
}

