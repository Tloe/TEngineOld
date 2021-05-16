#include "main.h"

#include "TEApiContextIncludes.h"
#include "TEEngine.h"
#include "TEFileSystemIO.h"

#include "TEGraphicsSystem.h"
#include "TETransformSystem.h"

#include "TEActionExecutor.h"
#include "TEEnvironmentUpdateEvent.h"
#include "TEEventManager.h"
#include "TEGameSystem.h"
#include "TEInputMapper.h"
#include "TENetworkManager.h"
#include "TENetworkSystem.h"
#include "TEOrientationEvent.h"
#include "TEQuaternion.h"
#include "TERangeExecutor.h"
#include "TEResolutionEvent.h"
#include "TEValue.h"
#include "TEVariant.h"
#include "TEVector3D.h"
#include <TERenderableObject.h>
#include <TETransformObject.h>
#include <TETranslationEvent.h>

#include "TELuaState.h"

int objectId = 3;

class FireExecutor : public TE::InputMapping::ActionExecutor {
  public:
    FireExecutor(TE::Event::EventManager &eventManager) : ActionExecutor("Fire0"),
                                                          m_eventManager(eventManager) {}

    virtual void Execute() {
        TE::Math::Quaternion<F32> rotation;
        rotation.SetRotationAboutX(0.05f);
        rotation.Normalize();
        TE::Event::OrientationEvent orientationEvent(rotation);

        m_eventManager.QueEvent(orientationEvent);
    }

  private:
    TE::Event::EventManager &m_eventManager;
};

class MoveExecutor : public TE::InputMapping::RangeExecutor {
  public:
    MoveExecutor(TE::Event::EventManager &eventManager) : RangeExecutor("MoveOnXAxis"),
                                                          m_eventManager(eventManager) {}

    virtual void Execute(F64 range) {
        TE::Math::Vector3D<F32> translation(3 * -static_cast<F32>(range), 0.0, 0.0);
        TE::Event::TranslationEvent translationEvent(translation);

        m_eventManager.QueEvent(translationEvent);
    }

  private:
    TE::Event::EventManager &m_eventManager;
};

void SpawnPlayer(TE::Engine::EngineRoot &engine) {
    TE::Engine::UniversalScene &universalScene   = engine.GetSceneHandler().GetScene("/Scenes/TestScene.scene");
    TE::Engine::UniversalObject &universalObject = universalScene.CreateUniversalObject("Player0");

    U32 graphicsSystemId                         = universalScene.GetSystemId("Graphics");
    U32 transformSystemId                        = universalScene.GetSystemId("Transform");
    U32 networkSystemId                          = universalScene.GetSystemId("Network");

    auto transformObject                         = universalScene.GetSystemScene(transformSystemId)->CreateSystemObject("TransformObject", universalObject.GetObjectId());
    ;
    auto renderableObject = universalScene.GetSystemScene(graphicsSystemId)->CreateSystemObject("RenderableObject", universalObject.GetObjectId());
    ;
    auto networkObject = universalScene.GetSystemScene(networkSystemId)->CreateSystemObject("NetworkObject", universalObject.GetObjectId());

    TE::Core::Value value(TE::Graphics::RenderableObject::Values::Mesh);
    value.AddString("/Meshes/Cube01.mesh");
    renderableObject->SetValue(value);

    value.Reset(TE::Graphics::RenderableObject::Values::Texture);
    value.AddString("/Textures/test4.png");
    renderableObject->SetValue(value);

    value.Reset(TE::Graphics::RenderableObject::Values::Effect);
    value.AddString("/Shaders/TEBasicTextured.cgfx");
    renderableObject->SetValue(value);

    value.Reset(TE::Graphics::RenderableObject::Values::BoundingVolume);
    value.AddString("Sphere");
    renderableObject->SetValue(value);

    value.Reset(TE::Graphics::RenderableObject::Values::Parrent);
    value.AddString("Root");
    renderableObject->SetValue(value);

    value.Reset(TE::Transform::TransformObject::Values::Position);
    TE::Core::AddVector(TE::Math::Vector3D<F32>(0.0f, 0.0f, 1.0f), value);
    transformObject->SetValue(value);

    value.Reset(TE::Transform::TransformObject::Values::Orientation);
    TE::Math::Quaternion<F32> q;
    q.SetRotationAboutAxis(2.5, TE::Math::Vector3D<F32>(3.0, 1.0, 4.0).Normalize());
    TE::Core::AddQuaternion(q, value);
    transformObject->SetValue(value);

    value.Reset(TE::Transform::TransformObject::Values::SubscribeTranslationEvent);
    value.AddBool(true);
    transformObject->SetValue(value);

    value.Reset(TE::Transform::TransformObject::Values::SubscribeOrientationEvent);
    value.AddBool(true);
    transformObject->SetValue(value);

    auto &networkSystem = engine.GetSystem<TE::Network::NetworkSystem>(networkSystemId);
    if (!networkSystem.GetNetworkManager().IsServer()) {
        value.Reset(TE::Network::NetworkObject::Values::SubscribeTranslationEvent);
        value.AddBool(true);
        networkObject->SetValue(value);

        value.Reset(TE::Network::NetworkObject::Values::SubscribeOrientationEvent);
        value.AddBool(true);
        networkObject->SetValue(value);
    }

    universalObject.AddSystemObject(graphicsSystemId, renderableObject);
    universalObject.AddSystemObject(transformSystemId, transformObject);
    universalObject.AddSystemObject(networkSystemId, networkObject);

    networkSystem.GetNetworkManager().MapConnectionToObjectId(0, 3);
}

