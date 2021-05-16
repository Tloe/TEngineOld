#ifndef TESCENENODE_H
#define TESCENENODE_H

#include <TEBSphere.h>
#include <TETransform.h>
#include <list>
#include <stack>
#include <vector>
//#include <TEGlobalState.h>
//#include <TELight.h>
#include "TECamera.h"

namespace TE {
    namespace Math {
        template <typename T>
        class Matrix4D;
    }
    namespace Math {
        template <typename T>
        class Matrix3D;
    }
    namespace Math {
        template <typename T>
        class Vector3D;
    }
    namespace Math {
        template <typename T>
        class Quaternion;
    }
    namespace SceneGraph {
        class Renderable;
    }

    namespace SceneGraph {
        class Spatial {
          public:
            typedef std::list<TE::SceneGraph::Renderable *> RenderablePtrList;

            Spatial();
            virtual ~Spatial();

            // void UpdateRenderState(std::stack< Memory::Pointer0< GlobalState > >* stateStack = NULL, std::vector< Memory::Pointer0< Light > >* lightStack = NULL);
            // void SetGlobalState (Memory::Pointer0<GlobalState> globalState);
            // GlobalState* GetGlobalState(I32 stateType);
            // void RemoveGlobalState(I32 stateType);
            // void RemoveAllGlobalStates();

            void Update(bool initiator = true);
            const Intersection::BSphere &GetBounding();
            void SetBounding(const Intersection::BSphere &bounding);

            virtual void GetRenderListNoCull(RenderablePtrList &renderList)                 = 0;
            virtual void GetRenderListNoSort(RenderablePtrList &renderList, Camera &camera) = 0;

            void SetTranslation(const Math::Vector3D<Real> &translation, bool localTransform = true);
            void SetScale(const Math::Vector3D<Real> &scale, bool localTransform = true);
            void SetScale(Real scale, bool localTransform = true);
            void SetOrientation(const Math::Quaternion<Real> &orientation, bool localTransform = true);
            const Math::Matrix4D<Real> &GetTransformMatrix();

          protected:
            /*void PropagateStateFromRoot(std::stack< Memory::Pointer0< GlobalState > >* stateStack, std::vector< Memory::Pointer0< Light > >* lightStack);
            virtual void UpdateRenderStateLocal(std::stack< Memory::Pointer0< GlobalState > >* stateStack, std::vector< Memory::Pointer0< Light > >* lightStack) = 0;
            void PushState(std::stack< Memory::Pointer0< GlobalState > >* stateStack, std::vector< Memory::Pointer0< Light > >* lightStack);
            void PopState(std::stack< Memory::Pointer0< GlobalState > >* stateStack, std::vector< Memory::Pointer0< Light > >* lightStack);*/

            bool IsCulled(Camera &camera) const;
            virtual void UpdateWorldData();
            virtual void UpdateWorldBound() = 0;
            void PropagateBoundToRoot();

            Math::Transform<Real> m_localTransform;
            Math::Transform<Real> m_worldTransform;

            Spatial *m_parent;
            Intersection::BSphere m_bounding;

            bool m_worldBoundIsCurrent;
            bool m_scaleSinceUpdate;
            bool m_translateSinceUpdate;
            bool m_rotationSinceUpdate;
            bool m_forceCull;

            // std::list<Memory::Pointer0<GlobalState> >	m_globalStates;
            // std::list<LightPtr>							m_lights;
        };
    }
}

#endif
