/**
 *	\file		TEQuaternion.h
 *  \author		Terje Loe
 *  \brief		Defenitions for Quaternion class
 */


#ifndef TEQUATERNION_H
#define TEQUATERNION_H

#include "TEDataTypes.h"
#include "TEMathBase.h"

#include <iostream>

namespace TE
{
	namespace Math { template <typename TReal> class Matrix4D; }
	namespace Math { template <typename TReal> class Matrix3D; }
	namespace Math { template<typename T> class Vector3D; }

	namespace Math
	{
		template <typename Real>
		class Quaternion
		{
		public:
			Real x,y,z,w;

			Quaternion(){}

			explicit Quaternion(const Vector3D<Real>& v)
			{
				x = v.x;
				y = v.y;
				z = v.z;
				w = Math::Base<Real>::REAL_ZERO;
			}

			Quaternion(const Vector3D<Real>& v, Real s)
			{
				x = v.x;
				y = v.y;
				z = v.z;
				w = s;
			}

			explicit Quaternion(Real s)
			{
				w = s;
				x = y = z = Math::Base<Real>::REAL_ZERO;
			}

			Quaternion(const Quaternion &src) : x(src.x), y(src.y), z(src.z), w(src.w)
			{}

			Quaternion(Real a, Real b, Real c, Real s)
			{
				x = a;
				y = b;
				z = c;
				w = s;
			}

			Quaternion& Set(const Vector3D<Real>& v, Real s)
			{
				x = v.x;
				y = v.y;
				z = v.z;
				w = s;
				return (*this);
			}

			Quaternion& Set(Real a, Real b, Real c, Real s)
			{
				x = a;
				y = b;
				z = c;
				w = s;
				return (*this);
			}

			Real& operator [](unsigned i)
			{
				return ((&x)[i]);
			}

			const Real& operator [](unsigned i) const
			{
				return ((&x)[i]);
			}

			Vector3D<Real>& GetVector3D()
			{
				return (*reinterpret_cast<Vector3D<Real> *>(this));
			}

			const Vector3D<Real>& GetVector3D() const
			{
				return (*reinterpret_cast<const Vector3D<Real> *>(this));
			}

			Quaternion& operator =(const Vector3D<Real>& v)
			{
				x = v.x;
				y = v.y;
				z = v.z;
				w = Math::Base<Real>::REAL_ZERO;
				return (*this);
			}

			Quaternion& operator =(Real s)
			{
				w = s;
				x = y = z = Math::Base<Real>::REAL_ZERO;
				return (*this);
			}

			Quaternion& operator +=(const Quaternion& q)
			{
				x += q.x;
				y += q.y;
				z += q.z;
				w += q.w;
				return (*this);
			}

			Quaternion& operator +=(const Vector3D<Real>& v)
			{
				x += v.x;
				y += v.y;
				z += v.z;
				return (*this);
			}

			Quaternion& operator +=(Real s)
			{
				w += s;
				return (*this);
			}

			Quaternion& operator -=(const Quaternion& q)
			{
				x -= q.x;
				y -= q.y;
				z -= q.z;
				w -= q.w;
				return (*this);
			}

			Quaternion& operator -=(const Vector3D<Real>& v)
			{
				x -= v.x;
				y -= v.y;
				z -= v.z;
				return (*this);
			}

			Quaternion& operator -=(Real s)
			{
				w -= s;
				return (*this);
			}

			Quaternion& operator *=(const Quaternion& q)
			{
				Real a = w * q.x + x * q.w + y * q.z - z * q.y;
				Real b = w * q.y - x * q.z + y * q.w + z * q.x;
				Real c = w * q.z + x * q.y - y * q.x + z * q.w;

				w = w * q.w - x * q.x - y * q.y - z * q.z;
				x = a;
				y = b;
				z = c;

				return (*this);
			}

