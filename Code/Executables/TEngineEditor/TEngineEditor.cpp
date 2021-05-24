#include "ConvertMeshFormatWidget.h"
#include "TECamera.h"
#include "TECameraNode.h"
#include "TEEffect.h"
#include "TEIndexBuffer.h"
#include "TEPlatformContextWin.h"
#include "TERenderable.h"
#include "TETexture.h"
#include "TETexturePNG.h"
#include "TEVector3D.h"
#include "TEVertexBuffer.h"
#include "TEVertexBufferLayout.h"
#include <DatFileManagerWidget.h>
#include <QtGui>
#include <TEngineEditor.h>

TEngineEditor::TEngineEditor() {
    m_tegineRenderWidget = new0 TEngineRenderWidget(this);
    m_tegineRenderWidget->setMinimumSize(640, 480);
    setCentralWidget(m_tegineRenderWidget);

    TE::IO::FileIOPtr fileLoader(
        new0 TE::IO::FileSystemIO("D:/coding/tengine/Executables/EngineTest"));
    TE::Context::PlatformContext newContext(centralWidget()->winId());
    m_renderer = new0 TE::Render::Renderer(newContext, fileLoader);
    m_renderer->Initialize();
    m_sceneMgr       = new0 TE::SceneGraph::SceneManager(m_renderer);

    m_datFileManager = new0 DatFileWidget(this);
    m_datFileManager->setWindowFlags(Qt::Tool);
    m_datFileManager->move(rect().center() - m_datFileManager->rect().center());
    m_openDatManagerAction = new0 QAction(tr("Dat File Manager"), this);
    connect(m_openDatManagerAction, SIGNAL(triggered()), m_datFileManager, SLOT(show()));

    m_convertMeshWidget = new0 ConvertMeshFormatWidget(this);
    m_convertMeshWidget->setWindowFlags(Qt::Tool);
    m_convertMeshWidget->move(rect().center() - m_convertMeshWidget->rect().center());
    m_openMeshConverterAction = new0 QAction(tr("Mesh Converter"), this);
    connect(m_openMeshConverterAction, SIGNAL(triggered()), m_convertMeshWidget, SLOT(show()));

    m_exitAction = new0 QAction(tr("E&xit"), this);
    connect(m_exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    m_demoDraw = new0 QAction(tr("&Draw"), this);
    connect(m_demoDraw, SIGNAL(triggered()), this, SLOT(DrawScene()));

    m_fileMenu = menuBar()->addMenu(tr("F&ile"));
    m_fileMenu->addAction(m_demoDraw);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    m_utilsMenu = menuBar()->addMenu(tr("&Utils"));
    m_utilsMenu->addAction(m_openDatManagerAction);
    m_utilsMenu->addAction(m_openMeshConverterAction);

    setWindowTitle(tr("TEngine Editor"));

    SetupDemoScene();
}

TEngineEditor::~TEngineEditor() {
    CleanupDemoScene();
    m_renderer->Cleanup();
}

void TEngineEditor::SetupDemoScene() {
    TE::SceneGraph::NodePtr rootNode(new0 TE::SceneGraph::Node);

    TE::Render::VertexBufferPtr newVertexBuffer(new0 TE::Render::VertexBuffer(
        "/Meshes/Cube01/Cube01.vertexbuffer", TE::Render::VertexBuffer::PRIMITIVETYPE_TRIANGLES,
        TE::Render::VertexBuffer::USAGE_DYNAMIC));

    Hash vertexBuffer = m_renderer->Register(newVertexBuffer);

    Hash indexBuffer = m_renderer->Register(TE::Render::IndexBufferPtr(new0 TE::Render::IndexBuffer(
        "/Meshes/Cube01/Cube01.indexbuffer", TE::Render::IndexBuffer::USAGE_DYNAMIC)));

    TE::Render::BufferLayoutPtr newVertexLayout(new0 TE::Render::VertexBufferLayout(
        "DEBUG: CHANGE THIS IN LOADFILE OF TEFileSystemIO.cpp"));
    newVertexLayout->AddElement(TE::Render::VertexBufferLayout::SEMANTIC_POSITION,
                                TE::Render::VertexBufferLayout::TYPE_F32, 3, 0);
    newVertexLayout->AddElement(TE::Render::VertexBufferLayout::SEMANTIC_NORMAL,
                                TE::Render::VertexBufferLayout::TYPE_F32, 3, 12);
    newVertexLayout->AddElement(TE::Render::VertexBufferLayout::SEMANTIC_TEXTURE,
                                TE::Render::VertexBufferLayout::TYPE_F32, 2, 24);
    Hash vertexLayout = m_renderer->Register(newVertexLayout);

    Hash effect       = m_renderer->Register(
              TE::Render::EffectPtr(new0 TE::Render::Effect("/Shaders/TEBasicTextured.cgfx")));

    Hash texture = m_renderer->Register(
        TE::Render::TexturePtr(new0 TE::Render::TexturePNG("/Textures/test.png")));

    TE::SceneGraph::RenderablePtr cube(
        new0 TE::SceneGraph::Renderable(vertexLayout, vertexBuffer, indexBuffer, effect, texture));
    cubePtr = cube;
    TE::Intersection::BSphere bounding;
    BSphereFromVertexData(bounding, newVertexBuffer->GetDataF32Ptr(),
                          newVertexBuffer->GetElementCount());

    cube->SetBounding(bounding);
    cube->GetWorldTransform().SetTranslation(TE::Math::Vector3D<Real>(0.0, 0.0, 0.0));
    rootNode->AddChild(cube);

    TE::SceneGraph::CameraPtr cam(new0 TE::SceneGraph::Camera);
    cam->SetFrustrum(TE::Math::Base<Real>::HALF_PI / 2, 640.0f / 480.0f, 0.1f, 100.0f);
    cam->SetLocation(TE::Math::Vector3D<Real>(0.0f, 0.0f, -5.0f));
    TE::Math::Quaternion<Real> orientation;
    orientation.SetRotationAboutX(0.0f);
    cam->SetOrientation(orientation);

    TE::SceneGraph::CameraNodePtr camNode(new0 TE::SceneGraph::CameraNode(cam));
    camNodeptr = camNode;
    rootNode->AddChild(camNode);

    m_sceneMgr->SetActiveCamera(camNode->GetCamera());
    m_sceneMgr->SetRootNode(rootNode);
    m_sceneMgr->InitScene();
}

void TEngineEditor::CleanupDemoScene() { m_sceneMgr->CleanupScene(); }

void TEngineEditor::DrawScene() {
    QRect geometry = centralWidget()->geometry();
    I32 width      = geometry.width() / 2;
    I32 height     = geometry.height() / 2;

    m_renderer->SetWindowed(geometry.width(), geometry.height());

    m_renderer->BeginFrame();

    m_renderer->SetViewPort(0, 0, width, height);
    m_sceneMgr->DrawScene();

    m_renderer->SetViewPort(width, 0, width, height);
    m_sceneMgr->DrawScene();

    m_renderer->SetViewPort(0, height, width, height);
    m_sceneMgr->DrawScene();

    m_renderer->SetViewPort(width, height, width, height);
    m_sceneMgr->DrawScene();

    m_renderer->EndFrame();
    cubePtr->GetWorldTransform().Translate(TE::Math::Vector3D<Real>(0.5, 0.0, 0.0));
}