#include <TELightNode.h>
#include <TELight.h>
#include <TEMatrix3D.h>

TE::SceneGraph::LightNode::LightNode( const Light& light )
	:
	m_light(light)
{
	m_localTransform.SetTranslation(m_light.m_position);
	Math::Matrix3D<Real> rotmat(m_light.m_direction, m_light.m_up, m_light.m_right);
	m_localTransform.SetOrientation(rotmat);
}

TE::SceneGraph::LightNode::~LightNode()
{
}

void TE::SceneGraph::LightNode::SetLight( const Light& light )
{
	m_light = light;
	m_localTransform.SetTranslation(light.m_position);
	Math::Matrix3D<Real> rotmat(light.m_direction, light.m_up, light.m_right);
	m_localTransform.SetOrientation(rotmat);
	Update();
}

TE::SceneGraph::Light& TE::SceneGraph::LightNode::GetLight()
{
	return m_light;
}

void TE::SceneGraph::LightNode::UpdateWorldData()
{
	Node::UpdateWorldData();
	m_light.m_position = m_worldTransform.GetTranslation();
	m_light.m_direction = Rotate(Math::Vector3D<Real>::VECTOR3D_AXIS_Z, m_worldTransform.GetOrientation());
	m_light.m_up = Rotate(Math::Vector3D<Real>::VECTOR3D_AXIS_Y, m_worldTransform.GetOrientation());
	m_light.m_right = Rotate(Math::Vector3D<Real>::VECTOR3D_AXIS_X, m_worldTransform.GetOrientation());
}

