#include <TENode.h>
#include <functional>
#include <algorithm>
#include "TECamera.h"

TE::SceneGraph::Node::Node()
{

}

TE::SceneGraph::Node::~Node()
{

}

void TE::SceneGraph::Node::AddChild( Spatial& child )
{
	m_children.push_back(&child);
}

void TE::SceneGraph::Node::RemoveChild( Spatial& child )
{
    m_children.remove(&child);
}

void TE::SceneGraph::Node::RemoveFromParrent()
{

}

void TE::SceneGraph::Node::GetRenderListNoCull( RenderablePtrList& renderList )
{
    std::for_each(m_children.begin(), m_children.end(),
                  [&renderList](Spatial* spatial){ spatial->GetRenderListNoCull(renderList); });

    /*std::for_each(m_children.begin(),
                  m_children.end(),
                  std::bind(&Spatial::GetRenderListNoCull, std::placeholders::_1, std::ref(renderList)));*/
}

void TE::SceneGraph::Node::GetRenderListNoSort( RenderablePtrList& renderList, Camera& camera )
{
	if (!IsCulled(camera))
	{
		std::for_each(m_children.begin(),
					  m_children.end(),
					  std::bind(&Spatial::GetRenderListNoSort, std::placeholders::_1,
							    std::ref(renderList), std::ref(camera)));
	}
}

void TE::SceneGraph::Node::UpdateWorldData()
{
	Spatial::UpdateWorldData();

	std::for_each(m_children.begin(),
				  m_children.end(),
				  std::bind(&Spatial::Update, std::placeholders::_1,
				  false));
}

void TE::SceneGraph::Node::UpdateWorldBound()
{
	if (!m_worldBoundIsCurrent && m_children.size())
	{
		SpatialPtrList::iterator current = m_children.begin();
		SpatialPtrList::const_iterator last = m_children.end();
		
		m_bounding = (*current)->GetBounding();
		for(++current ;current != last; ++current)
		{
			Grow(m_bounding, (*current)->GetBounding());
		}
	}
}
/*
void TE::SceneGraph::Node::UpdateRenderStateLocal( std::stack< Memory::Pointer0< GlobalState > >* stateStack, std::vector< Memory::Pointer0< Light > >* lightStack )
{
	SpatialPtrList::iterator current = m_children.begin();
	SpatialPtrList::const_iterator last = m_children.end();

	while(current != last)
	{
		(*current)->UpdateRenderState(stateStack, lightStack);
		++current;
	}
}*/
