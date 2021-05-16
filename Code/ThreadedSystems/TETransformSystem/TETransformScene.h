#ifndef TETRANSFORMSCENE_H
#define TETRANSFORMSCENE_H

#include "TEDataTypes.h"
#include <TESystemScene.h>

#include <list>
#include <string>

namespace TE {
    namespace Event {
        class EventManager;
    }

    namespace Transform {
        class TransformScene : public Engine::SystemScene {
          public:
            TransformScene(Event::EventManager &eventManager);
            virtual ~TransformScene();

            virtual void Initialize();
            virtual void Cleanup();
            virtual Engine::SystemTask *GetSystemTask();
            virtual Engine::SystemObjectSPtr CreateSystemObject(const std::string &objectType, I32 objectId);

          private:
            Event::EventManager &m_eventManager;
        };
    }
}

#endif
