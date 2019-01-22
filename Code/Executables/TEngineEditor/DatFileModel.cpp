#include <DatFileModel.h>
#include <assert.h>
#include <iostream>


DatFileModel::DatFileModel( QObject *parent )
	:
	QAbstractListModel(parent),
	m_path("/"),
	m_fetchedCount(0),
	m_entryCount(0)
{
	m_iconProvider = new0 QFileIconProvider;
}

QVariant DatFileModel::data( const QModelIndex &index, I32 role ) const
{
	if(index.isValid())
	{
		if (index.row() >= m_entryCount || index.row() < 0)
			return QVariant();

		if (role == Qt::DisplayRole)
		{
			if (index.row() == 0 && !m_isRootPath)
			{
				return QVariant(QString("."));
			}
			else if (index.row() == 1 && !m_isRootPath)
			{
				return QVariant(QString(".."));
			}
			else
			{
				I32 relativeIndex = index.row() - (m_isRootPath? 0: 2);
				return QVariant(QString(m_pathFoldersAndFiles[relativeIndex].c_str()));
			}
		}
		else if (role == Qt::DecorationRole)
		{
			if (index.row() == 0 && !m_isRootPath)
			{
				return m_iconProvider->icon(QFileIconProvider::Folder);
			}
			else if (index.row() == 1 && !m_isRootPath)
			{
				return m_iconProvider->icon(QFileIconProvider::Folder);
			}
			else
			{
				I32 relativeIndex = index.row() - (m_isRootPath? 0 : +2);
				if(relativeIndex < m_filesOffset)
				{
					return m_iconProvider->icon(QFileIconProvider::Folder);
				}
				else
				{
					return m_iconProvider->icon(QFileIconProvider::File);
				}
			}
		}
	}

	return QVariant();
}

I32 DatFileModel::rowCount( const QModelIndex &parent /*= QModelIndex()*/ ) const
{
	return m_fetchedCount;
}

void DatFileModel::setDirPath( const TE::IO::DatPath& datPath )
{
	m_path = datPath;
	m_pathFoldersAndFiles.clear();
	m_filesOffset = m_datFile.GetFolderContent(m_path, m_pathFoldersAndFiles);
	m_entryCount = m_pathFoldersAndFiles.size();
	
	if (m_path.IsRoot())
	{
		m_isRootPath = true;
	}
	else 
	{
		m_entryCount += 2;
		m_isRootPath = false;
	}
	
	m_fetchedCount = 0;
	reset();
	emit PathChanged(QString(datPath.GetFullPath().c_str()));
}

bool DatFileModel::canFetchMore( const QModelIndex &parent ) const
{
	if (m_fetchedCount < m_entryCount)
		return true;
	else
		return false;
}

void DatFileModel::fetchMore( const QModelIndex &parent )
{
	I32 itemsToFetch = m_entryCount - m_fetchedCount;
	assert(itemsToFetch < 1000 && "Cannot fetch more than 1000"); //Change limit?

	beginInsertRows(QModelIndex(), m_fetchedCount, m_fetchedCount+itemsToFetch);

	m_fetchedCount += itemsToFetch;

	endInsertRows();

	emit numberPopulated(itemsToFetch);
}

void DatFileModel::doubleClicked( const QModelIndex &index )
{
	if(index.row() == 0 && !m_isRootPath)
	{
		setDirPath(m_path);
	}
	else if (index.row() == 1 && !m_isRootPath)
	{
		m_path.CdUp();
		setDirPath(m_path);
	}
	else
	{
		I32 relativeIndex = index.row() - (m_isRootPath? 0 : 2);
		std::string selectedElement = m_pathFoldersAndFiles[relativeIndex];
		if(relativeIndex < m_filesOffset)
		{
			m_path.Cd(selectedElement);
			setDirPath(m_path);
		}
	}
}

bool DatFileModel::AddFile( const std::string& filePath )
{
	if (filePath.size() == 3 && filePath[1] == ':') return false; //Windows drive

	size_t substrPos = filePath.find_last_of('/');
	TE::IO::DatPath datPath(m_path.GetFullPath() + filePath.substr(substrPos+1));
        if(datPath.IsValid() && m_datFile.AddFile(filePath, datPath))
	{
		setDirPath(m_path);
		return true;
	}

	return false;
}

bool DatFileModel::AddFile( std::vector<U8>& data, const TE::IO::DatPath& relativePath )
{
	if (m_datFile.AddFile(data, relativePath))
	{
		setDirPath(m_path);
		return true;
	}

	return false;
}

bool DatFileModel::NewFolder( const std::string& relativePath )
{
	if(m_datFile.NewFolder(TE::IO::DatPath(m_path.GetFullPath() + relativePath + '/')))
	{
		setDirPath(m_path);
		return true;
	}
	return false;
}

bool DatFileModel::DeletePath(const QModelIndex &index)
{
	if((!m_isRootPath &&
		(index.row() == 0 || index.row() == 1))	||
		m_pathFoldersAndFiles.empty() ||
		!index.isValid())
	{
		return false;
	}

	I32 relativeIndex = index.row() - (m_isRootPath? 0 : 2);
	std::string selectedElement = m_pathFoldersAndFiles[relativeIndex];
	if(relativeIndex < m_filesOffset)
	{
		selectedElement = m_path.GetFullPath() + selectedElement + '/';
	}
	else
	{
		selectedElement = m_path.GetFullPath() + selectedElement;
	}
	m_datFile.RemovePath(TE::IO::DatPath(selectedElement));

	setDirPath(m_path);

	return true;
}

bool DatFileModel::OpenDatFile( const std::string& datFilePath )
{
	if (m_datFile.OpenFile(datFilePath))
	{
		setDirPath(m_path);
		return true;
	}
	return false;
}
