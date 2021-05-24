/**
 *	\file		TEMathBase.h
 *  \author		Terje Loe
 *  \brief		Defenitions for templated MathBase class
 */

#ifndef TEMATHBASE_H
#define TEMATHBASE_H

#include <TEDataTypes.h>
#include <assert.h>
#include <cmath>

namespace TE::Math {
    template <typename Real> class Base {
      public:
        inline static const Real InverseSqrt(Real value) {
            assert(value != Math::Base<Real>::REAL_ZERO && "Division by zero in inverseSqrt()\n");
            return 1 / std::sqrt(value);
        }

        inline static const Real Sqrt(Real value) {
            assert(value >= Math::Base<Real>::REAL_ZERO && "Negative input to sqrt()\n");
            return std::sqrt(value);
        }

        inline static const Real Sin(Real value) { return std::sin(value); }

        inline static const Real Cos(Real value) { return std::cos(value); }

        inline static const Real Abs(Real value) { return std::abs(value); }

        inline static const Real Tan(Real value) { return std::tan(value); }

        inline static const Real Atan(Real value0, Real value1) {
            return std::atan2(value0, value1);
        }

        inline static const Real Atan(Real value) { return std::atan(value); }

        inline static const Real Asin(Real value) { return std::asin(value); }

        // Constants
        static const Real EPSILON;
        static const Real ZERO_TOLERANCE;
        static const Real MAX_REAL;
        static const Real PI;
        static const Real PI_OVER_TWO;
        static const Real TWO_PI;
        static const Real HALF_PI;
        static const Real INV_PI;
        static const Real INV_TWO_PI;
        static const Real DEG_TO_RAD;
        static const Real RAD_TO_DEG;
        // static const Real LN_2;
        // static const Real LN_10;
        // static const Real INV_LN_2;
        // static const Real INV_LN_10;
        static const Real SQRT_2;
        static const Real INV_SQRT_2;
        static const Real SQRT_3;
        static const Real INV_SQRT_3;
        static const Real REAL_ZERO;
        static const Real REAL_ONE;
        static const Real REAL_TWO;
        static const Real REAL_HALF;
    };

    template <> inline const F32 Base<F32>::EPSILON        = std::numeric_limits<F32>::epsilon();
    template <> inline const F32 Base<F32>::ZERO_TOLERANCE = 1e-06f;
    template <> inline const F32 Base<F32>::MAX_REAL       = std::numeric_limits<F32>::max();
    template <> inline const F32 Base<F32>::PI             = (F32)(4.0f * atan(1.0f));
    template <> inline const F32 Base<F32>::PI_OVER_TWO    = (F32)Base<F32>::PI / 2;
    template <> inline const F32 Base<F32>::TWO_PI         = 2.0f * Base<F32>::PI;
    template <> inline const F32 Base<F32>::HALF_PI        = 0.5f * Base<F32>::PI;
    template <> inline const F32 Base<F32>::INV_PI         = 1.0f / Base<F32>::PI;
    template <> inline const F32 Base<F32>::INV_TWO_PI     = 1.0f / Base<F32>::TWO_PI;
    template <> inline const F32 Base<F32>::DEG_TO_RAD     = Base<F32>::PI / 180.0f;
    template <> inline const F32 Base<F32>::RAD_TO_DEG     = 180.0f / Base<F32>::PI;
    // template<> inline const F32 Base<F32>::LN_2 = Base<F32>::Log(2.0f);
    // template<> inline const Real Base<F32>::LN_10 = Base<F32>::Log(10.0f);
    // template<> inline const Real Base<F32>::INV_LN_2 = 1.0f/Base<F32>::LN_2;
    // template<> inline const F32 Base<F32>::INV_LN_10 = 1.0f/Base<F32>::LN_10;
    template <> inline const F32 Base<F32>::SQRT_2         = (F32)(sqrt(2.0));
    template <> inline const F32 Base<F32>::INV_SQRT_2     = 1.0f / Base<F32>::SQRT_2;
    template <> inline const F32 Base<F32>::SQRT_3         = (F32)(sqrt(3.0));
    template <> inline const F32 Base<F32>::INV_SQRT_3     = 1.0f / Base<F32>::SQRT_3;
    template <> inline const F32 Base<F32>::REAL_ZERO      = 0.0f;
    template <> inline const F32 Base<F32>::REAL_ONE       = 1.0f;
    template <> inline const F32 Base<F32>::REAL_TWO       = 2.0f;
    template <> inline const F32 Base<F32>::REAL_HALF      = 0.5f;

    template <> inline const F64 Base<F64>::EPSILON        = std::numeric_limits<F64>::epsilon();
    template <> inline const F64 Base<F64>::ZERO_TOLERANCE = 1e-08;
    template <> inline const F64 Base<F64>::MAX_REAL       = std::numeric_limits<F64>::max();
    template <> inline const F64 Base<F64>::PI             = 4.0 * atan(1.0);
    template <> inline const F64 Base<F64>::PI_OVER_TWO    = (F64)Base<F64>::PI / 2;
    template <> inline const F64 Base<F64>::TWO_PI         = 2.0 * Base<F64>::PI;
    template <> inline const F64 Base<F64>::HALF_PI        = 0.5 * Base<F64>::PI;
    template <> inline const F64 Base<F64>::INV_PI         = 1.0 / Base<F64>::PI;
    template <> inline const F64 Base<F64>::INV_TWO_PI     = 1.0 / Base<F64>::TWO_PI;
    template <> inline const F64 Base<F64>::DEG_TO_RAD     = Base<F64>::PI / 180.0;
    template <> inline const F64 Base<F64>::RAD_TO_DEG     = 180.0 / Base<F64>::PI;
    //		template<> inline const F64 Base<F64>::LN_2 = Base<F64>::Log(2.0);
    //		template<> inline const F64 Base<F64>::LN_10 = Base<F64>::Log(10.0);
    //		template<> inline const F64 Base<F64>::INV_LN_2 = 1.0/Base<F64>::LN_2;
    //		template<> inline const F64 Base<F64>::INV_LN_10 = 1.0/Base<F64>::LN_10;
    template <> inline const F64 Base<F64>::SQRT_2         = sqrt(2.0);
    template <> inline const F64 Base<F64>::INV_SQRT_2     = 1.0 / Base<F64>::SQRT_2;
    template <> inline const F64 Base<F64>::SQRT_3         = sqrt(3.0);
    template <> inline const F64 Base<F64>::INV_SQRT_3     = 1.0 / Base<F64>::SQRT_3;
    template <> inline const F64 Base<F64>::REAL_ZERO      = 0.0;
    template <> inline const F64 Base<F64>::REAL_ONE       = 1.0;
    template <> inline const F64 Base<F64>::REAL_TWO       = 2.0;
    template <> inline const F64 Base<F64>::REAL_HALF      = 0.5;
}

#endif
