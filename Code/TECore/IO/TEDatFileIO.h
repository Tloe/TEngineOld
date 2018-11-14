#ifndef TEDATFILEIO_H
#define TEDATFILEIO_H

#include "TEFileIO.h"
#include "TEDatFile.h"

namespace TE
{
	namespace IO
	{
		class DatFileIO : public FileIO
		{
		public:
			DatFileIO(const std::string& datFilePath);
			void LoadFile( const std::string& filePath, std::vector<U8>& data );
			void LoadFile( I32 fileHash, std::vector<U8>& data );
			void SaveFile( const std::string& filePath, const std::vector<U8>& data );
			void SaveFile( I32 fileHash, const std::vector<U8>& data );
			IO::DatFile& GetDatFile();
			bool SupportsHash();
		private:
			std::string m_datFilePath;
			IO::DatFile m_datFile;
		};
	}
}

#endif