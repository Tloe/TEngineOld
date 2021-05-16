#ifndef TETRANSFORM_H
#define TETRANSFORM_H

#include <TEHelpers.h>
#include <TEMatrix4D.h>
#include <TEQuaternion.h>
#include <TEVector3D.h>

namespace TE {
namespace Math {
    template <typename Real>
    class Transform {
      public:
        Transform() : m_transformNeedsUpdate(false),
                      m_isScaled(false) {
            SetIdentity();
        }

        /*
        const Transform& operator=(const Transform& rhs)
        {
                if (this == &rhs) return this;

                this->m_translation = rhs.m_translation;
                this->m_scale = rhs.m_scale;
                this->m_orientation = rhs.m_orientation;
        }*/

        const Matrix4D<Real> &GetTransformMatrix() {
            if (m_transformNeedsUpdate)
                UpdateTransformMatrix();

            return m_transform;
        }

        void SetIdentity() {
            m_isIdentity  = true;
            m_scaleChange = m_orientationChange = m_translationChange = m_transformNeedsUpdate = false;
            m_isScaled                                                                         = false;
            m_translation                                                                      = Vector3D<Real>::VECTOR3D_ZERO;
            m_scale                                                                            = Vector3D<Real>::VECTOR3D_ONE;
            m_orientation                                                                      = Quaternion<Real>::QUATERNION_IDENTITY;
            UpdateTransformMatrix();
        }

        const Vector3D<Real> &GetTranslation() {
            return m_translation;
        }

        const Quaternion<Real> &GetOrientation() {
            return m_orientation;
        }

        const Matrix3D<Real> GetOrientationMatrix() {
            // Prefer using the quaternion version, its cheaper!
            m_orientation.GetRotationMatrix();
        }

        const Vector3D<Real> &GetScale() {
            return m_scale;
        }

        void SetTranslation(const Vector3D<Real> &position) {
            m_translationChange = m_transformNeedsUpdate = true;
            m_isIdentity                                 = false;
            m_translation                                = position;
        }

        void SetOrientation(const Matrix3D<Real> &orientation) {
            // Prefer using the quaternion version, its cheaper!
            m_orientationChange = m_transformNeedsUpdate = true;
            m_isIdentity                                 = false;
            m_orientation.SetRotationMatrix(orientation);
        }

        void SetOrientation(const Quaternion<Real> &orientation) {
            m_orientationChange = m_transformNeedsUpdate = true;
            m_isIdentity                                 = false;
            m_orientation                                = orientation;
        }

        void SetScale(const Vector3D<Real> &scale) {
            m_isScaled = m_transformNeedsUpdate = true;
            m_isIdentity                        = false;
            m_scale                             = scale;
        }

        void SetScale(F32 scale) {
            m_isScaled = m_scaleChange = m_transformNeedsUpdate = true;
            m_isIdentity                                        = false;
            m_scale.x = m_scale.y = m_scale.z = scale;
        }

        void Translate(const Vector3D<Real> &translation) {
            m_translationChange = m_transformNeedsUpdate = true;
            m_isIdentity                                 = false;
            m_translation += translation;
        }

        void Rotate(const Quaternion<Real> &rotation) {
            m_orientationChange = m_transformNeedsUpdate = true;
            m_isIdentity                                 = false;
            m_orientation *= rotation;
        }

        void Rotate(const Matrix3D<Real> &rotation) {
            // Prefer using the quaternion version, its cheaper!
            m_orientationChange = m_transformNeedsUpdate = true;
            m_isIdentity                                 = false;
            Quaternion<Real> quatRotation;
            quatRotation.SetRotationMatrix(rotation);
            m_orientation *= rotation;
        }

        void Scale(const Vector3D<Real> &scale) {
            // orientation change flag set as it is needed for the correct update
            m_isScaled = m_scaleChange = m_transformNeedsUpdate = true;
            m_isIdentity                                        = false;
            m_scale += scale;
        }

        void Scale(F32 scale) {
            // orientation change flag set as it is needed for the correct update
            m_isScaled = m_scaleChange = m_transformNeedsUpdate = true;
            m_isIdentity                                        = false;
            m_scale.x += scale;
            m_scale.y += scale;
            m_scale.z += scale;
        }

        bool HasScaleChange() {
            return m_scaleChange;
        }

        bool HasTranslationChange() {
            return m_translationChange;
        }

        bool HasOrientationChange() {
            return m_orientationChange;
        }

        bool HasChange() {
            return m_scaleChange || m_translationChange || m_orientationChange;
        }

      private:
        void UpdateScale() {
            m_transform(0, 0) *= m_scale[0];
            m_transform(0, 1) *= m_scale[1];
            m_transform(0, 2) *= m_scale[2];

            m_transform(1, 0) *= m_scale[0];
            m_transform(1, 1) *= m_scale[1];
            m_transform(1, 2) *= m_scale[2];

            m_transform(2, 0) *= m_scale[0];
            m_transform(2, 1) *= m_scale[1];
            m_transform(2, 2) *= m_scale[2];
        }

        void UpdateOrientation() {
            m_transform(0, 0) = 1 - (2 * m_orientation.y * m_orientation.y) - (2 * m_orientation.z * m_orientation.z);
            m_transform(0, 1) = (2 * m_orientation.x * m_orientation.y) - (2 * m_orientation.z * m_orientation.w);
            m_transform(0, 2) = (2 * m_orientation.x * m_orientation.z) + (2 * m_orientation.y * m_orientation.w);

            m_transform(1, 0) = (2 * m_orientation.x * m_orientation.y) + (2 * m_orientation.z * m_orientation.w);
            m_transform(1, 1) = 1 - (2 * m_orientation.x * m_orientation.x) - (2 * m_orientation.z * m_orientation.z);
            m_transform(1, 2) = (2 * m_orientation.y * m_orientation.z) - (2 * m_orientation.x * m_orientation.w);

            m_transform(2, 0) = (2 * m_orientation.x * m_orientation.z) - (2 * m_orientation.y * m_orientation.w);
            m_transform(2, 1) = (2 * m_orientation.y * m_orientation.z) + (2 * m_orientation.x * m_orientation.w);
            m_transform(2, 2) = 1 - (2 * m_orientation.x * m_orientation.x) - (2 * m_orientation.y * m_orientation.y);
        }

        void UpdateTransformMatrix() {
            if (m_isIdentity) {
                m_transform.SetIdentity();
            } else {
                if (m_orientationChange) {
                    if (m_scaleChange || m_isScaled) {
                        UpdateOrientation();
                        UpdateScale();
                    } else {
                        UpdateOrientation();
                    }
                } else if (m_scaleChange) // && !m_orientationChange
                {
                    UpdateScale();
                }

                if (m_translationChange) {
                    m_transform(3, 0) = m_translation.x;
                    m_transform(3, 1) = m_translation.y;
                    m_transform(3, 2) = m_translation.z;
                }
            }

            m_transformNeedsUpdate = m_scaleChange = m_translationChange = m_orientationChange = false;
        }

        bool m_transformNeedsUpdate;
        bool m_isIdentity;
        bool m_translationChange;
        bool m_orientationChange;
        bool m_scaleChange;
        bool m_isScaled;

        Vector3D<Real> m_translation;
        Vector3D<Real> m_scale;
        Quaternion<Real> m_orientation;
        Matrix4D<Real> m_transform;
    };
}
}

#endif