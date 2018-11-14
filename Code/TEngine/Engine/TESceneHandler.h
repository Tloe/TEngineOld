#ifndef TESCENEHANDLER_H
#define TESCENEHANDLER_H

#include "TEUniversalScene.h"
#include "TEResourceManager.h"
#include "TEResource.h"
#include "TESystem.h"

#include <set>

namespace TE
{
	namespace Engine { class ChangeSyncer; }
	namespace Engine { class FileIO; }
	namespace Engine { class Scheduler; }

	namespace Engine
	{
		class SceneHandler
		{
		public:
			SceneHandler(ChangeSyncer& changeSyncer,
						 TE::IO::FileIO& fileIO,
                         SystemUPtrVec& systems,
						 Scheduler& scheduler);

			void AddSceneFile(const std::string& sceneFile);
			void RemoveSceneFile(const std::string& sceneFile);
			void SetCurrentScene(const std::string& sceneFile);
            UniversalScene& GetScene(const std::string& sceneFile);
			void Cleanup();
		private:
            typedef std::set<std::string> SceneFileSet;

            ChangeSyncer& m_changeSyncer;
			Resources::ResourceManager<UniversalScene> m_sceneResourceManager;
			Resources::ResourceHandle<UniversalScene> m_currentScene;
            SceneFileSet m_sceneFiles;
            SystemUPtrVec& m_systems;
			Scheduler& m_scheduler;
		};
	}
}

#endif
