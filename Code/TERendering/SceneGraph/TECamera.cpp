#include <TECamera.h>
#include <TEBSphere.h>
#include <TEPlane.h>
#include <TEMathBase.h>

TE::SceneGraph::Camera::Camera(bool isPerspective)
	:
	m_isPerspective(isPerspective)
{
#if TE_DX11
	m_depthType = DEPTHTYPE_MINUS_ONE_TO_ONE;
#elif TE_OPENGL
	m_depthType = DEPTHTYPE_ZERO_TO_ONE;
#endif
}

void TE::SceneGraph::Camera::SetLocation( const Math::Vector3D<Real>& position )
{
	m_position = position;

	m_viewMatrixUpdated = true;
}

void TE::SceneGraph::Camera::SetOrientation( const Math::Vector3D<Real>& direction, const Math::Vector3D<Real>& up, const Math::Vector3D<Real>& right )
{
	m_direction = direction;
	m_up = up;
	m_right = right;

	const F32 epsilon = 0.01f;
	F32 det = Dot(m_direction, Cross(m_up, m_right));
	if (Math::Base<Real>::Abs(Math::Base<Real>::REAL_ONE - det) > epsilon)
	{
		Orthonormalize(m_direction, m_up, m_right);
	}

	m_viewMatrixUpdated = true;
}

void TE::SceneGraph::Camera::SetOrientation( const Math::Quaternion<Real>& orientation )
{
	m_direction = Math::Rotate(Math::Vector3D<Real>::VECTOR3D_AXIS_Z, orientation);
	m_up = Math::Rotate(Math::Vector3D<Real>::VECTOR3D_AXIS_Y, orientation);
	m_right = Math::Rotate(Math::Vector3D<Real>::VECTOR3D_AXIS_X, orientation);

	m_viewMatrixUpdated = true;
}

// void TE::SceneGraph::Camera::Rotate( const Math::Quaternion<Real>& rotation )
// {
// 	m_direction = Math::Rotate(m_direction, rotation);
// 	m_up = Math::Rotate(m_up, rotation);
// 	m_right = Math::Rotate(m_right, rotation);
// 
// 	m_updated = true;
// }

const TE::Math::Matrix4D<Real>& TE::SceneGraph::Camera::GetViewMatrix()
{
	if (m_viewMatrixUpdated)
	{
		m_viewMatrix(0,0) = m_right.x;
		m_viewMatrix(0,1) = m_right.y;
		m_viewMatrix(0,2) = m_right.z;
		m_viewMatrix(0,3) = Math::Base<Real>::REAL_ZERO;
		m_viewMatrix(1,0) = m_up.x;
		m_viewMatrix(1,1) = m_up.y;
		m_viewMatrix(1,2) = m_up.z;
		m_viewMatrix(1,3) = Math::Base<Real>::REAL_ZERO;
		m_viewMatrix(2,0) = m_direction.x;
		m_viewMatrix(2,1) = m_direction.y;
		m_viewMatrix(2,2) = m_direction.z;
		m_viewMatrix(2,3) = Math::Base<Real>::REAL_ZERO;
		m_viewMatrix(3,0) = -Dot(m_position,m_right);
		m_viewMatrix(3,1) = -Dot(m_position, m_up);
		m_viewMatrix(3,2) = -Dot(m_position, m_direction);
		m_viewMatrix(3,3) = Math::Base<Real>::REAL_ONE;
		m_viewMatrixUpdated = false;
	}

	return m_viewMatrix;
}

