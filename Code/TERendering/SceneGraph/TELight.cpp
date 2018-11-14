#include <TELight.h>

void TE::SceneGraph::SetLightDirection(Light& light, const Math::Vector3D<Real>& direction)
{
	light.m_direction = direction;
	CreateOrthonormalBasis(light.m_right, light.m_up, light.m_direction);
}