#ifndef TEINPUTSCENE_H
#define TEINPUTSCENE_H

#include <list>
#include "TESystemScene.h"
#include "TEInputTask.h"

namespace TE
{
	namespace Input { class InputObject; typedef std::unique_ptr<InputObject> InputObjectUPtr; }
	namespace Input { class InputSystem; }
	namespace Platform { class PlatformWindow; }
	namespace Engine { class Property; typedef std::vector<Property> PropertyVec; }

	namespace Input
	{
		class InputScene : public Engine::SystemScene
		{
		public:
			InputScene(InputSystem& inputSystem, Platform::PlatformWindow& platformWindow);

			virtual void Initialize();
			virtual void Cleanup();
			virtual void SetProperties( const Engine::PropertyVec& properties );
			virtual void GetProperties( Engine::PropertyVec& properties );
			virtual Hash GetSystemHash();
			virtual const std::string& GetSystemString();
			virtual Engine::SystemTask* GetSystemTask();
			virtual Engine::SystemObject* CreateSystemObject(const std::string& objectTypeStr, const std::string& objectName);
			virtual void DestroySystemObject( Engine::SystemObject* systemObject );

			void InputUpdate();
			InputObject* FindInputObject(Hash objectHash);

			

		private:
			typedef std::list<InputObject*> InputObjectPtrList;

			InputSystem& m_inputSystem;
			Platform::PlatformWindow& m_platformWindow;
			InputObjectPtrList m_inputObjects;
			InputTask m_inputTask;
		};
	}
}

#endif