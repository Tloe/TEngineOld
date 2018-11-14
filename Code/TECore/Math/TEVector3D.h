/**
 *	\file		TEVector2D.h
 *  \author		Terje Loe
 *  \brief		Defenitions for Vector3D class
 */

#ifndef TEVECTOR3D_H
#define TEVECTOR3D_H

#include <iostream>
#include <assert.h>
#include <TEDataTypes.h>
#include <TEMathBase.h>

namespace TE
{
	namespace Math
	{
		template <typename Real>
		class Vector3D
		{
		public:
			Real x,y,z;

			Vector3D() {}

			Vector3D(const Vector3D &src) : x(src.x), y(src.y), z(src.z)
			{

			}

			Vector3D(Real nx, Real ny, Real nz) : x(nx), y(ny), z(nz){}

			void Set(Real nx, Real ny, Real nz)
			{
				x = nx; y = ny; z = nz;
			}

            const Vector3D& operator=(const Vector3D &rhs)
			{
				if (&rhs == this) return *this;
				x = rhs.x; y = rhs.y; z = rhs.z;

				return *this;
			}

			Vector3D& operator +=(const Vector3D& rhs)
			{
				x += rhs.x; y += rhs.y; z += rhs.z;
				return *this;
			}

			Vector3D& operator -=(const Vector3D& rhs)
			{
				x -= rhs.x;	y -= rhs.y;	z -= rhs.z;
				return *this;
			}

			Vector3D& operator *=(Real scalar)
			{
				x *= scalar; y *= scalar; z *= scalar;
				return *this;
			}

			Vector3D& operator /=(Real scalar)
			{
				Real invScalar = Math::Base<Real>::REAL_ONE / scalar;
				x *= invScalar; y *= invScalar;	z *= invScalar;
				return *this;
			}

			Vector3D& Normalize()
			{
				Real magSqr = MagnitudeSqr(*this);

				if (magSqr > Math::Base<Real>::REAL_ZERO)
				{
					Real invMag = Math::Base<Real>::REAL_ONE/Math::Base<Real>::Sqrt(magSqr);
					x *= invMag; y *= invMag; z *= invMag;
				}

				return *this;
			}

			Real& operator[](I32 i)
			{
				assert(i < 3 && i> -1);
				return *(&x + i);
			}

			const Real& operator[](I32 i) const
			{
				assert(i < 3 && i > -1);
				return *(&x + i);
			};

			static const Vector3D VECTOR3D_ZERO;
			static const Vector3D VECTOR3D_AXIS_X;
			static const Vector3D VECTOR3D_AXIS_Y;
			static const Vector3D VECTOR3D_AXIS_Z;
			static const Vector3D VECTOR3D_NEG_AXIS_X;
			static const Vector3D VECTOR3D_NEG_AXIS_Y;
			static const Vector3D VECTOR3D_NEG_AXIS_Z;
			static const Vector3D VECTOR3D_ONE;
		};

		template<typename Real>
		inline Real Magnitude(const Vector3D<Real>& v)
		{
			return Base<Real>::Sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
		}

		template<typename Real>
		inline Real MagnitudeSqr(const Vector3D<Real>& v)
		{
			return v.x*v.x + v.y*v.y + v.z*v.z;
		}

		template<typename Real>
		inline Real InverseMag(const Vector3D<Real>& v)
		{
			return Base<Real>::InverseSqrt(v.x*v.x + v.y*v.y + v.z*v.z);
		}

		template<typename Real>
		inline const Vector3D<Real> Cross(const Vector3D<Real>& lhs, const Vector3D<Real>& rhs)
		{
			return (Vector3D<Real>(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x));
		}

		template<typename Real>
		inline const Real Dot(const Vector3D<Real>& lhs, const Vector3D<Real>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}

		template<typename Real>
		inline bool operator==(const Vector3D<Real> &lhs, const Vector3D<Real> &rhs)
		{
			return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
		}

		template<typename Real>
		inline bool operator !=(const Vector3D<Real>& lhs, const Vector3D<Real>& rhs)
		{
			return ((lhs.x != rhs.x) || (lhs.y != rhs.y) || (lhs.z != rhs.z));
		}

		template<typename Real>
		inline Vector3D<Real> operator-(const Vector3D<Real>& v)
		{
			return Vector3D<Real>(-v.x, -v.y, -v.z);
		}

