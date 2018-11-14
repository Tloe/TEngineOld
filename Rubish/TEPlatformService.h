#ifndef TEPLATFORMSERVICE_H
#define TEPLATFORMSERVICE_H

#include "TEService.h"
#include <string>

namespace TE
{
	//Forward declaration
	namespace IO { class FileIO; }
	//End forward declaration

	namespace Engine
	{
		class PlatformService : public Service
		{
		public:
			PlatformService(IO::FileIO& fileIO);

			IO::FileIO& GetFileIO();
		private:
			IO::FileIO& m_fileIO;
		};
	}
}

#endif