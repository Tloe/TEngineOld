#ifndef TECAMERAOBJECT_H
#define TECAMERAOBJECT_H

#include "TEDataTypes.h"
#include "TEGraphicsObject.h"
#include <TECamera.h>
#include <TECameraNode.h>
#include <TESceneManager.h>

namespace TE {
    namespace Graphics {
        class SceneGraphBuilder;
    }
    namespace Engine {
        class Property;
        typedef std::vector<Property> PropertyVec;
    }

    namespace Graphics {
        class CameraObject : public GraphicsObject {
          public:
            struct Values {
                enum {
                    Frustrum,
                    ActiveCamera,
                    Parrent
                };
            };

            struct FrustrumType {
                enum {
                    FromFov,
                    FromValues
                };
            };

            CameraObject(I32 objectId, SceneGraph::SceneManager &sceneManager);

            virtual void SetValue(Core::Value &value);
            virtual void Initialize();
            virtual void Cleanup();
            //            virtual void JSONDeserialize(const Json::Value& jsonValue);
            //			virtual void JSONSerialize(Json::Value& jsonValue);
            virtual void OnSubjectChange(Subject *subject, Bitmask64 changeBits);

          private:
            SceneGraph::SceneManager &m_sceneManager;
            SceneGraph::CameraNode m_cameraNode;
            SceneGraph::Camera m_camera;
        };

    }
}

#endif