		template<typename Real>
		inline Vector3D<Real> operator +(const Vector3D<Real>& lhs, const Vector3D<Real>& rhs)
		{
			return (Vector3D<Real>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z));
		}

		template<typename Real>
		inline Vector3D<Real> operator -(const Vector3D<Real>& lhs, const Vector3D<Real>& rhs)
		{
			return (Vector3D<Real>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z));
		}

		template<typename Real>
		inline Vector3D<Real> operator *(const Vector3D<Real>& v, Real scalar)
		{
			return (Vector3D<Real>(v.x * scalar, v.y * scalar, v.z * scalar));
		}

		template<typename Real>
		inline Vector3D<Real> operator *(Real scalar, const Vector3D<Real>& v)
		{
			return (Vector3D<Real>(scalar * v.x, scalar * v.y, scalar * v.z));
		}

		template<typename Real>
		inline Vector3D<Real> operator /(const Vector3D<Real>& v, Real scalar)
		{
			Real invScalar = Math::Base<Real>::REAL_ONE / scalar;
			return (Vector3D<Real>(v.x * invScalar, v.y * invScalar, v.z * invScalar));
		}

		template<typename Real>
		inline std::ostream& operator<<(std::ostream& output, const Vector3D<Real>& v)
		{
			output << "(" << v.x << ", " << v.y << ", " << v.z << ")";
			return output;
        }

		template <typename Real>
		inline bool IsZero(const Vector3D<Real>& v)
		{
			return v.x == 0 &&
				v.y == 0 &&
				v.z == 0;
		}

		template <typename Real>
		inline Real Max(const Vector3D<Real>& v)
		{
			Real temp = max(v.x,v.y);
			return max(temp, v.z);
		}

		template <typename Real>
		inline void Orthonormalize (Vector3D<Real>& u, Vector3D<Real>& v, Vector3D<Real>& w)
		{
			// If the input vectors are v0, v1, and v2, then the Gram-Schmidt
			// orthonormalization produces vectors u0, u1, and u2 as follows,
			//
			//   u0 = v0/|v0|
			//   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
			//   u2 = (v2-(u0*v2)u0-(u1*v2)u1)/|v2-(u0*v2)u0-(u1*v2)u1|
			//
			// where |A| indicates length of vector A and A*B indicates dot
			// product of vectors A and B.

			// compute u0
			u.Normalize();

			// compute u1
			Real dot0 = Dot(u,v); 
			v -= dot0*u;
			v.Normalize();

			// compute u2
			Real dot1 = Dot(v,w);
			dot0 = Dot(u,w);
			w -= dot0*u + dot1*v;
			w.Normalize();
		}

		template <typename Real>
		inline void CreateOrthonormalBasis(Vector3D<Real>& u, Vector3D<Real>& v, Vector3D<Real>& w)
		{
			w.Normalize();
			CreateComplementBasis(u,v,w);
		}

		template <typename Real>
		inline void CreateComplementBasis(Vector3D<Real>& u, Vector3D<Real>& v, const Vector3D<Real>& w)
		{
			Real invLength;

			if (Math::Base<Real>::Abs(w.x) >= Math::Base<Real>::Abs(w.y))
			{
				// vec2.x or vec2.z is the largest magnitude component, swap them
				invLength = Math::Base<Real>::REAL_ONE / Math::Base<Real>::Sqrt(w.x*w.x + w.z*w.z);
				u.x = -w.z*invLength;
				u.y = Math::Base<Real>::REAL_ZERO;
				u.z = +w.x*invLength;
				u.x = w.y*u.z;
				u.y = w.z*u.x -	w.x*u.z;
				u.z = -w.y*u.x;
			}
			else
			{
				// vec2.y or vec2.z is the largest magnitude component, swap them
				invLength = Math::Base<Real>::REAL_ONE / Math::Base<Real>::Sqrt(w.y*w.y + w.z*w.z);
				u.x = Math::Base<Real>::REAL_ZERO;
				u.y = +w.z*invLength;
				u.z = -w.y*invLength;
				u.x = w.y*u.z -	w.z*u.y;
				u.y = -w.x*u.z;
				u.z = w.x*u.y;
			}
		}
	}
}

#endif
