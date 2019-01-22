#ifndef DATFILEMANAGERWIDGET_H
#define DATFILEMANAGERWIDGET_H

#include <QtGui>
#include <DatFileModel.h>
#include "TEDatFile.h"

class DatFileWidget : public QWidget
{
	Q_OBJECT
public:
	DatFileWidget(QWidget * parent);
	~DatFileWidget();
private slots:
	void OpenFile();
	void SetResourceFolder();
	void NewFolder();
	void AddFile();
	void Delete();
private:
	QMenuBar* m_menu;
	QMenu* m_fileMenu;
	QAction* m_openFileAction;
	QAction* m_setResourceFolderAction;
	QAction* m_closeAction;

	QFileSystemModel* m_fileModel;
	QTreeView* m_fileBrowser;
	
	DatFileModel* m_datFileModel;
	QListView* m_datFileBrowser;
	QLineEdit* m_datFilePathLineEdit;

	QPushButton* m_addFileButton;
	QPushButton* m_deleteButton;
	QPushButton* m_newFolderButton;

	QMessageBox m_msgBox;
};

#endif