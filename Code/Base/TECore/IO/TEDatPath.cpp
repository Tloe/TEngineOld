#include <TEDatPath.h>
#include <assert.h>

std::string TE::IO::DatPath::m_validChars = "/._-";

TE::IO::DatPath::DatPath( const std::string& path )
	:m_path(path)
{

}

bool TE::IO::DatPath::IsValid() const
{
	bool valid = true;
	for (unsigned i = 0; i < m_path.size(); ++i)
	{
		if (!isalnum(m_path[i]) && m_validChars.find_first_of(m_path[i]) == std::string::npos)
		{
			valid = false;
		}
	}	

	return valid && m_path[0] == '/' && !m_path.empty();
}

bool TE::IO::DatPath::IsFile() const
{
	return m_path[m_path.size()-1] != '/';
}

bool TE::IO::DatPath::IsFolder() const
{
	return m_path[m_path.size()-1] == '/';
}

bool TE::IO::DatPath::IsRoot() const
{
	return m_path.size() == 1 && m_path[0] == '/';
}

const std::string& TE::IO::DatPath::GetFullPath() const
{
	return m_path;
}

bool TE::IO::DatPath::InSubPathOf( const DatPath& datPath )
{
	if (InSubPathOfRecursive(datPath))
	{
		std::string temp = datPath.GetFullPath() + GetFolderIn(datPath) + '/';
		if (m_path.size() <= temp.size())
		{
			return true;
		}
	}
	return false;
}

bool TE::IO::DatPath::InSubPathOfRecursive( const DatPath& datPath )
{
	if (m_path != datPath.GetFullPath() &&
		m_path.substr(0, datPath.GetFullPath().size()) == datPath.GetFullPath())
	{
		return true;
	}
	return false;
}

const std::string TE::IO::DatPath::GetFolderIn(const DatPath& relativeDatPath) const
{
	size_t relativeSize = relativeDatPath.GetFullPath().size();
	size_t endPathPos = m_path.find('/', relativeSize);
	return m_path.substr(relativeSize, endPathPos-relativeSize);
}

const std::string TE::IO::DatPath::GetFileOrFolder()
{
	if (m_path.size() == 1) return "";

	size_t lastSlashPos = m_path.find_last_of('/', m_path.size()-2);

	if (IsFile())
		return m_path.substr(lastSlashPos+1);
	else
		return m_path.substr(lastSlashPos+1, m_path.size()-lastSlashPos-2);

} 

void TE::IO::DatPath::CdUp()
{
	size_t substrPos = m_path.substr(0, m_path.size()-1).find_last_of('/');
	m_path = m_path.substr(0, substrPos+1);

	assert(IsValid());

}

void TE::IO::DatPath::Cd( const std::string& folder )
{
	m_path += folder + '/';

	assert(IsValid());
}
