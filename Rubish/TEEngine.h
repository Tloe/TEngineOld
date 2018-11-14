#ifndef TEENGINE_H
#define TEENGINE_H

#include <TEDatFile.h>
#include <TERenderer.h>

#if TE_WINDOWS
#include <TEPlatformContextWin.h>
#elif TE_LINUX
#include <TEPlatformContextLinux.h>
#endif

namespace TE
{
	class Engine
	{
	public:
		Engine(const Context::PlatformContextPtr& platformContext, const std::string& datFilename = "");
		Engine(const std::string& datFilename = "" );
		
		void Init();
		void Cleanup();
		void OpenDatFile(const std::string& datFilename);

		Render::RendererPtr& GetRenderer();
		FileLoading::DatFile& GetDatFile();
	private:
		FileLoading::DatFile m_datFile;
		Render::RendererPtr m_renderer;
	};

	typedef std::shared_ptr<Engine> EnginePtr;
}

#endif