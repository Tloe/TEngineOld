#if TE_Linux
#   include <TEContextLinuxOpenGL.h>
#elif TE_WINDOWS
#   if TE_OPENGL
#       include <TEContextWinOpenGL.h>
#   elif TE_DX11
#       include <TEContextWinDX11.h>
#   endif
#endif