const TE::Math::Matrix4D<Real>& TE::SceneGraph::Camera::GetProjectionMatrix()
{
	F32 invDDiff = 1.0f/(m_directionMax - m_directionMin);
	F32 invUDiff = 1.0f/(m_upMax - m_upMin);
	F32 invRDiff = 1.0f/(m_rightMax - m_rightMin);
	F32 sumRMinRMaxInvRDiff = (m_rightMin + m_rightMax)*invRDiff;
	F32 sumUMinUMaxInvUDiff = (m_upMin + m_upMax)*invUDiff;
	F32 sumDMinDMaxInvDDiff = (m_directionMin + m_directionMax)*invDDiff;

	if (m_projectionMatrixUpdated)
	{
		if (m_isPerspective)
		{
			//Calculate perspective projection matrix
			F32 twoDMinInvRDiff = 2.0f*m_directionMin*invRDiff;
			F32 twoDMinInvUDiff = 2.0f*m_directionMin*invUDiff;
			F32 dMaxInvDDiff = m_directionMax*invDDiff;
			F32 dMinDMaxInvDDiff = m_directionMin*dMaxInvDDiff;
			F32 twoDMinDMaxInvDDiff = 2.0f*dMinDMaxInvDDiff;

			if (m_depthType == DEPTHTYPE_ZERO_TO_ONE)
			{
				// Map (x,y,z) into [-1,1]x[-1,1]x[0,1].
				m_projectionMatrix(0,0) = twoDMinInvRDiff;
				m_projectionMatrix(0,1) = 0.0f;
				m_projectionMatrix(0,2) = -sumRMinRMaxInvRDiff;
				m_projectionMatrix(0,3) = 0.0f;
				m_projectionMatrix(1,0) = 0.0f;
				m_projectionMatrix(1,1) = twoDMinInvUDiff;
				m_projectionMatrix(1,2) = -sumUMinUMaxInvUDiff;
				m_projectionMatrix(1,3) = 0.0f;
				m_projectionMatrix(2,0) = 0.0f;
				m_projectionMatrix(2,1) = 0.0f;
				m_projectionMatrix(2,2) = dMaxInvDDiff;
				m_projectionMatrix(2,3) = 1.0;
				m_projectionMatrix(3,0) = 0.0f;
				m_projectionMatrix(3,1) = 0.0f;
				m_projectionMatrix(3,2) = -dMinDMaxInvDDiff;
				m_projectionMatrix(3,3) = 0.0f;
			}
			else
			{
				// Map (x,y,z) into [-1,1]x[-1,1]x[-1,1].
				m_projectionMatrix(0,0) = twoDMinInvRDiff;
				m_projectionMatrix(0,1) = 0.0f;
				m_projectionMatrix(0,2) = -sumRMinRMaxInvRDiff;
				m_projectionMatrix(0,3) = 0.0f;
				m_projectionMatrix(1,0) = 0.0f;
				m_projectionMatrix(1,1) = twoDMinInvUDiff;
				m_projectionMatrix(1,2) = -sumUMinUMaxInvUDiff;
				m_projectionMatrix(1,3) = 0.0f;
				m_projectionMatrix(2,0) = 0.0f;
				m_projectionMatrix(2,1) = 0.0f;
				m_projectionMatrix(2,2) = sumDMinDMaxInvDDiff;
				m_projectionMatrix(2,3) = 1.0f;
				m_projectionMatrix(3,0) = 0.0f;
				m_projectionMatrix(3,1) = 0.0f;
				m_projectionMatrix(3,2) = -twoDMinDMaxInvDDiff;
				m_projectionMatrix(3,3) = 0.0f;
			}
		}
		else
		{
			//Calculate orthogonal projection matrix
			F32 twoInvRDiff = 2.0f*invRDiff;
			F32 twoInvUDiff = 2.0f*invUDiff;
			F32 twoInvDDiff = 2.0f*invDDiff;
			F32 dMinInvDDiff = m_directionMin*invDDiff;

			if (m_depthType == DEPTHTYPE_ZERO_TO_ONE)
			{
				// Map (x,y,z) into [-1,1]x[-1,1]x[0,1].
				m_projectionMatrix(0,0) = twoInvRDiff;
				m_projectionMatrix(0,1) = 0.0f;
				m_projectionMatrix(0,2) = 0.0f;
				m_projectionMatrix(0,3) = 0.0f;
				m_projectionMatrix(1,0) = 0.0f;
				m_projectionMatrix(1,1) = twoInvUDiff;
				m_projectionMatrix(1,2) = 0.0f;
				m_projectionMatrix(1,3) = 0.0f;
				m_projectionMatrix(2,0) = 0.0f;
				m_projectionMatrix(2,1) = 0.0f;
				m_projectionMatrix(2,2) = invDDiff;
				m_projectionMatrix(2,3) = 0.0f;
				m_projectionMatrix(3,0) = -sumRMinRMaxInvRDiff;
				m_projectionMatrix(3,1) = -sumUMinUMaxInvUDiff;
				m_projectionMatrix(3,2) = -dMinInvDDiff;
				m_projectionMatrix(3,3) = 1.0f;
			}
			else
			{
				// Map (x,y,z) into [-1,1]x[-1,1]x[-1,1].
				m_projectionMatrix(0,0) = twoInvRDiff;
				m_projectionMatrix(0,1) = 0.0f;
				m_projectionMatrix(0,2) = 0.0f;
				m_projectionMatrix(0,3) = 0.0f;
				m_projectionMatrix(1,0) = 0.0f;
				m_projectionMatrix(1,1) = twoInvUDiff;
				m_projectionMatrix(1,2) = 0.0f;
				m_projectionMatrix(1,3) = 0.0f;
				m_projectionMatrix(2,0) = 0.0f;
				m_projectionMatrix(2,1) = 0.0f;
				m_projectionMatrix(2,2) = twoInvDDiff;
				m_projectionMatrix(2,3) = 0.0f;
				m_projectionMatrix(3,0) = -sumRMinRMaxInvRDiff;
				m_projectionMatrix(3,1) = -sumUMinUMaxInvUDiff;
				m_projectionMatrix(3,2) = -sumDMinDMaxInvDDiff;
				m_projectionMatrix(3,3) = 1.0f;
			}
		}

		m_projectionMatrixUpdated = false;
	}

	return m_projectionMatrix;
}