			Quaternion& operator *=(const Vector3D<Real>& v)
			{
				Real a = w * v.x + y * v.z - z * v.y;
				Real b = w * v.y - x * v.z + z * v.x;
				Real c = w * v.z + x * v.y - y * v.x;

				w = -x * v.x - y * v.y - z * v.z;
				x = a;
				y = b;
				z = c;

				return (*this);
			}

			Quaternion& operator *=(Real s)
			{
				x *= s;
				y *= s;
				z *= s;
				w *= s;
				return (*this);
			}

			Quaternion<Real>& operator /=(const Quaternion<Real>& q)
			{
				return (*this *= Inverse(q));
			}

			Quaternion<Real>& operator /=(const Vector3D<Real>& v)
			{
				return (*this *= -v / SquaredMag(v));
			}
			Quaternion& operator /=(Real s)
			{
				Real f = Math::Base<Real>::REAL_ONE / s;
				x *= f;
				y *= f;
				z *= f;
				w *= f;
				return (*this);
			}

			Quaternion& Normalize()
			{
				return (*this *= Base<Real>::InverseSqrt(x * x + y * y + z * z + w * w));
			}

			Vector3D<Real> GetDirectionX() const
			{
				return (Vector3D<Real>(Math::Base<Real>::REAL_ONE - Math::Base<Real>::REAL_TWO * (y * y + z * z), Math::Base<Real>::REAL_TWO * (x * y + w * z), Math::Base<Real>::REAL_TWO * (x * z - w * y)));
			}

			Vector3D<Real> GetDirectionY() const
			{
				return (Vector3D<Real>(Math::Base<Real>::REAL_TWO * (x * y - w * z), Math::Base<Real>::REAL_ONE - Math::Base<Real>::REAL_TWO * (x * x + z * z), Math::Base<Real>::REAL_TWO * (y * z + w * x)));
			}

			Vector3D<Real> GetDirectionZ() const
			{
				return (Vector3D<Real>(Math::Base<Real>::REAL_TWO * (x * z + w * y), Math::Base<Real>::REAL_TWO * (y * z - w * x), Math::Base<Real>::REAL_ONE - Math::Base<Real>::REAL_TWO * (x * x + y * y)));
			}

			Quaternion& SetRotationAboutX(Real radian)
			{
				radian *= 0.5F;
				w = static_cast<Real>(Math::Base<Real>::Cos(radian));
				x = static_cast<Real>(Math::Base<Real>::Sin(radian));
				y = z = Math::Base<Real>::REAL_ZERO;
				return *this;
			}

			Quaternion& SetRotationAboutY(Real radian)
			{
				radian *= 0.5F;
				w = static_cast<Real>(Math::Base<Real>::Cos(radian));
				y = static_cast<Real>(Math::Base<Real>::Sin(radian));
				x = z = Math::Base<Real>::REAL_ZERO;
				return *this;
			}

			Quaternion& SetRotationAboutZ(Real radian)
			{
				radian *= 0.5F;
				w = static_cast<Real>(Math::Base<Real>::Cos(radian));
				z = static_cast<Real>(Math::Base<Real>::Sin(radian));
				x = y = Math::Base<Real>::REAL_ZERO;
				return *this;
			}

			Quaternion& SetRotationAboutAxis(Real radian, const Vector3D<Real>& axis)
			{
				radian *= 0.5F;
				Real s = Math::Base<Real>::Sin(radian) * InverseMag(axis);

				w = Math::Base<Real>::Cos(radian);
				x = s * axis.x;
				y = s * axis.y;
				z = s * axis.z;

				return *this;
			}

			Matrix3D<Real> GetRotationMatrix() const
			{
				return Matrix3D<Real>(Math::Base<Real>::REAL_ONE - Math::Base<Real>::REAL_TWO * (y * y + z * z), Math::Base<Real>::REAL_TWO * (x * y - w * z), Math::Base<Real>::REAL_TWO * (x * z + w * y),
					Math::Base<Real>::REAL_TWO * (x * y + w * z), Math::Base<Real>::REAL_ONE - Math::Base<Real>::REAL_TWO * (x * x + z * z), Math::Base<Real>::REAL_TWO * (y * z - w * x),
					Math::Base<Real>::REAL_TWO * (x * z - w * y), Math::Base<Real>::REAL_TWO * (y * z + w * x), Math::Base<Real>::REAL_ONE - Math::Base<Real>::REAL_TWO * (x * x + y * y));
			}

