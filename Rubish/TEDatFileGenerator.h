#ifndef TEDATFILEGENERATOR_H
#define TEDATFILEGENERATOR_H

#include <fstream>
#include <string>
#include <boost/filesystem.hpp>

namespace TE
{
	namespace Resources
	{
		class DatFileGenerator
		{
		private:
			struct TOCFile
			{
				std::string fullpath;
				std::string filename;
				uintmax_t filesize;
			};

			struct TOCDirectory
			{
				std::string relativepath;
				std::vector<TOCDirectory> m_subDirs;
				std::vector<TOCFile> m_files;
			};

			struct Header
			{
				TOCDirectory rootFolder;
			};
		public:
			void Generate(const std::string& folderpath, const std::string& saveFilename);
		private:
			TOCDirectory RecurseSetupStructs(int &rFileCount, boost::filesystem::path& path, const std::string& relativePath);
			void WriteHeader(int fileCount, const Header& header);
			void RecurseWriteIndex(const TOCDirectory& rDirectory);
			void RecurseWriteFiles( const TOCDirectory& rDirectory );

			std::ofstream m_outFile;
		};
	}
}

#endif
