/**
 *	\file		TEVector2D.h
 *  \author		Terje Loe
 *  \brief		Defenitions for Vector2D class
 */

#ifndef TEVECTOR2D_H
#define TEVECTOR2D_H

#include <TEDataTypes.h>
#include <TEMathBase.h>

namespace TE
{
	namespace Math { template<typename T> class Vector3D; }

	namespace Math
	{
		template <typename Real>
		class Vector2D
		{
		public:
			Real x,y;

			Vector2D(){}

			Vector2D(const Vector2D &src) : x(src.x), y(src.y){}

			Vector2D(Real nx, Real ny) : x(nx), y(ny){}

			void Set(Real nx, Real ny)
			{
				x = nx; y = ny;
			}

			const Vector2D& operator=(const Vector2D &rhs)
			{
				if (&rhs == this) return *this;
				x = rhs.x; y = rhs.y;
				return *this;
			}

			Vector2D& operator +=(const Vector2D& rhs)
			{
				x += rhs.x; y += rhs.y;
				return *this;
			}

			Vector2D& operator -=(const Vector2D& rhs)
			{
				x -= rhs.x;	y -= rhs.y;
				return *this;
			}

			Vector2D& operator *=(Real scalar)
			{
				x *= scalar; y *= scalar;
				return *this;
			}

			Vector2D& operator /=(Real scalar)
			{
				Real invScalar = Math::Base<Real>::REAL_ONE / scalar;
				x *= invScalar; y *= invScalar;
				return *this;
			}

			Vector2D& Normalize()
			{
				Real magSqr = MagnitudeSqr(*this);

				if (magSqr > Math::Base<Real>::REAL_ZERO)
				{
					Real invMag = Math::Base<Real>::REAL_ONE/Math::Base<Real>::sqrt(magSqr);
					x *= invMag; y *= invMag;
				}

				return *this;
			}

			static const Vector2D VECTOR2D_ZERO;
			static const Vector2D VECTOR2D_AXIS_X;
			static const Vector2D VECTOR2D_AXIS_Y;
			static const Vector2D VECTOR2D_NEG_AXIS_X;
			static const Vector2D VECTOR2D_NEG_AXIS_Y;
			static const Vector2D VECTOR2D_ONE;
		};

		template<typename Real>
		inline Real Magnitude(const Vector2D<Real>& v)
		{
			return Base<Real>::Sqrt(v.x*v.x + v.y*v.y);
		}

		template<typename Real>
		inline Real MagnitudeSqr(const Vector2D<Real>& v)
		{
			return v.x*v.x + v.y*v.y;
		}
		
		template<typename Real>
		inline const Real Dot(const Vector2D<Real>& lhs, const Vector2D<Real>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		template<typename Real>
		inline bool operator==(const Vector2D<Real> &lhs, const Vector2D<Real> &rhs)
		{
			return lhs.x == rhs.x && lhs.y == rhs.y;
		}

		template<typename Real>
		inline bool operator !=(const Vector2D<Real>& lhs, const Vector2D<Real>& rhs)
		{
			return ((lhs.x != rhs.x) || (lhs.y != rhs.y));
		}

		template<typename Real>
		inline Vector2D<Real> operator-(const Vector2D<Real>& v)
		{
			return Vector2D<Real>(-v.x, -v.y);
		}

		template<typename Real>
		inline Vector2D<Real> operator+(const Vector2D<Real>& lhs, const Vector2D<Real>& rhs)
		{
			return Vector2D<Real>(lhs.x + rhs.x, lhs.y + rhs.y);
		}

		template<typename Real>
		inline Vector2D<Real> operator-(const Vector2D<Real>& lhs, const Vector2D<Real>& rhs)
		{
			return Vector2D<Real>(lhs.x - rhs.x, lhs.y - rhs.y);
		}

		template<typename Real>
		inline Vector2D<Real> operator*(const Vector2D<Real>& v, Real scalar)
		{
			return Vector3D<Real>(v.x * scalar, v.y * scalar);
		}

		template<typename Real>
		inline Vector2D<Real> operator*(Real scalar, const Vector2D<Real>& v)
		{
			return Vector2D<Real>(scalar * v.x, scalar * v.y);
		}

		template<typename Real>
		inline Vector2D<Real> operator/(const Vector2D<Real>& v, Real scalar)
		{
			Real invScalar = Math::Base<Real>::REAL_ONE / scalar;
			return Vector2D<Real>(v.x * invScalar, v.y * invScalar);
		}

		template <typename Real>
		bool IsZero(const Vector2D<Real>& v)
		{
			return v.x == 0 &&
				v.y == 0;
		}

        template <> inline const TE::Math::Vector2D<F32> TE::Math::Vector2D<F32>::VECTOR2D_ZERO(0.0f, 0.0f);
        template <> inline const TE::Math::Vector2D<F64> TE::Math::Vector2D<F64>::VECTOR2D_ZERO(0.0, 0.0);

        template <> inline const TE::Math::Vector2D<F32> TE::Math::Vector2D<F32>::VECTOR2D_AXIS_X(1.0f, 0.0f);
        template <> inline const TE::Math::Vector2D<F64> TE::Math::Vector2D<F64>::VECTOR2D_AXIS_X(1.0, 0.0);

        template <> inline const TE::Math::Vector2D<F32> TE::Math::Vector2D<F32>::VECTOR2D_AXIS_Y(0.0f, 1.0f);
        template <> inline const TE::Math::Vector2D<F64> TE::Math::Vector2D<F64>::VECTOR2D_AXIS_Y(0.0, 1.0);

        template <> inline const TE::Math::Vector2D<F32> TE::Math::Vector2D<F32>::VECTOR2D_NEG_AXIS_X(-1.0f, 0.0f);
        template <> inline const TE::Math::Vector2D<F64> TE::Math::Vector2D<F64>::VECTOR2D_NEG_AXIS_X(-1.0, 0.0);

        template <> inline const TE::Math::Vector2D<F32> TE::Math::Vector2D<F32>::VECTOR2D_NEG_AXIS_Y(0.0f, -1.0f);
        template <> inline const TE::Math::Vector2D<F64> TE::Math::Vector2D<F64>::VECTOR2D_NEG_AXIS_Y(0.0, -1.0);

        template <> inline const TE::Math::Vector2D<F32> TE::Math::Vector2D<F32>::VECTOR2D_ONE(1.0f, 1.0f);
        template <> inline const TE::Math::Vector2D<F64> TE::Math::Vector2D<F64>::VECTOR2D_ONE(1.0, 1.0);
	}
}

#endif
