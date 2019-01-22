#ifndef TEGAMESCENE_H
#define TEGAMESCENE_H

#include "TEDataTypes.h"
#include "TESystemScene.h"
#include "TEGameTask.h"

#include <string>

namespace TE
{
    namespace Engine { class SystemTask; }
    namespace Engine { class SystemObject; typedef std::shared_ptr<SystemObject> SystemObjectSPtr; }

    namespace Game
    {
        class GameScene : public Engine::SystemScene
        {
        public:
			GameScene();

            virtual void Initialize();
            virtual void Cleanup();

            virtual Engine::SystemTask* GetSystemTask();
            virtual Engine::SystemObjectSPtr CreateSystemObject(const std::string& objectType, I32 objectId);

			void Update();

        private:
            GameTask m_gameTask;
        };
    }
}

#endif
