#include "TEEngine.h"

TE::Engine::Engine( const Context::PlatformContextPtr& platformContext, const std::string& datFilename )
{
	if (datFilename != "")
	{
		OpenDatFile(datFilename);
	}

	m_renderer.reset(new Render::Renderer(platformContext, m_datFile));
}

TE::Engine::Engine( const std::string& datFilename )
{
	if (datFilename != "")
	{
		OpenDatFile(datFilename);
	}

	m_renderer.reset(new Render::Renderer(m_datFile));
}

void TE::Engine::Init()
{
	m_renderer->Init();
}

void TE::Engine::Cleanup()
{
	m_renderer->Cleanup();
}

void TE::Engine::OpenDatFile(const std::string& datFilename)
{
	m_datFile.Open(datFilename);
}


TE::Render::RendererPtr& TE::Engine::GetRenderer()
{
	return m_renderer;
}

TE::FileLoading::DatFile& TE::Engine::GetDatFile()
{
	return m_datFile;
}

