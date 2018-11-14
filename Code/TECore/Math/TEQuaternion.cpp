#include <TEQuaternion.h>

template <> const TE::Math::Quaternion<F32> TE::Math::Quaternion<F32>::QUATERNION_IDENTITY(0.0f, 0.0f, 0.0f, 1.0);
template <> const TE::Math::Quaternion<F64> TE::Math::Quaternion<F64>::QUATERNION_IDENTITY(0.0, 0.0, 0.0, 1.0);

template <> const TE::Math::Quaternion<F32> TE::Math::Quaternion<F32>::QUATERNION_INVALID(0.0f, 0.0f, 0.0f, 0.0);
template <> const TE::Math::Quaternion<F64> TE::Math::Quaternion<F64>::QUATERNION_INVALID(0.0, 0.0, 0.0, 0.0);