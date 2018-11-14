#include <DatFileManagerWidget.h>
#include <QtGui>
#include <DatFileModel.h>
#include <TEDatPath.h>

DatFileWidget::DatFileWidget(QWidget * parent)
	:
	QWidget(parent)
{
	m_closeAction = new0 QAction(tr("&Close"), this);
	connect(m_closeAction, SIGNAL(triggered()), this, SLOT(close()));

	m_setResourceFolderAction = new0 QAction(tr("Set &resource folder"), this);
	connect(m_setResourceFolderAction, SIGNAL(triggered()), this, SLOT(SetResourceFolder()));
	
	m_openFileAction = new0 QAction(tr("&Open file"), this);
	connect(m_openFileAction, SIGNAL(triggered()), this, SLOT(OpenFile()));

	m_menu = new0 QMenuBar(this);
	m_fileMenu = m_menu->addMenu(tr("F&ile"));
	m_fileMenu->addSeparator();
	m_fileMenu->addAction(m_openFileAction);
	m_fileMenu->addAction(m_setResourceFolderAction);
	m_fileMenu->addSeparator();
	m_fileMenu->addAction(m_closeAction);

	m_fileModel = new0 QFileSystemModel;
	m_fileModel->setFilter(QDir::Filters( QDir::NoDotAndDotDot|QDir::Hidden|QDir::AllEntries|QDir::Dirs|QDir::AllDirs|QDir::Files|QDir::Drives|QDir::Hidden ) );
	m_fileModel->setRootPath(QDir::rootPath());
	
	m_fileBrowser = new0 QTreeView(this);
	m_fileBrowser->setModel(m_fileModel);
	m_fileBrowser->header()->hideSection(3);
	m_fileBrowser->header()->resizeSection(0, 250);
	m_fileBrowser->setMinimumSize(550, 450);
	m_fileBrowser->setSortingEnabled(true);

	m_addFileButton = new0 QPushButton(tr("Add file"));
	connect(m_addFileButton, SIGNAL(clicked()), this, SLOT(AddFile()));
	m_newFolderButton = new0 QPushButton(tr("New folder"));
	connect(m_newFolderButton, SIGNAL(clicked()), this, SLOT(NewFolder()));
	m_deleteButton = new0 QPushButton(tr("Delete"));
	connect(m_deleteButton, SIGNAL(clicked()), this, SLOT(Delete()));
	
	m_datFilePathLineEdit = new0 QLineEdit;
	m_datFilePathLineEdit->setReadOnly(true);
	m_datFilePathLineEdit->setEnabled(false);

	m_datFileModel = new0 DatFileModel(this);
	connect(m_datFileModel, SIGNAL(PathChanged(const QString&)), m_datFilePathLineEdit,SLOT(setText(const QString&)));
	//m_datFileModel->setDirPath(TE::IO::DatPath("/"));

	m_datFileBrowser = new0 QListView(this);
	m_datFileBrowser->setModel(m_datFileModel);
	m_datFileBrowser->setMinimumSize(350,450);
	//m_datFileBrowser->setSelectionMode(QAbstractItemView::ExtendedSelection); //Need to subclass QListView to use this
	connect(m_datFileBrowser, SIGNAL(doubleClicked(const QModelIndex &)), m_datFileModel, SLOT(doubleClicked(const QModelIndex &)));
	
	QGridLayout* layout = new0 QGridLayout;
	layout->setMenuBar(m_menu);
	layout->addWidget(m_fileBrowser, 0, 0,1,1);
	QVBoxLayout* buttonlayout = new0 QVBoxLayout;
	buttonlayout->addWidget(m_addFileButton);
	buttonlayout->addWidget(m_newFolderButton);
	buttonlayout->addWidget(m_deleteButton);
	layout->addLayout(buttonlayout,0,1,1,1, Qt::AlignTop);
	QVBoxLayout* datFilelayout = new0 QVBoxLayout;
	datFilelayout->addWidget(m_datFilePathLineEdit);
	datFilelayout->addWidget(m_datFileBrowser);
	layout->addLayout(datFilelayout, 0, 2,1,1);

	setLayout(layout);

	setWindowTitle(tr("Dat File Manager"));

	//DEBUGING
	QString dir = "D://testing";

	m_fileModel->setRootPath(dir);
	m_fileBrowser->setRootIndex(m_fileModel->index(dir));
	//END DEGUG
}

DatFileWidget::~DatFileWidget()
{

}

void DatFileWidget::NewFolder()
{
	bool ok;
	
	QString folderName = QInputDialog::getText(this,
											   tr("Enter new folder name"),
											   tr("Folder name:"),
											   QLineEdit::Normal,
											   QString(""),
											   &ok);
	
	if (ok && !folderName.isEmpty())
	{
		if(!m_datFileModel->NewFolder( folderName.toLocal8Bit().constData()))
		{
			m_msgBox.setText("Could not add new folder.");
			m_msgBox.exec();
		}
	}
}

void DatFileWidget::AddFile()
{
	QModelIndex index = m_fileBrowser->currentIndex();
	QFileInfo fileInfo = m_fileModel->filePath(index);
	
	if(fileInfo.isDir())
	{
		m_msgBox.setText("Cannot add folder paths");
		m_msgBox.exec();
	}
	else
	{
		if(!m_datFileModel->AddFile(fileInfo.filePath().toLocal8Bit().constData()))
		{
			m_msgBox.setText("Could not add file.");
			m_msgBox.exec();
		}
	}
}

void DatFileWidget::Delete()
{
	QModelIndex index = m_datFileBrowser->currentIndex();
	if(!m_datFileModel->DeletePath(index))
	{
		m_msgBox.setText("Could not delete path.");
		m_msgBox.exec();
	}
	m_datFileBrowser->setCurrentIndex(index);
}

void DatFileWidget::SetResourceFolder()
{
	QString dir = QFileDialog::getExistingDirectory(this, "Select resource folder");

	m_fileModel->setRootPath(dir);
	m_fileBrowser->setRootIndex(m_fileModel->index(dir));
}

void DatFileWidget::OpenFile()
{
	QString filePath = QFileDialog::getSaveFilePath(this,
													tr("Get file name"),
													"",
													tr("Dat files (*.dat)"),
													0,
													QFileDialog::DontConfirmOverwrite);
	if (filePath != "")
	{
		if(!m_datFileModel->OpenDatFile(filePath.toLocal8Bit().constData()))
		{
			m_msgBox.setText("Could not open dat file.");
			m_msgBox.exec();
		}
	}
}
