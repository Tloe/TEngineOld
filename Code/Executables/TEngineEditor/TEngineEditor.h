#ifndef TENGINEEDITOR_H
#define TENGINEEDITOR_H

#include "TECameraNode.h"
#include "TEEngine.h"
#include "TENode.h"
#include "TERenderWidget.h"
#include "TESceneManager.h"
#include <QtGui>

class DatFileWidget;
class ConvertMeshFormatWidget;

class TEngineEditor : public QMainWindow {
    Q_OBJECT
  public:
    TEngineEditor();
    ~TEngineEditor();
  private slots:
    void DrawScene();

  private:
    DatFileWidget *m_datFileManager;
    ConvertMeshFormatWidget *m_convertMeshWidget;

    void SetupDemoScene();
    void CleanupDemoScene();

    // Menues
    QMenu *m_fileMenu;
    QMenu *m_utilsMenu;
    // Menu actions
    QAction *m_exitAction;
    QAction *m_openDatFileAction;
    QAction *m_openDatManagerAction;
    QAction *m_openMeshConverterAction;
    QAction *m_demoDraw;

    // Widgets
    TEngineRenderWidget *m_tegineRenderWidget;
    QDockWidget *m_sceneViewDock;
    QTreeView *m_sceneViewTree;

    // demoscene
    TE::Render::RendererPtr m_renderer;
    TE::SceneGraph::SceneManagerPtr m_sceneMgr;
    TE::SceneGraph::RenderablePtr cubePtr;
    TE::SceneGraph::CameraNodePtr camNodeptr;
};

#endif