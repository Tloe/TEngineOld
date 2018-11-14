/*	This file is only inluded in the window file if we want a windows opengl context.
 *	Controlled by the TEWINDOWS define
 */

#ifndef TECONTEXTWINOPENGL_H
#define TECONTEXTWINOPENGL_H

#include <TEWindowWin.h>

namespace TE
{
	//Forward declarations
	namespace Render { struct APIContext; }
	class Window;
	//End forward declarations

	namespace Context
	{
		class APIPlatformWindow : public WindowWin
		{
		public:
			APIPlatformWindow();
			~APIPlatformWindow();
			void Init(Render::APIContext& apiContext, Window& window);
			void Cleanup(Render::APIContext& apiContext);
			void BeginFrame();
			void EndFrame();
			Window& GetWindowRef();
		private:
			HDC			m_hdc;
			HGLRC		m_hrc;
		};
	}
}

#endif
