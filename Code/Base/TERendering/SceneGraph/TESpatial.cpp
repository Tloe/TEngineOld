#include <TESpatial.h>
#include <TECamera.h>
#include <TERenderer.h>
#include <TERenderable.h>
#include "TEMatrix4D.h"

TE::SceneGraph::Spatial::Spatial()
	:
	m_parent(NULL),
	m_worldBoundIsCurrent(false),
	m_forceCull(false)
{

}

TE::SceneGraph::Spatial::~Spatial()
{

}

const TE::Intersection::BSphere& TE::SceneGraph::Spatial::GetBounding()
{
	return m_bounding;
}

void TE::SceneGraph::Spatial::Update(bool initiator)
{
	UpdateWorldData();
	//Commented out as it needs more work
	//UpdateWorldBound();
	//if(initiator) PropagateBoundToRoot();
}

void TE::SceneGraph::Spatial::PropagateBoundToRoot()
{
	if (m_parent)
	{
		m_parent->UpdateWorldBound();
		m_parent->PropagateBoundToRoot();
	}
}

void TE::SceneGraph::Spatial::UpdateWorldData()
{
	if (m_parent)
	{
		if (m_parent->m_localTransform.HasTranslationChange())
		{
			m_worldTransform.SetTranslation(m_parent->m_worldTransform.GetTranslation() + m_localTransform.GetTranslation());
		}
		if (m_parent->m_localTransform.HasScaleChange())
		{
			m_worldTransform.SetScale(m_parent->m_worldTransform.GetScale() + m_localTransform.GetScale());
		}
		if (m_parent->m_localTransform.HasOrientationChange())
		{
			m_worldTransform.SetOrientation(m_parent->m_worldTransform.GetOrientation() * m_localTransform.GetOrientation());
		}
	}
	else
	{
		m_worldTransform = m_localTransform;
	}
}

void TE::SceneGraph::Spatial::SetBounding( const Intersection::BSphere& bounding )
{
	m_bounding = bounding;
}

/*void TE::SceneGraph::Spatial::SetGlobalState( Memory::Pointer0<GlobalState> globalState )
{
	m_globalStates.push_back(globalState);
}

TE::SceneGraph::GlobalState* TE::SceneGraph::Spatial::GetGlobalState( I32 stateType )
{
	std::list<Memory::Pointer0<GlobalState> >::iterator itr = m_globalStates.begin();

	while(itr != m_globalStates.end())
	{
		if ((*itr)->GetGlobalStateType() == stateType)
		{
			return *itr;
		}
	}

	return NULL;
}

void TE::SceneGraph::Spatial::RemoveGlobalState( I32 stateType )
{
	std::list<Memory::Pointer0<GlobalState> >::iterator itr = m_globalStates.begin();

	while(itr != m_globalStates.end())
	{
		if ((*itr)->GetGlobalStateType() == stateType)
		{
			m_globalStates.remove(*itr);
			return;
		}
	}
}

void TE::SceneGraph::Spatial::RemoveAllGlobalStates()
{
	m_globalStates.clear();
}

void TE::SceneGraph::Spatial::UpdateRenderState( std::stack< Memory::Pointer0< GlobalState > >* stateStack, std::vector< Memory::Pointer0< Light > >* lightStack )
{
	bool initiator = stateStack == NULL;

	if(initiator)
	{
		stateStack = new0 std::stack< Memory::Pointer0<GlobalState > >[GlobalState::STATE_COUNT];
		for (unsigned i = 0; i < GlobalState::STATE_COUNT ; i++)
		{
			stateStack[i].push(GlobalState::s_default[i]);
		}
		lightStack = new0 std::vector< Memory::Pointer0<Light > >;

		PropagateStateFromRoot(stateStack, lightStack);
	}
	else
	{
		PushState(stateStack, lightStack);
	}

	UpdateRenderStateLocal(stateStack, lightStack);

	if (initiator)
	{
		delete []stateStack;
		delete lightStack;
	}
	else
	{
		PopState(stateStack, lightStack);
	}
}

void TE::SceneGraph::Spatial::PropagateStateFromRoot( std::stack< Memory::Pointer0< GlobalState > >* stateStack, std::vector< Memory::Pointer0< Light > >* lightStack )
{
	if (m_parent) PropagateStateFromRoot(stateStack, lightStack);

	PushState(stateStack, lightStack);
}

void TE::SceneGraph::Spatial::PushState( std::stack< Memory::Pointer0< GlobalState > >* stateStack, std::vector< Memory::Pointer0< Light > >* lightStack )
{
	std::list<Memory::Pointer0<GlobalState> >::const_iterator lastItr = m_globalStates.end();
	std::list<Memory::Pointer0<GlobalState> >::iterator currentItr = m_globalStates.begin();
	while (currentItr != lastItr)
	{
		I32 type = (*currentItr)->GetGlobalStateType();
		stateStack[type].push(*currentItr);
	}

	lightStack->insert(lightStack->begin(), m_lights.begin(), m_lights.end());
}

void TE::SceneGraph::Spatial::PopState( std::stack< Memory::Pointer0< GlobalState > >* stateStack, std::vector< Memory::Pointer0< Light > >* lightStack )
{
	std::list<Memory::Pointer0<GlobalState> >::iterator stateItr = m_globalStates.begin();
	while (stateItr != m_globalStates.end())
	{
		I32 type = (*stateItr)->GetGlobalStateType();
		stateStack[type].pop();
	}

	std::list<Memory::Pointer0<Light> >::iterator lightItr = m_lights.begin();
	while (lightItr != m_lights.end())
	{
		lightStack->pop_back();
	}
}*/

