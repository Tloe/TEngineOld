#include <TETexture.h>
#include "TEFileIO.h"
#include "TEImage.h"
#include "TEFile.h"
#include "TEImagePNG.h"

TE::Render::Texture::Texture( const std::string& filePath )
	:
	Resource(filePath)
{

}

TE::Render::Texture::Texture( const Texture&& other )
	:
	Resource(other.GetFilePath()),
	m_image(std::move(other.m_image))
{
	
}

TE::Render::Texture::~Texture()
{

}

TE::Render::Texture& TE::Render::Texture::operator=( const Texture& rhs )
{
	m_image = std::move(rhs.m_image);

	return *this;
}

void TE::Render::Texture::Load( IO::FileIO& fileIO )
{
	std::string fileExtention = IO::FileExtentionFromPath(GetFilePath());

	if (fileExtention == "png")
	{
		m_image.reset(new Images::ImagePng);
		m_image->Load(fileIO, GetFilePath());
	}
}

TE::Images::Image& TE::Render::Texture::GetImage()
{
	return *m_image;
}

void TE::Render::Texture::Prepare()
{
	m_image->Prepare();
}

bool TE::Render::Texture::IsLoaded() const
{
	return m_image->IsLoaded();
}

void TE::Render::Texture::Unload()
{

}
