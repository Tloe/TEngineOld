#include <TECameraNode.h>
#include <TEMatrix3D.h>

TE::SceneGraph::CameraNode::CameraNode(Camera &camera)
    : m_camera(camera) {
    UpdateLocalTransformFromCamera(camera);
}

TE::SceneGraph::CameraNode::~CameraNode() {
}

void TE::SceneGraph::CameraNode::SetCameraRef(Camera &camera) {
    m_camera = camera;

    UpdateLocalTransformFromCamera(camera);
    Update();
}

TE::SceneGraph::Camera &TE::SceneGraph::CameraNode::GetCamera() const {
    return m_camera;
}

void TE::SceneGraph::CameraNode::UpdateWorldData() {
    Node::UpdateWorldData();

    Math::Vector3D<Real> position  = m_worldTransform.GetTranslation();
    Math::Vector3D<Real> direction = Rotate(Math::Vector3D<Real>::VECTOR3D_AXIS_Z, m_worldTransform.GetOrientation());
    Math::Vector3D<Real> up        = Rotate(Math::Vector3D<Real>::VECTOR3D_AXIS_Y, m_worldTransform.GetOrientation());
    Math::Vector3D<Real> right     = Rotate(Math::Vector3D<Real>::VECTOR3D_AXIS_X, m_worldTransform.GetOrientation());

    m_camera.SetLocation(position);
    m_camera.SetOrientation(direction, up, right);
}

void TE::SceneGraph::CameraNode::UpdateLocalTransformFromCamera(const Camera &camera) {
    m_localTransform.SetTranslation(m_camera.GetPosition());
    Math::Matrix3D<Real> rotmat(m_camera.GetDirection(), m_camera.GetUp(), m_camera.GetRight());
    m_localTransform.SetOrientation(rotmat);
}
