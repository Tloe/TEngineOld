#ifndef TENETWORKSCENE_H
#define TENETWORKSCENE_H

#include "TENetworkManager.h"
#include "TENetworkTask.h"
#include "TESystemScene.h"

namespace TE {
    namespace Event {
        class EventManager;
    }
    namespace Network {
        class NetworkObject;
        typedef std::weak_ptr<NetworkObject> NetworkObjectWPtr;
    }
    namespace Network {
        struct Outgoing;
    }

    namespace Network {
        class NetworkScene : public Engine::SystemScene {
          public:
            NetworkScene(Event::EventManager &eventManager, NetworkManager &networkManager);

            virtual void Initialize();
            virtual void Cleanup();
            virtual Engine::SystemTask *GetSystemTask();
            virtual Engine::SystemObjectSPtr CreateSystemObject(const std::string &objectType, I32 objectId);
            void Update(U64 dt, U64 time);

          private:
            NetworkTask m_networkTask;
            NetworkManager &m_networkManager;
            Event::EventManager &m_eventManager;
        };
    }
}

#endif
