#ifndef TEDATFILEMANIPULATOR_H
#define TEDATFILEMANIPULATOR_H
#include <string>
#include <vector>
#include <utility>

namespace TE
{
	namespace Resources
	{
		class DatFileManipulator
		{
			std::string m_datFilename;
			void WriteIndex( std::ofstream& filestr, std::vector<std::pair<std::string, int> >& fileIndex );
			void ReadFileContent( const std::string& filesystempath, std::vector<char>& data );
		public:
			DatFileManipulator(const std::string& filename);

			void AddFile(const std::string& filesystempath, const std::string& datfilepath);
			void RemoveFile(const std::string& filepath);
			
		};
	}
}

#endif