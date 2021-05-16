#ifndef CONVERTMESHFORMATWIDGET_H
#define CONVERTMESHFORMATWIDGET_H

#include "TEFileSystemIO.h"
#include <DatFileModel.h>
#include <QtGui>
#include <TEAssetImporter.h>

class ConvertMeshFormatWidget : public QWidget {
    Q_OBJECT
  public:
    ConvertMeshFormatWidget(QWidget *parent);
    ~ConvertMeshFormatWidget();
  private slots:
    void OpenFile();
    void Convert();

  private:
    TE::IO::AssetImporter m_assetImporter;
    TE::IO::FileSystemIO m_fileSystemIO;

    QMenuBar *m_menu;
    QMenu *m_fileMenu;
    QAction *m_openAction;
    QAction *m_closeAction;

    QListWidget *m_meshList;
    QGroupBox *m_checkGroup;
    QCheckBox *m_obbCheck;
    QCheckBox *m_bsphereCheck;
    QCheckBox *m_indexBufferCheck;
    QGroupBox *m_vertexBufferGroup;
    QCheckBox *m_verticesCheck;
    QCheckBox *m_normalsCheck;
    QCheckBox *m_textureCoordsCheck;

    QPushButton *m_convertButton;
};

#endif