const TE::Math::Vector3D<Real>& TE::SceneGraph::Camera::GetPosition() const
{
	return m_position;
}

const TE::Math::Vector3D<Real>& TE::SceneGraph::Camera::GetDirection() const
{
	return m_direction;
}

const TE::Math::Vector3D<Real>& TE::SceneGraph::Camera::GetUp() const
{
	return m_up;
}

const TE::Math::Vector3D<Real>& TE::SceneGraph::Camera::GetRight() const
{
	return m_right;
}

Real TE::SceneGraph::Camera::GetDirectionMin() const
{
	return m_directionMin;
}

Real TE::SceneGraph::Camera::GetDirectionMax() const
{
	return m_directionMax;
}

Real TE::SceneGraph::Camera::GetUpMin() const
{
	return m_upMin;
}

Real TE::SceneGraph::Camera::GetUpMax() const
{
	return m_upMax;
}

Real TE::SceneGraph::Camera::GetRightMin() const
{
	return m_rightMin;
}

Real TE::SceneGraph::Camera::GetRightMax() const
{
	return m_rightMax;
}

void TE::SceneGraph::Camera::SetFrustrum( Real rightMin, Real rightMax, Real upMin, Real upMax, Real directionMin, Real directionMax )
{
	m_rightMin = rightMin;
	m_rightMax = rightMax;
	m_upMin = upMin;
	m_upMax = upMax;
	m_directionMin = directionMin;
	m_directionMax = directionMax;

	m_projectionMatrixUpdated = true;
}

