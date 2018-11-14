/*	This file is only inluded in the window file if we want a windows directx context.
 *	Controlled by the TEWINDOWS define
 */

#ifndef TECONTEXTWINDX11_H
#define TECONTEXTWINDX11_H

#include <TEWindowWin.h>
#include <TEReal.h>
#include <d3d11.h>
#include <memory>

namespace TE
{
	namespace Render { struct APIContext; }

	namespace Context
	{
		class APIPlatformWindow : public WindowWin
		{
		public:
			APIPlatformWindow();
			~APIPlatformWindow();
			
			virtual void Init(Render::APIContext& apiContext, Window& window);
			virtual void Cleanup(Render::APIContext& apiContext);
			virtual void BeginFrame();
			virtual void EndFrame();
		};

		typedef std::shared_ptr<Context::APIPlatformWindow> APIPlatformWindowPtr;
	}
}

#endif