			Matrix3D<Real> GetRotationScaleMatrix() const
			{
				Real s2 = MagnitudeSqr(*this);
				Real r = Base<Real>::InverseSqrt(s2);
				Real s = s2 * r;
				Real t = s * Math::Base<Real>::REAL_TWO;

				Real a = w * r;
				Real b = x * r;
				Real c = y * r;
				Real d = z * r;

				return Matrix3D<Real>(s - t * (c * c + d * d), t * (b * c - a * d), t * (b * d + a * c),
					t * (b * c + a * d), s - t * (b * b + d * d), t * (c * d - a * b),
					t * (b * d - a * c), t * (c * d + a * b), s - t * (b * b + c * c));
			}

			Quaternion& SetRotationMatrix(const Matrix3D<Real>& m)
			{
				Real m00 = m(0,0);
				Real m11 = m(1,1);
				Real m22 = m(2,2);
				Real trace = m00 + m11 + m22;

				if (trace > Math::Base<Real>::REAL_ZERO)
				{
					w = 0.5F * Base<Real>::Sqrt(trace + Math::Base<Real>::REAL_ONE);
					Real f = 0.25F / w;

					x = (m(2,1) - m(1,2)) * f;
					y = (m(0,2) - m(2,0)) * f;
					z = (m(1,0) - m(0,1)) * f;
				}
				else if ((m00 > m11) && (m00 > m22))
				{
					x = 0.5F * Base<Real>::Sqrt(m00 - m11 - m22 + Math::Base<Real>::REAL_ONE);
					Real f = 0.25F / x;

					y = (m(0,1) + m(1,0)) * f;
					z = (m(0,2) + m(2,0)) * f;
					w = (m(2,1) - m(1,2)) * f;
				}
				else if (m11 > m22)
				{
					y = 0.5F * Base<Real>::Sqrt(m11 - m00 - m22 + Math::Base<Real>::REAL_ONE);
					Real f = 0.25F / y;

					x = (m(0,1) + m(1,0)) * f;
					z = (m(1,2) + m(2,1)) * f; 
					w = (m(0,2) - m(2,0)) * f;
				} 
				else 
				{ 
					z = 0.5F * Base<Real>::Sqrt(m22 - m00 - m11 + Math::Base<Real>::REAL_ONE);
					Real f = 0.25F / z; 

					x = (m(0,2) + m(2,0)) * f;
					y = (m(1,2) + m(2,1)) * f; 
					w = (m(1,0) - m(0,1)) * f; 
				} 

				return (*this);
			}

			Quaternion& SetRotationMatrix(const Matrix4D<Real>& m)
			{
				Real m00 = m(0,0);
				Real m11 = m(1,1);
				Real m22 = m(2,2);
				Real trace = m00 + m11 + m22;

				if (trace > Math::Base<Real>::REAL_ZERO)
				{
					w = 0.5F * Base<Real>::Sqrt(trace + Math::Base<Real>::REAL_ONE);
					Real f = 0.25F / w;

					x = (m(2,1) - m(1,2)) * f;
					y = (m(0,2) - m(2,0)) * f;
					z = (m(1,0) - m(0,1)) * f;
				}
				else if ((m00 > m11) && (m00 > m22))
				{
					x = 0.5F * Base<Real>::Sqrt(m00 - m11 - m22 + Math::Base<Real>::REAL_ONE);
					Real f = 0.25F / x;

					y = (m(0,1) + m(1,0)) * f;
					z = (m(0,2) + m(2,0)) * f;
					w = (m(2,1) - m(1,2)) * f;
				}
				else if (m11 > m22)
				{
					y = 0.5F * Base<Real>::Sqrt(m11 - m00 - m22 + Math::Base<Real>::REAL_ONE);
					Real f = 0.25F / y;

					x = (m(0,1) + m(1,0)) * f;
					z = (m(1,2) + m(2,1)) * f;
					w = (m(0,2) - m(2,0)) * f;
				}
				else
				{
					z = 0.5F * Base<Real>::Sqrt(m22 - m00 - m11 + Math::Base<Real>::REAL_ONE);
					Real f = 0.25F / z;

					x = (m(0,2) + m(2,0)) * f;
					y = (m(1,2) + m(2,1)) * f;
					w = (m(1,0) - m(0,1)) * f;
				}

				return *this;
			}

