#ifndef TELIGHTNODE_H
#define TELIGHTNODE_H

#include <TEDataTypes.h>
#include <TENode.h>
#include <TELight.h>

namespace TE
{
	namespace SceneGraph
	{
		class LightNode : public Node
		{
		public:
			LightNode(const Light& light);

			virtual ~LightNode();

			void SetLight(const Light& light);

			Light& GetLight();

			virtual void UpdateWorldData();
		private:
			Light m_light;
		};
	}
}

#endif