I32 main() {
#if TE_WINDOWS
    TE::IO::FileSystemIO fileIO("D:/code/tengine/Executables/Data");
#elif TE_LINUX
    TE::IO::FileSystemIO fileIO("/src/tengine/Executables/Data");
#endif

    TE::Graphics::GraphicsSystemFactory graphicsSystemFactory;
    TE::Transform::TransformSystemFactory transformSystemFactory;
    TE::Network::NetworkSystemFactory networkSystemFactory;
    TE::Game::GameSystemFactory gameSystemFactory;

    TE::Engine::EngineRoot engine(fileIO, std::string("/Scripts/InitScript.lua"));
    engine.AddSystemFactory(graphicsSystemFactory);
    engine.AddSystemFactory(transformSystemFactory);
    engine.AddSystemFactory(networkSystemFactory);
    engine.AddSystemFactory(gameSystemFactory);

    engine.Startup();

    auto &graphicsSystem = engine.GetSystem<TE::Graphics::GraphicsSystem>("Graphics");
    engine.SetMessageLoop([&graphicsSystem]() { return graphicsSystem.GetPlatformWindow().MessageLoop(); });

    engine.GetSceneHandler().AddSceneFile("/Scenes/TestScene.scene");
    engine.GetSceneHandler().SetCurrentScene("/Scenes/TestScene.scene");

    SpawnPlayer(engine);
    if (true) // c == 'c')
    {
        TE::InputMapping::InputMapper &inputMapper        = graphicsSystem.GetPlatformWindow().GetInputMapper();

        TE::InputMapping::ActionExecutorUPtr fireExecutor = std::make_unique<FireExecutor>(engine.GetEventManager());
        TE::InputMapping::RangeExecutorUPtr rangeExecutor = std::make_unique<MoveExecutor>(engine.GetEventManager());
        inputMapper.AddActionExecutor(fireExecutor, 1);
        inputMapper.AddRangeExecutor(rangeExecutor, 1);

        inputMapper.PushContext("MainContext");

        TE::Core::Value value(TE::Network::NetworkSystem::Values::Connect);
        value.AddString("127.0.0.1");
        value.AddString("4445");
        value.AddString("IPv4");
        engine.GetSystem("Network").SetValue(value);
    }

    engine.Run();

    engine.Shutdown();

    return 0;
}
