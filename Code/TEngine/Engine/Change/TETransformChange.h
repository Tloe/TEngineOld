#ifndef TETRANSFORMCHANGE_H
#define TETRANSFORMCHANGE_H

#include "TESystemObject.h"
#include "TEVector3D.h"
#include "TEQuaternion.h"

namespace TE
{
	namespace Engine
	{
		class TransformChange
		{
		public:
            virtual Math::Vector3D<F32> GetPosition(){ assert(false); return Math::Vector3D<F32>::VECTOR3D_ZERO; }
            virtual Math::Vector3D<F32> GetTranslation(){ assert(false); return Math::Vector3D<F32>::VECTOR3D_ZERO; }
            virtual Math::Quaternion<F32> GetOrientation(){ assert(false); return Math::Quaternion<F32>::QUATERNION_IDENTITY; }
            virtual Math::Quaternion<F32> GetRotation(){ assert(false); return Math::Quaternion<F32>::QUATERNION_IDENTITY; }
            virtual Math::Vector3D<F32> GetScale(){ assert(false); return Math::Vector3D<F32>::VECTOR3D_ZERO; }
            virtual Math::Vector3D<F32> GetScaleDelta(){ assert(false); return Math::Vector3D<F32>::VECTOR3D_ZERO; }
		};
	}
}

#endif
