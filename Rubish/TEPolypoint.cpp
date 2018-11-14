#include <TEPolypoint.h>

TE::SceneGraph::Polypoint::Polypoint( float* vertices )
	: 
	Renderable(PT_POLYPOINTS)
{

}

void TE::SceneGraph::Polypoint::SetActiveCount( int activeCount )
{
	m_activeCount = activeCount;
}

int TE::SceneGraph::Polypoint::GetActiveCount()
{
	return m_activeCount;
}
