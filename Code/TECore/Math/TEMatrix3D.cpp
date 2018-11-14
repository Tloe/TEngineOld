#include <TEMatrix3D.h>

template <> const TE::Math::Matrix3D<F32> TE::Math::Matrix3D<F32>::MATRIX3D_ZERO(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
template <> const TE::Math::Matrix3D<F64> TE::Math::Matrix3D<F64>::MATRIX3D_ZERO(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

template <> const TE::Math::Matrix3D<F32> TE::Math::Matrix3D<F32>::MATRIX3D_IDENTITY(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
template <> const TE::Math::Matrix3D<F64> TE::Math::Matrix3D<F64>::MATRIX3D_IDENTITY(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);