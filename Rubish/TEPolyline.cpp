#include <TEPolyline.h>

TE::SceneGraph::Polyline::Polyline( float* vertices, bool closed, bool contiguous ) : m_closed(closed), m_contigous(contiguous)
{
	UpdatePrimitiveType();
}

TE::SceneGraph::Polyline::~Polyline()
{

}

void TE::SceneGraph::Polyline::SetActiveCount( int activeCount )
{
	m_activeCount = activeCount;
}

int TE::SceneGraph::Polyline::GetActiveCount()
{
	return m_activeCount;
}

void TE::SceneGraph::Polyline::SetClosed( bool closed )
{
	m_closed;
	UpdatePrimitiveType();
}

bool TE::SceneGraph::Polyline::GetClosed()
{
	return m_closed;
}

void TE::SceneGraph::Polyline::SetContigous( bool contigous )
{
	m_contigous = contigous;
	UpdatePrimitiveType();
}

bool TE::SceneGraph::Polyline::GetContigous()
{
	return m_contigous;
}

void TE::SceneGraph::Polyline::UpdatePrimitiveType()
{
	if (m_contigous)
	{
		if(m_closed)
			m_primitiveType = PT_POLYLINE_CLOSED;
		else
			m_primitiveType = PT_POLYLINE_OPEN;
	}
	else
	{
		m_primitiveType = PT_POLYLINE_SEGMENTS;
	}
}