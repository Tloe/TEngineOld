#ifndef TEGRAPHICSOBJECT_H
#define TEGRAPHICSOBJECT_H

#include "TEDataTypes.h"
#include "TESystemObject.h"

namespace TE
{
	namespace SceneGraph { class SceneManager; }

	namespace Graphics
	{
		namespace GraphicsObjectType
		{
			enum
			{
				Renderable,
				Camera,
				Light
			};
		}

		class GraphicsObject : public Engine::SystemObject
		{
		public:
            GraphicsObject(I32 objectId, Enum type, SceneGraph::SceneManager& sceneManager);
			virtual ~GraphicsObject();
            virtual Bitmask64 GetDesiredSystemChanges();
            virtual Bitmask64 GetPotentialSystemChanges();
            virtual I32 GetObjectId() const;
			Enum GetType();

		protected:
			SceneGraph::SceneManager& GetSceneManager();
		private:
            Enum m_type;
			SceneGraph::SceneManager& m_sceneManager;
            I32 m_objectId;
		};
	}
}

#endif
