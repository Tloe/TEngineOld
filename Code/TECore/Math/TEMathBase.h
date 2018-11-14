/**
 *	\file		TEMathBase.h
 *  \author		Terje Loe
 *  \brief		Defenitions for templated MathBase class
 */


#ifndef TEMATHBASE_H
#define TEMATHBASE_H

#include <assert.h>
#include <TEDataTypes.h>
#include <cmath>

namespace TE
{
	namespace Math
	{
		template<typename Real>
		class Base
		{
		public:
			inline static const Real InverseSqrt(Real value)
			{
				assert(value != Math::Base<Real>::REAL_ZERO && "Division by zero in inverseSqrt()\n");
				return 1/std::sqrt(value);
			}

			inline static const Real Sqrt(Real value)
			{
				assert(value >= Math::Base<Real>::REAL_ZERO && "Negative input to sqrt()\n");
				return std::sqrt(value);
			}

			inline static const Real Sin(Real value)
			{
				return std::sin(value);
			}
			
			inline static const Real Cos(Real value)
			{
				return std::cos(value);
			}

			inline static const Real Abs(Real value)
			{
				return std::abs(value);
			}

			inline static const Real Tan(Real value)
			{
				return std::tan(value);
			}

			inline static const Real Atan(Real value0, Real value1)
			{
				return std::atan2(value0,value1);
			}

			inline static const Real Atan(Real value)
			{
				return std::atan(value);
			}

			inline static const Real Asin(Real value)
			{
				return std::asin(value);
			}

			//Constants
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
			//static const Real LN_2;
			//static const Real LN_10;
			//static const Real INV_LN_2;
			//static const Real INV_LN_10;
			static const Real SQRT_2;
			static const Real INV_SQRT_2;
			static const Real SQRT_3;
			static const Real INV_SQRT_3;
			static const Real REAL_ZERO;
			static const Real REAL_ONE;
			static const Real REAL_TWO;
			static const Real REAL_HALF;
		};
	}
}

#endif