			static const Quaternion QUATERNION_IDENTITY;
			static const Quaternion QUATERNION_INVALID;
		};

		template <typename Real>
		inline Quaternion<Real> operator -(const Quaternion<Real>& q)
		{
			return (Quaternion<Real>(-q.x, -q.y, -q.z, -q.w));
		}

		template <typename Real>
		inline Quaternion<Real> operator +(const Quaternion<Real>& q1, const Quaternion<Real>& q2)
		{
			return (Quaternion<Real>(q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w));
		}

		template <typename Real>
		inline Quaternion<Real> operator +(const Quaternion<Real>& q, const Vector3D<Real>& v)
		{
			return (Quaternion<Real>(q.x + v.x, q.y + v.y, q.z + v.z, q.w));
		}

		template <typename Real>
		inline Quaternion<Real> operator +(const Vector3D<Real>& v, const Quaternion<Real>& q)
		{
			return (Quaternion<Real>(v.x + q.x, v.y + q.y, v.z + q.z, q.w));
		}

		template <typename Real>
		inline Quaternion<Real> operator +(const Quaternion<Real>& q, Real s)
		{
			return (Quaternion<Real>(q.x, q.y, q.z, q.w + s));
		}

		template <typename Real>
		inline Quaternion<Real> operator +(Real s, const Quaternion<Real>& q)
		{
			return (Quaternion<Real>(q.x, q.y, q.z, s + q.w));
		}

		template <typename Real>
		inline Quaternion<Real> operator -(const Quaternion<Real>& q1, const Quaternion<Real>& q2)
		{
			return (Quaternion<Real>(q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w));
		}

		template <typename Real>
		inline Quaternion<Real> operator -(const Quaternion<Real>& q, const Vector3D<Real>& v)
		{
			return (Quaternion<Real>(q.x - v.x, q.y - v.y, q.z - v.z, q.w));
		}

		template <typename Real>
		inline Quaternion<Real> operator -(const Vector3D<Real>& v, const Quaternion<Real>& q)
		{
			return (Quaternion<Real>(v.x - q.x, v.y - q.y, v.z - q.z, -q.w));
		}

		template <typename Real>
		inline Quaternion<Real> operator -(const Quaternion<Real>& q, Real s)
		{
			return (Quaternion<Real>(q.x, q.y, q.z, q.w - s));
		}

		template <typename Real>
		inline Quaternion<Real> operator -(Real s, const Quaternion<Real>& q)
		{
			return (Quaternion<Real>(-q.x, -q.y, -q.z, s - q.w));
		}

		template <typename Real>
		inline Quaternion<Real> operator *(const Quaternion<Real>& q, Real s)
		{
			return (Quaternion<Real>(q.x * s, q.y * s, q.z * s, q.w * s));
		}

		template <typename Real>
		inline Quaternion<Real> operator *(Real s, const Quaternion<Real>& q)
		{
			return (Quaternion<Real>(s * q.x, s * q.y, s * q.z, s * q.w));
		}

		template <typename Real>
		inline Quaternion<Real> operator /(const Quaternion<Real>& q, Real s)
		{
			Real f = Math::Base<Real>::REAL_ONE / s;
			return (Quaternion<Real>(q.x * f, q.y * f, q.z * f, q.w * f));
		}

