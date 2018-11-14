#include <TEDatFileGenerator.h>
#include <iosfwd>
#include <sstream>
#include <iostream>

void TE::Resources::DatFileGenerator::Generate( const std::string& folderpath, const std::string& saveFilename )
{
	boost::filesystem::path rootPath(folderpath);
	if(!boost::filesystem::exists(rootPath) || !boost::filesystem::is_directory(rootPath))
		throw;

	Header header;
	int fileCount = 0;
	header.rootFolder = RecurseSetupStructs(fileCount, rootPath, "/");

	m_outFile.open(saveFilename, std::ios::binary | std::ios::out);

	m_outFile << fileCount << '\n';
	RecurseWriteIndex( header.rootFolder);
	
	RecurseWriteFiles(header.rootFolder);
	m_outFile.close();
}

TE::Resources::DatFileGenerator::TOCDirectory TE::Resources::DatFileGenerator::RecurseSetupStructs( int &rFileCount, boost::filesystem::path& path, const std::string& relativePath )
{
	TOCDirectory newDirectory;
	newDirectory.relativepath = relativePath;

	std::vector<boost::filesystem::path> paths;
	copy(boost::filesystem::directory_iterator(path), boost::filesystem::directory_iterator(), std::back_inserter(paths));
	std::sort(paths.begin(), paths.end());

	for (unsigned i = 0; i < paths.size(); ++i)
	{
		size_t found = paths[i].string().find_last_of("/\\");
		std::string endOfPath(paths[i].string().substr(found+1));
		if (boost::filesystem::is_directory(paths[i]))
		{
			newDirectory.m_subDirs.push_back(RecurseSetupStructs(rFileCount, paths[i], relativePath + endOfPath + "/"));
		}

		if (boost::filesystem::is_regular_file(paths[i]) &&
			endOfPath != "TEDatArchiver.exe" &&
			paths[i].extension().string() != ".dat")
		{
			std::cout << paths[i].string() << std::endl;
			TOCFile newFile;
			newFile.fullpath = paths[i].string();
			newFile.filename = endOfPath;
			newFile.filesize  = boost::filesystem::file_size(paths[i]);
			newDirectory.m_files.push_back(newFile);
		}
	}

	rFileCount += newDirectory.m_files.size();
	return newDirectory;
}

void TE::Resources::DatFileGenerator::RecurseWriteIndex( const TOCDirectory& rDir )
{
	for(unsigned i = 0; i < rDir.m_subDirs.size(); ++i)
	{
		RecurseWriteIndex(rDir.m_subDirs[i]);
	}

	for (unsigned i = 0; i < rDir.m_files.size(); ++i)
	{
		std::stringstream data;
		data << rDir.relativepath 
			<< rDir.m_files[i].filename 
			<< " " 
			<< rDir.m_files[i].filesize
			<< "\n";

		m_outFile.write(data.str().c_str(), data.str().size());
	}
}

void TE::Resources::DatFileGenerator::RecurseWriteFiles( const TOCDirectory& rDirectory )
{
	for(unsigned i = 0; i < rDirectory.m_subDirs.size(); ++i)
	{
		RecurseWriteFiles(rDirectory.m_subDirs[i]);
	}

	for (unsigned i = 0; i < rDirectory.m_files.size(); ++i)
	{
		std::ifstream inFilestream(rDirectory.m_files[i].fullpath, std::ios::binary | std::ios::in);
		
		inFilestream.seekg(0, std::ios::end);
		std::streampos length = inFilestream.tellg();
		inFilestream.seekg(0, std::ios::beg);
		
		std::vector<char> data(static_cast<int>(length));
		inFilestream.read(&data[0], length);
		
		m_outFile.write(&data[0], data.size());
	}
}
