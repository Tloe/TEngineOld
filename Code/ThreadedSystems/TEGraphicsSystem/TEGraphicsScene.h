#ifndef TEGRAPHICSSCENE_H
#define TEGRAPHICSSCENE_H

#include "TESystemScene.h"
#include "TESceneManager.h"
#include "TEGraphicsTask.h"

#include <map>

namespace TE
{
	namespace Engine { class SystemObject; }

	namespace Graphics
	{
		class GraphicsScene : public Engine::SystemScene
		{
		public:
			GraphicsScene(SceneGraph::SceneManager& sceneManager);

			virtual void Initialize();
			virtual void Cleanup();
			virtual Engine::SystemTask* GetSystemTask();
            virtual Engine::SystemObjectSPtr CreateSystemObject(const std::string& objectType, I32 objectId);

        private:
            SceneGraph::SceneManager& m_sceneManager;
			GraphicsTask m_graphicsTask;
		};
	}
}

#endif
