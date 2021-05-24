#include <ConvertMeshFormatWidget.h>
#include <TEDatFile.h>

ConvertMeshFormatWidget::ConvertMeshFormatWidget(QWidget *parent) : QWidget(parent) {
    setWindowTitle(tr("Mesh Converter"));

    m_openAction = new0 QAction(tr("&Open file"), this);
    connect(m_openAction, SIGNAL(triggered()), this, SLOT(OpenFile()));

    m_closeAction = new0 QAction(tr("&Close"), this);
    connect(m_closeAction, SIGNAL(triggered()), this, SLOT(close()));

    m_menu     = new0 QMenuBar(this);
    m_fileMenu = m_menu->addMenu(tr("F&ile"));
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_closeAction);

    m_meshList = new0 QListWidget(this);
    m_meshList->setFixedWidth(100);
    m_meshList->setSelectionMode(QAbstractItemView::SingleSelection);

    m_checkGroup = new0 QGroupBox;
    m_checkGroup->setTitle("Extract/Generate");

    m_obbCheck          = new0 QCheckBox("OBB");
    m_bsphereCheck      = new0 QCheckBox("Bounding Sphere");
    m_indexBufferCheck  = new0 QCheckBox("Index buffer");

    m_vertexBufferGroup = new0 QGroupBox;
    m_vertexBufferGroup->setTitle("Vertex buffer");

    m_verticesCheck      = new0 QCheckBox("Vertices");
    m_textureCoordsCheck = new0 QCheckBox("Texture coordinates");
    m_normalsCheck       = new0 QCheckBox("Normals");

    m_convertButton      = new0 QPushButton("Convert");
    connect(m_convertButton, SIGNAL(clicked()), this, SLOT(Convert()));

    QHBoxLayout *layout     = new0 QHBoxLayout;
    QGridLayout *gridLayout = new0 QGridLayout;

    layout->setMenuBar(m_menu);

    QGridLayout *vertexBufferLayout = new0 QGridLayout;
    vertexBufferLayout->addWidget(m_verticesCheck, 0, 0, 1, 1);
    vertexBufferLayout->addWidget(m_normalsCheck, 1, 0, 1, 1);
    vertexBufferLayout->addWidget(m_textureCoordsCheck, 2, 0, 1, 1);
    m_vertexBufferGroup->setLayout(vertexBufferLayout);

    QGridLayout *checkLayout = new0 QGridLayout;
    checkLayout->addWidget(m_obbCheck, 0, 0, 1, 1);
    checkLayout->addWidget(m_bsphereCheck, 1, 0, 1, 1);
    checkLayout->addWidget(m_indexBufferCheck, 0, 1, 1, 1);
    checkLayout->addWidget(m_vertexBufferGroup, 2, 0, 3, 1);
    m_checkGroup->setLayout(checkLayout);

    gridLayout->addWidget(m_checkGroup, 1, 0, 3, 3);
    gridLayout->addWidget(m_convertButton, 5, 2, 1, 1);

    layout->addWidget(m_meshList);
    layout->addLayout(gridLayout);

    setLayout(layout);
}

ConvertMeshFormatWidget::~ConvertMeshFormatWidget() {}

void ConvertMeshFormatWidget::OpenFile() {
    QString &filePath = QFileDialog::getOpenFilePath(this, tr("Open mesh file"), "", "");

    if (m_assetImporter.OpenFile(filePath.toLocal8Bit().constData())) {
        std::vector<std::string> meshes;
        m_assetImporter.GetMesheNames(meshes);

        m_meshList->clear();
        for (unsigned i = 0; i < meshes.size(); ++i) {
            QListWidgetItem *newItem = new0 QListWidgetItem;
            newItem->setText(QString(meshes[i].c_str()));
            m_meshList->insertItem(i, newItem);
        }

        m_meshList->item(0)->setSelected(true);

        show();
    } else {
        QMessageBox::warning(NULL, tr("Could not open file"),
                             tr("The assimp library could not open the file for import."));
    }
}

void ConvertMeshFormatWidget::Convert() {
    QList<QListWidgetItem *> selectedItems = m_meshList->selectedItems();
    if (selectedItems.size() == 0)
        return;
    std::string meshName      = selectedItems[0]->text().toLocal8Bit().constData();

    QString folderPathQString = QFileDialog::getExistingDirectory(
        this, tr("Select directory"), "",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    std::string folderPath(folderPathQString.toLocal8Bit().constData());
    folderPath += "/";

    if (m_obbCheck->isChecked()) {}
    if (m_bsphereCheck->isChecked()) {}
    if (m_indexBufferCheck->isChecked()) {
        std::vector<U8> indexBuffer;
        m_assetImporter.GetIndexBuffer(indexBuffer, meshName);

        m_fileSystemIO.SaveFile(folderPath + meshName + ".indexbuffer", indexBuffer);
    }
    if (m_verticesCheck->isChecked() || m_textureCoordsCheck->isChecked() ||
        m_verticesCheck->isChecked()) {
        I32 flags = 0;
        if (m_verticesCheck->isChecked())
            flags ^= TE::IO::VERTEXBUFFER_POSITION;
        if (m_normalsCheck->isChecked())
            flags ^= TE::IO::VERTEXBUFFER_NORMALS;
        if (m_textureCoordsCheck->isChecked())
            flags ^= TE::IO::VERTEXBUFFER_TEXTURECOORDS;

        std::vector<U8> vertexBuffer;
        m_assetImporter.GetVertexBuffer(vertexBuffer, meshName, flags);

        m_fileSystemIO.SaveFile(folderPath + meshName + ".vertexbuffer", vertexBuffer);
    }
}
