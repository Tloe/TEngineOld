#include <TEMathBase.h>
#include <float.h>
#include <limits>

namespace TE
{
	namespace Math
	{
		template<> const F32 Base<F32>::EPSILON = std::numeric_limits<F32>::epsilon();
		template<> const F32 Base<F32>::ZERO_TOLERANCE = 1e-06f;
		template<> const F32 Base<F32>::MAX_REAL = std::numeric_limits<F32>::max();
		template<> const F32 Base<F32>::PI = (F32)(4.0f*atan(1.0f));
		template<> const F32 Base<F32>::PI_OVER_TWO = (F32)Base<F32>::PI/2;
		template<> const F32 Base<F32>::TWO_PI = 2.0f*Base<F32>::PI;
		template<> const F32 Base<F32>::HALF_PI = 0.5f*Base<F32>::PI;
		template<> const F32 Base<F32>::INV_PI = 1.0f/Base<F32>::PI;
		template<> const F32 Base<F32>::INV_TWO_PI = 1.0f/Base<F32>::TWO_PI;
		template<> const F32 Base<F32>::DEG_TO_RAD = Base<F32>::PI/180.0f;
		template<> const F32 Base<F32>::RAD_TO_DEG = 180.0f/Base<F32>::PI;
		//template<> const F32 Base<F32>::LN_2 = Base<F32>::Log(2.0f);
		//template<> const Real Base<F32>::LN_10 = Base<F32>::Log(10.0f);
		//template<> const Real Base<F32>::INV_LN_2 = 1.0f/Base<F32>::LN_2;
		//template<> const F32 Base<F32>::INV_LN_10 = 1.0f/Base<F32>::LN_10;
		template<> const F32 Base<F32>::SQRT_2 = (F32)(sqrt(2.0));
		template<> const F32 Base<F32>::INV_SQRT_2 = 1.0f/Base<F32>::SQRT_2;
		template<> const F32 Base<F32>::SQRT_3 = (F32)(sqrt(3.0));
		template<> const F32 Base<F32>::INV_SQRT_3 = 1.0f/Base<F32>::SQRT_3;
		template<> const F32 Base<F32>::REAL_ZERO = 0.0f;
		template<> const F32 Base<F32>::REAL_ONE = 1.0f;
		template<> const F32 Base<F32>::REAL_TWO = 2.0f;
		template<> const F32 Base<F32>::REAL_HALF = 0.5f;

		template<> const F64 Base<F64>::EPSILON = std::numeric_limits<F64>::epsilon();
		template<> const F64 Base<F64>::ZERO_TOLERANCE = 1e-08;
		template<> const F64 Base<F64>::MAX_REAL = std::numeric_limits<F64>::max();
		template<> const F64 Base<F64>::PI = 4.0*atan(1.0);
		template<> const F64 Base<F64>::PI_OVER_TWO = (F64)Base<F64>::PI/2;
		template<> const F64 Base<F64>::TWO_PI = 2.0*Base<F64>::PI;
		template<> const F64 Base<F64>::HALF_PI = 0.5*Base<F64>::PI;
		template<> const F64 Base<F64>::INV_PI = 1.0/Base<F64>::PI;
		template<> const F64 Base<F64>::INV_TWO_PI = 1.0/Base<F64>::TWO_PI;
		template<> const F64 Base<F64>::DEG_TO_RAD = Base<F64>::PI/180.0;
		template<> const F64 Base<F64>::RAD_TO_DEG = 180.0/Base<F64>::PI;
//		template<> const F64 Base<F64>::LN_2 = Base<F64>::Log(2.0);
//		template<> const F64 Base<F64>::LN_10 = Base<F64>::Log(10.0);
//		template<> const F64 Base<F64>::INV_LN_2 = 1.0/Base<F64>::LN_2;
//		template<> const F64 Base<F64>::INV_LN_10 = 1.0/Base<F64>::LN_10;
		template<> const F64 Base<F64>::SQRT_2 = sqrt(2.0);
		template<> const F64 Base<F64>::INV_SQRT_2 = 1.0/Base<F64>::SQRT_2;
		template<> const F64 Base<F64>::SQRT_3 = sqrt(3.0);
		template<> const F64 Base<F64>::INV_SQRT_3 = 1.0/Base<F64>::SQRT_3;
		template<> const F64 Base<F64>::REAL_ZERO = 0.0;
		template<> const F64 Base<F64>::REAL_ONE = 1.0;
		template<> const F64 Base<F64>::REAL_TWO = 2.0;
		template<> const F64 Base<F64>::REAL_HALF = 0.5;
	}
}