		template <typename Real>
		inline bool operator ==(const Quaternion<Real>& q1, const Quaternion<Real>& q2)
		{
			return ((q1.x == q2.x) && (q1.y == q2.y) && (q1.z == q2.z) && (q1.w == q2.w));
		}

		template <typename Real>
		inline bool operator ==(const Quaternion<Real>& q, const Vector3D<Real>& v)
		{
			return ((q.x == v.x) && (q.y == v.y) && (q.z == v.z) && (q.w == Math::Base<Real>::REAL_ZERO));
		}

		template <typename Real>
		inline bool operator ==(const Vector3D<Real>& v, const Quaternion<Real>& q)
		{
			return ((q.x == v.x) && (q.y == v.y) && (q.z == v.z) && (q.w == Math::Base<Real>::REAL_ZERO));
		}

		template <typename Real>
		inline bool operator ==(const Quaternion<Real>& q, Real s)
		{
			return ((q.w == s) && (q.x == Math::Base<Real>::REAL_ZERO) && (q.y == Math::Base<Real>::REAL_ZERO) && (q.z == Math::Base<Real>::REAL_ZERO));
		}

		template <typename Real>
		inline bool operator ==(Real s, const Quaternion<Real>& q)
		{
			return ((q.w == s) && (q.x == Math::Base<Real>::REAL_ZERO) && (q.y == Math::Base<Real>::REAL_ZERO) && (q.z == Math::Base<Real>::REAL_ZERO));
		}

		template <typename Real>
		inline bool operator !=(const Quaternion<Real>& q1, const Quaternion<Real>& q2)
		{
			return ((q1.x != q2.x) || (q1.y != q2.y) || (q1.z != q2.z) || (q1.w != q2.w));
		}

		template <typename Real>
		inline bool operator !=(const Quaternion<Real>& q, const Vector3D<Real>& v)
		{
			return ((q.x != v.x) || (q.y != v.y) || (q.z != v.z) || (q.w != Math::Base<Real>::REAL_ZERO));
		}

		template <typename Real>
		inline bool operator !=(const Vector3D<Real>& v, const Quaternion<Real>& q)
		{
			return ((q.x != v.x) || (q.y != v.y) || (q.z != v.z) || (q.w != Math::Base<Real>::REAL_ZERO));
		}

		template <typename Real>
		inline bool operator !=(const Quaternion<Real>& q, Real s)
		{
			return ((q.w != s) || (q.x != Math::Base<Real>::REAL_ZERO) || (q.y != Math::Base<Real>::REAL_ZERO) || (q.z != Math::Base<Real>::REAL_ZERO));
		}

		template <typename Real>
		inline bool operator !=(Real s, const Quaternion<Real>& q)
		{
			return ((q.w != s) || (q.x != Math::Base<Real>::REAL_ZERO) || (q.y != Math::Base<Real>::REAL_ZERO) || (q.z != Math::Base<Real>::REAL_ZERO));
		}

		template <typename Real>
		inline Real Dot(const Quaternion<Real>& q1, const Quaternion<Real>& q2)
		{
			return (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w);
		}

		template <typename Real>
		inline Real Magnitude(const Quaternion<Real>& q)
		{
			return (Base<Real>::Sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w));
		}