void TE::SceneGraph::Camera::SetFrustrum( Real upFovRadians, Real aspectRatio, Real directionMin, Real directionMax )
{
	m_directionMin = directionMin;
	m_directionMax = directionMax;
	m_upFovRadians = upFovRadians;

	Real halfAngleRadians = Math::Base<Real>::REAL_HALF*upFovRadians;
	m_upMax = m_directionMin*Math::Base<Real>::Tan(halfAngleRadians);
	m_rightMax = aspectRatio*m_upMax;
	m_upMin = -m_upMax;
	m_rightMin = -m_rightMax;


	m_projectionMatrixUpdated = true;
}

void TE::SceneGraph::Camera::GetFrustrum( Real& rightMin, Real& rightMax, Real& upMin, Real& upMax, Real& directionMin, Real& directionMax ) const
{
	rightMin = m_rightMin;
	rightMax = m_rightMax;
	upMin = m_upMin;
	upMax = m_upMax;
	directionMin = m_directionMin;
	directionMax = m_directionMax;
}

bool TE::SceneGraph::Camera::GetSymetricFrustrum( Real& upFovDegrees, Real& aspectRatio, Real& directionMin, Real& directionMax ) const
{
	if (m_rightMin == -m_rightMax && m_upMin == -m_upMax)
	{
		F32 tmp = m_upMax/m_directionMin;
		upFovDegrees = Math::Base<Real>::REAL_TWO * Math::Base<Real>::Atan(tmp) * Math::Base<Real>::RAD_TO_DEG;
		aspectRatio = m_rightMax/m_upMax;
		directionMin = m_directionMin;
		directionMax = m_directionMax;
		return true;
	}
	return false;
}

const TE::Math::Matrix4D<Real>& TE::SceneGraph::Camera::GetViewProjectionMatrix()
{
	if (m_viewMatrixUpdated || m_projectionMatrixUpdated)
	{
		m_projViewMatrix = GetViewMatrix() * GetProjectionMatrix();
	}

	return m_projViewMatrix;
}

void TE::SceneGraph::Camera::SetViewPort( Real left, Real right, Real top, Real bottom )
{
	m_viewPortLeft = left;
	m_viewPortRight = right;
	m_viewPortTop = top;
	m_viewPortBottom = bottom;

	//Set renderer 
}

void TE::SceneGraph::Camera::GetViewPort( Real& left, Real& right, Real& top, Real& bottom ) const
{
	left = m_viewPortLeft;
	right = m_viewPortRight;
	top = m_viewPortTop;
	bottom = m_viewPortBottom;
}

unsigned TE::SceneGraph::Camera::GetPlaneStateBits() const
{
	return m_planeStateBits;
}

void TE::SceneGraph::Camera::SetPlaneStateBits( unsigned planeStateBits )
{
	m_planeStateBits = planeStateBits;
}

bool TE::SceneGraph::Camera::IsCulled( Intersection::BSphere bounding )
{
	unsigned countMinusOne = m_cullingPlanes.size() - 1;
	unsigned stateMask = 1 << countMinusOne;

	for (I32 i = countMinusOne; i >= 0; --i, stateMask >>=1)
	{
		if(m_planeStateBits & stateMask)
		{
			I32 side = WhichSide(m_cullingPlanes[i],bounding);
			if(side < 0) return true;
			//Object is on positive side of plane, there is no need to check
			//sub-spatial objects to this plane
			if(side > 0) m_planeStateBits &= ~stateMask;
		}
	}

	return false;
}

const std::vector<TE::Intersection::Plane> TE::SceneGraph::Camera::GetPlanes() const
{
	return m_cullingPlanes;
}

void TE::SceneGraph::Camera::PushPlane( const Intersection::Plane& plane )
{
	assert(m_cullingPlanes.size() < CAMERAPLANES_WORLD_MAX && "Too many planes added to camera");
	m_cullingPlanes.push_back(plane);
}

void TE::SceneGraph::Camera::PopPlane()
{
	m_cullingPlanes.pop_back();
}

void TE::SceneGraph::Camera::SetDepthType( I32 depthType )
{
	m_depthType = depthType;
	m_projectionMatrixUpdated = true;
}
