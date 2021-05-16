#ifndef TEGAMELOOP_H
#define TEGAMELOOP_H

#include "TEChangeMasks.h"
#include "TEChangeSyncer.h"
#include "TEEnvironment.h"
#include "TEEventHandler.h"
#include "TEEventManager.h"
#include "TELuaExtended.h"
#include "TELuaState.h"
#include "TESceneHandler.h"
#include "TEScheduler.h"
#include "TEThreadPool.h"

#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace TE {
    namespace IO {
        class FileIO;
    }
    namespace EntityManagement {
        class EntityManager;
    }
    namespace CollisionDetection {
        class CollisionComponent;
    }
    namespace Physics {
        class PhysicsComponent;
    }
    namespace Platform {
        class PlatformWindow;
    }

    namespace Engine {
        class EngineRoot
            : public Event::EventHandler,
              public Lua::Extended
        //, public IO::JsonSerializer
        {
          public:
            EngineRoot(IO::FileIO &fileIO, const std::string &initScript = "");
            ~EngineRoot();

            virtual void HandleEvent(Event::EnvironmentUpdateEvent &environmentUpdateEvent);
            virtual void SetData(Lua::Table &luaTable);
            virtual Lua::Table GetData();
            // virtual void JSONDeserialize( const Json::Value& jsonValue );
            // virtual void JSONSerialize(Json::Value& jsonValue);

            void Startup();
            void Run();
            void Shutdown();

            void SetMessageLoop(std::function<bool()> function);

            Event::EventManager &GetEventManager();
            SceneHandler &GetSceneHandler();
            IO::FileIO &GetFileIO();

            void AddSystemFactory(SystemFactory &systemGenerator);
            U32 GetSystemId(const std::string &systemName);

            System &GetSystem(const std::string &systemName);

            template <typename SystemT>
            SystemT &GetSystem(const std::string &systemName) {
                auto findItr = std::find_if(std::begin(m_systems), std::end(m_systems),
                                            [&systemName](SystemUPtr &sysPtr) { return sysPtr->GetSystemName() == systemName; });

                assert(findItr != std::end(m_systems) && "System type not added");

                assert(dynamic_cast<SystemT *>(findItr->get()) != nullptr);

                return static_cast<SystemT &>(*findItr->get());
            }

            template <typename SystemT>
            SystemT &GetSystem(U32 systemId) {
                auto findItr = std::find_if(std::begin(m_systems), std::end(m_systems),
                                            [&systemId](SystemUPtr &sysPtr) { return sysPtr->GetSystemId() == systemId; });

                assert(findItr != std::end(m_systems) && "System type not added");

                assert(dynamic_cast<SystemT *>(findItr->get()) != nullptr);

                return static_cast<SystemT &>(*findItr->get());
            }

          private:
            typedef std::vector<SystemFactory *> SystemGeneratorVec;

            SystemUPtrVec m_systems;
            SystemGeneratorVec m_systemFactories;

            IO::FileIO &m_fileIO;
            std::string m_startupScript;
            Scheduler m_scheduler;
            Event::EventManager m_eventManager;
            Environment m_environment;
            Threading::ThreadPool m_threadPool;
            ChangeSyncer m_changeSyncer;
            SceneHandler m_sceneHandler;
            std::function<bool()> m_messageLoop;
            Lua::State m_luaState;

            U64 m_maxFrameTime;
            Time::Timer m_frameTimer;
            U64 m_accumulatedFrameTime;
            U64 m_accumulatedFrameRate;
            U64 m_microsecondsPrFrame;
            U64 m_totalFrameTime;
            U32 m_updateFrameCount;
            U32 m_drawFrameCount;
            U32 m_previousUpdateFrameCount;
            U32 m_previousDrawFrameCount;
            U32 m_updateFPS;
            U32 m_drawFPS;
            U64 m_previousFPSTime;
        };
    }
}

#endif
