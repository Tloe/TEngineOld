#ifndef DATFILEMODEL_H
#define DATFILEMODEL_H

#include <QtGui>
#include <TEDatFile.h>
#include <stdint.h>
#include <TEDatPath.h>

class DatFileModel : public QAbstractListModel
{
	Q_OBJECT
	
	QFileIconProvider* m_iconProvider;
	I32 m_fetchedCount;
	I32 m_entryCount;
	TE::IO::DatFile m_datFile;
	TE::IO::DatPath m_path;
	bool m_isRootPath;
	std::vector<std::string> m_pathFoldersAndFiles;
	I32 m_filesOffset;
public:
	DatFileModel(QObject *parent);

	void setDirPath(const TE::IO::DatPath& datPath);
	QVariant data(const QModelIndex &index, I32 role) const;
	I32 rowCount(const QModelIndex &parent = QModelIndex()) const;

	bool OpenDatFile(const std::string& datFilePath);
	bool AddFile(const std::string& filePath);
	bool AddFile(std::vector<U8>& data, const TE::IO::DatPath& relativePath);
	bool NewFolder(const std::string& folderName);
	bool DeletePath(const QModelIndex &index);
signals:
	void numberPopulated(I32 number);
	void PathChanged(const QString& newPath);
public slots:
	void doubleClicked(const QModelIndex &index);
protected:
	bool canFetchMore(const QModelIndex &parent) const;
	void fetchMore(const QModelIndex &parent);
};

#endif