bool TE::SceneGraph::Spatial::IsCulled( Camera& camera ) const
{
	if(m_forceCull)
		return true;
	
	bool culled = false; 
	unsigned planeState = camera.GetPlaneStateBits();

	if(camera.IsCulled(m_bounding))
		culled = true;

	camera.SetPlaneStateBits(planeState);

	return culled;
}

void TE::SceneGraph::Spatial::SetTranslation( const Math::Vector3D<Real>& translation, bool localTransform)
{
	if (localTransform)
	{
		m_localTransform.SetTranslation(translation);
		//m_worldTransform.SetTranslation(m_parent->m_worldTransform.GetTranslation() + translation);
	}
	else
	{
		assert(false && "Not sure if this should be possible?");
		m_worldTransform.SetTranslation(translation);
		m_localTransform.SetTranslation(translation - m_parent->m_worldTransform.GetTranslation());
	}
	
}

void TE::SceneGraph::Spatial::SetScale( const Math::Vector3D<Real>& scale, bool localTransform )
{
	if (localTransform)
	{
		m_localTransform.SetScale(scale);
		//m_worldTransform.SetScale(m_parent->m_worldTransform.GetScale() + scale);
	}
	else
	{
		assert(false && "Not sure if this should be possible?");
		m_worldTransform.SetScale(scale);
		m_localTransform.SetScale(scale - m_parent->m_worldTransform.GetScale());
	}
}

void TE::SceneGraph::Spatial::SetScale( Real scale, bool localTransform )
{
	if (localTransform)
	{
		m_localTransform.SetScale(scale);
		//m_worldTransform.SetScale(m_parent->m_worldTransform.GetScale() +  Math::Vector3D<Real>(scale, scale, scale));
	}
	else
	{
		assert(false && "Not sure if this should be possible?");
		m_worldTransform.SetScale(scale);
		m_localTransform.SetScale(Math::Vector3D<Real>(scale, scale, scale) - m_parent->m_worldTransform.GetScale());
	}
}

void TE::SceneGraph::Spatial::SetOrientation( const Math::Quaternion<Real>& orientation, bool localTransform )
{
	if (localTransform)
	{
		m_localTransform.SetOrientation(orientation);
		//m_worldTransform.SetOrientation(m_parent->m_worldTransform.GetOrientation() * orientation);
	}
	else
	{
		assert(false && "Not sure if this should be possible?");
		m_worldTransform.SetOrientation(orientation);
		m_localTransform.SetOrientation(orientation*Inverse(m_parent->m_worldTransform.GetOrientation()));
	}
}

const TE::Math::Matrix4D<Real>& TE::SceneGraph::Spatial::GetTransformMatrix()
{
	return m_worldTransform.GetTransformMatrix();
}

