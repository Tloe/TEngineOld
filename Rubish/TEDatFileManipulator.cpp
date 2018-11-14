#include <TEDatFileManipulator.h>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>
#include "TEDatFileReader.h"

TE::Resources::DatFileManipulator::DatFileManipulator( const std::string& filename )
	:
	m_datFilename(filename)
{

}

void TE::Resources::DatFileManipulator::WriteIndex( std::ofstream& filestr, std::vector<std::pair<std::string, int> >& fileIndex )
{
	int indexOffset = static_cast<int>(filestr.tellp());
	for (unsigned i = 0; i < fileIndex.size(); ++i)
	{
		std::stringstream data;
		data << fileIndex[i].first
			<< " " 
			<< fileIndex[i].second
			<< "\n";

		filestr.write(data.str().c_str(), data.str().size());
	}
	filestr.write(reinterpret_cast<char*>(&indexOffset), static_cast<int>(sizeof(int)));
	int numLines = fileIndex.size();
	filestr.write(reinterpret_cast<char*>(&numLines), static_cast<int>(sizeof(int)));
}

void TE::Resources::DatFileManipulator::RemoveFile( const std::string& filepath )
{
	std::fstream filestr(filepath, std::ios::binary | std::ios::in | std::ios::out);


}

void TE::Resources::DatFileManipulator::ReadFileContent( const std::string& filesystempath, std::vector<char>& data )
{
	std::ifstream inFilestream(filesystempath, std::ios::binary | std::ios::in);
	
	inFilestream.seekg(0, std::ios::end);
	std::streampos length = inFilestream.tellg();
	inFilestream.seekg(0, std::ios::beg);
	
	data.resize(static_cast<int>(length));
	inFilestream.read(&data[0], length);
	
	inFilestream.close();
}
