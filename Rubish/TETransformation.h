#ifndef TETRANSFORMATION_H
#define TETRANSFORMATION_H

#include "TEMatrix3D.h"
#include "TEVector3D.h"
#include "..\..\TEngine\inc\TEDefines.h"

namespace TE
{
	namespace Math
	{
		class Transformation
		{
		public:
			//Identity transform
			Transformation() : m_rotation(Matrix3D<Real>::MATRIX3D_IDENTITY), m_translation(Vector3D<Real>::VECTOR3D_ZERO), m_scale(Vector3D<Real>::VECTOR3D_ONE), m_identityTransform(true)
			{}

			//Set all
			Transformation(const Math::Matrix3D<Real>& rotation, const Math::Vector3D<Real>& translation, const Math::Vector3D<Real>& scale) : m_rotation(rotation), m_translation(translation), m_scale(scale), m_identityTransform(false)
			{}

			//Set rotation only
			Transformation(const Math::Matrix3D<Real>& rotation) : m_rotation(rotation), m_translation(Vector3D<Real>::VECTOR3D_ZERO), m_scale(Vector3D<Real>::VECTOR3D_ONE), m_identityTransform(false)
			{}

			//Set translation only
			Transformation(const Math::Vector3D<Real>& translation) : m_rotation(Matrix3D<Real>::MATRIX3D_IDENTITY), m_translation(translation), m_scale(Vector3D<Real>::VECTOR3D_ONE), m_identityTransform(false)
			{}

			//Set rotation and translation
			Transformation(const Math::Matrix3D<Real>& rotation, const Math::Vector3D<Real>& translation) : m_rotation(rotation), m_translation(translation), m_scale(Vector3D<Real>::VECTOR3D_ONE), m_identityTransform(false)
			{}

			void SetRotation(const Math::Matrix3D<Real>& rotation)
			{
				m_rotation = rotation;
				m_identityTransform = false;
			}

			const Math::Matrix3D<Real>& GetRotation()
			{
				return m_rotation;
			}

			void SetTranslation(const Math::Vector3D<Real>& translation)
			{
				m_translation = translation;
				m_identityTransform = false;
			}

			const Math::Vector3D<Real>& GetTranslation()
			{
				return m_translation;
			}

			void SetScale(const Math::Vector3D<Real>& scale)
			{
				m_scale = scale;
				m_identityTransform = false;
			}

			const Math::Vector3D<Real>& GetScale()
			{
				return m_scale;
			}

			bool HasIdentityTransform()
			{
				return m_identityTransform;
			}
		private:
			bool					m_identityTransform;
			Math::Matrix3D<Real>	m_rotation;
			Math::Vector3D<Real>	m_translation;
			Math::Vector3D<Real>	m_scale;
		private:
		};
	}
}

#endif 