		template <typename Real>
		inline Real SquaredMag(const Quaternion<Real>& q)
		{
			return (q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
		}

		template <typename Real>
		inline Quaternion<Real> Conjugate(const Quaternion<Real>& q)
		{
			return Quaternion<Real>(-q.x, -q.y, -q.z, q.w);
		}

		template <typename Real>
		inline Quaternion<Real> Inverse(const Quaternion<Real>& q)
		{
			return (Conjugate(q) / SquaredMag(q));
		}
	
		template <typename Real>
		inline Quaternion<Real> operator /(Real s, const Quaternion<Real>& q)
		{
			return (s * Inverse(q));
		}

		template <typename Real>
		Quaternion<Real> operator *(const Quaternion<Real>& q1, const Quaternion<Real>& q2)
		{
			return (Quaternion<Real>(q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
									 q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
									 q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
									 q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z));
		}

		template <typename Real>
		Quaternion<Real> operator *(const Quaternion<Real>& q, const Vector3D<Real>& v)
		{
			return (Quaternion<Real>(q.w * v.x + q.y * v.z - q.z * v.y,
				q.w * v.y - q.x * v.z + q.z * v.x,
				q.w * v.z + q.x * v.y - q.y * v.x,
				-q.x * v.x - q.y * v.y - q.z * v.z));
		}

		template <typename Real>
		inline Quaternion<Real> operator *(const Vector3D<Real>& v, const Quaternion<Real>& q)
		{
			return (Quaternion<Real>(v.x, v.y, v.z, Math::Base<Real>::REAL_ZERO) * q);
		}

		template <typename Real>
		inline Quaternion<Real> operator /(const Quaternion<Real>& q1, const Quaternion<Real>& q2)
		{
			return (q1 * Inverse(q2));
		}

		template <typename Real>
		inline Quaternion<Real> operator /(const Quaternion<Real>& q, const Vector3D<Real>& v)
		{
			return (q * (-v / SquaredMag(v)));
		}

		template <typename Real>
		inline Quaternion<Real> operator /(const Vector3D<Real>& v, const Quaternion<Real>& q)
		{
			return (Quaternion<Real>(v.x, v.y, v.z, Math::Base<Real>::REAL_ZERO) * Inverse(q));
		}

        template<typename Real>
        inline std::ostream& operator<<(std::ostream& output, const Quaternion<Real>& q)
        {
            output << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
            return output;
        }

		template <typename Real>
		Vector3D<Real> Rotate(const Vector3D<Real>& v, const Quaternion<Real>& q)
		{
			/*
			The commented out code taken from the C4 engine gives wrong values on some rotations
			Real x2 = q.x * q.x;
			Real y2 = q.y * q.y;
			Real z2 = q.z * q.z;

			Real xy = q.x * q.y;
			Real xz = q.x * q.z;
			Real yz = q.y * q.z;

			Real wx = q.w * q.x;
			Real wy = q.w * q.y;
			Real wz = q.w * q.z;

			return (Vector3D<Real>(v.x * (Math::Base<Real>::REAL_ONE - Math::Base<Real>::REAL_TWO * (y2 + z2)) + v.y * Math::Base<Real>::REAL_TWO * (xy - wz) + v.z * Math::Base<Real>::REAL_TWO * (xz + wy),
				v.x * Math::Base<Real>::REAL_TWO * (xy + wz) + v.y * (Math::Base<Real>::REAL_ONE - Math::Base<Real>::REAL_TWO * (x2 + z2)) + v.z * Math::Base<Real>::REAL_TWO * (yz - wx),
				v.x * Math::Base<Real>::REAL_TWO * (xz - wy) + v.y * Math::Base<Real>::REAL_TWO * (yz - wx) + v.z * (Math::Base<Real>::REAL_ONE - Math::Base<Real>::REAL_TWO * (x2 + y2))));*/

			F32 vMult = Math::Base<Real>::REAL_TWO*(q.x*v.x + q.y*v.y + q.z*v.z);
			F32 crossMult = Math::Base<Real>::REAL_TWO*q.w;
			F32 pMult = crossMult*q.w - Math::Base<Real>::REAL_ONE;

			return Vector3D<Real>( pMult*v.x + vMult*q.x + crossMult*(q.y*v.z - q.z*v.y),
				pMult*v.y + vMult*q.y + crossMult*(q.z*v.x - q.x*v.z),
				pMult*v.z + vMult*q.z + crossMult*(q.x*v.y - q.y*v.x) );
		}
	}
}

#endif
