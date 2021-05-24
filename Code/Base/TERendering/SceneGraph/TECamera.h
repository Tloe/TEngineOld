#ifndef TECAMERA_H
#define TECAMERA_H

#include <TEMatrix4D.h>
#include <TEPlane.h>
#include <TEQuaternion.h>
#include <TEVector3D.h>
#include <vector>

namespace TE::Intersection {
  struct BSphere;
}

namespace TE::SceneGraph {
  class Camera {
  public:
    enum {
      // Zero to one is typicaly used for ogl, minus one to one is used for D3D
      DEPTHTYPE_ZERO_TO_ONE,
      DEPTHTYPE_MINUS_ONE_TO_ONE,
      DEPTHTYPE_COUNT
    };

    enum { CAMERAPLANES_FRUSTRUM = 6, CAMERAPLANES_WORLD_MAX = 32 };

    Camera(bool isPerspective = true);

    void SetDepthType(I32 depthType);

    void SetLocation(const Math::Vector3D<Real> &position);

    void SetOrientation(const Math::Vector3D<Real> &direction,
                        const Math::Vector3D<Real> &up,
                        const Math::Vector3D<Real> &right);

    void SetOrientation(const Math::Quaternion<Real> &orientation);

    // void Rotate(const Math::Quaternion<Real>& Rotation);

    void SetFrustrum(Real rightMin,
                     Real rightMax,
                     Real upMin,
                     Real upMax,
                     Real directionMin,
                     Real directionMax);

    void SetFrustrum(Real upFovDegrees, Real aspectRatio, Real directionMin, Real directionMax);

    void SetViewPort(Real left, Real right, Real top, Real bottom);
    void GetViewPort(Real &left, Real &right, Real &top, Real &bottom) const;

    void GetFrustrum(Real &rightMin,
                     Real &rightMax,
                     Real &upMin,
                     Real &upMax,
                     Real &directionMin,
                     Real &directionMax) const;

    bool GetSymetricFrustrum(Real &upFovDegrees,
                             Real &aspectRatio,
                             Real &directionMin,
                             Real &directionMax) const;

    const Math::Matrix4D<Real> &GetViewMatrix();
    const Math::Matrix4D<Real> &GetProjectionMatrix();
    const Math::Matrix4D<Real> &GetViewProjectionMatrix();

    const Math::Vector3D<Real> &GetPosition() const;

    const Math::Vector3D<Real> &GetDirection() const;

    const Math::Vector3D<Real> &GetUp() const;

    const Math::Vector3D<Real> &GetRight() const;

    Real GetDirectionMin() const;

    Real GetDirectionMax() const;

    Real GetUpMin() const;

    Real GetUpMax() const;

    Real GetRightMin() const;

    Real GetRightMax() const;

    unsigned GetPlaneStateBits() const;
    void SetPlaneStateBits(unsigned planeState);
    bool IsCulled(Intersection::BSphere bounding);
    const std::vector<Intersection::Plane> GetPlanes() const;
    void PushPlane(const Intersection::Plane &plane);
    void PopPlane();

  private:
    I32 m_depthType;

    Math::Vector3D<Real> m_position;
    Math::Vector3D<Real> m_direction;
    Math::Vector3D<Real> m_up;
    Math::Vector3D<Real> m_right;

    Real m_upFovRadians;
    Real m_directionMin;
    Real m_directionMax;
    Real m_upMin;
    Real m_upMax;
    Real m_rightMin;
    Real m_rightMax;

    Real m_viewPortLeft;
    Real m_viewPortRight;
    Real m_viewPortTop;
    Real m_viewPortBottom;

    Math::Matrix4D<Real> m_viewMatrix;
    Math::Matrix4D<Real> m_projectionMatrix;
    Math::Matrix4D<Real> m_projViewMatrix;

    bool m_viewMatrixUpdated;
    bool m_projectionMatrixUpdated;

    bool m_isPerspective;

    unsigned m_planeStateBits;
    std::vector<Intersection::Plane> m_cullingPlanes;
  };
}

#endif
