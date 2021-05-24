/**
 *	\file		Matrix3D.h
 *  \author		Terje Loe
 *  \brief		Defenitions for Matrix3D class
 */
#ifndef TEMATRIX3D_H
#define TEMATRIX3D_H

#include <TEDataTypes.h>
#include <TEMathBase.h>
#include <assert.h>

namespace TE::Math {
  template <typename TReal> class Matrix4D;
  template <typename T> class Vector3D;

  template <typename TReal> class Matrix3D {
  private:
    TReal m_data[3][3];

  public:
    Matrix3D() {}

    Matrix3D(const Vector3D<TReal> &c0, const Vector3D<TReal> &c1, const Vector3D<TReal> &c2) {
      m_data[0][0] = c0.x;
      m_data[0][1] = c0.y;
      m_data[0][2] = c0.z;
      m_data[1][0] = c1.x;
      m_data[1][1] = c1.y;
      m_data[1][2] = c1.z;
      m_data[2][0] = c2.x;
      m_data[2][1] = c2.y;
      m_data[2][2] = c2.z;
    }

    Matrix3D(TReal m00,
             TReal m01,
             TReal m02,
             TReal m10,
             TReal m11,
             TReal m12,
             TReal m20,
             TReal m21,
             TReal m22) {
      m_data[0][0] = m00;
      m_data[0][1] = m01;
      m_data[0][2] = m02;
      m_data[1][0] = m10;
      m_data[1][1] = m11;
      m_data[1][2] = m12;
      m_data[2][0] = m20;
      m_data[2][1] = m21;
      m_data[2][2] = m22;
    }

    /*
    Matrix3D(const Matrix3D& m)
    {
            m_data[0][0] = m.m_data[0][0];
            m_data[0][1] = m.m_data[0][1];
            m_data[0][2] = m.m_data[0][2];
            m_data[1][0] = m.m_data[1][0];
            m_data[1][1] = m.m_data[1][1];
            m_data[1][2] = m.m_data[1][2];
            m_data[2][0] = m.m_data[2][0];
            m_data[2][1] = m.m_data[2][1];
            m_data[2][2] = m.m_data[2][2];
    }*/

    Matrix3D &Set(const Vector3D<TReal> &c0, const Vector3D<TReal> &c1, const Vector3D<TReal> &c2) {
      m_data[0][0] = c0.x;
      m_data[0][1] = c0.y;
      m_data[0][2] = c0.z;
      m_data[1][0] = c1.x;
      m_data[1][1] = c1.y;
      m_data[1][2] = c1.z;
      m_data[2][0] = c2.x;
      m_data[2][1] = c2.y;
      m_data[2][2] = c2.z;
    }

    Matrix3D &Set(TReal m00,
                  TReal m01,
                  TReal m02,
                  TReal m10,
                  TReal m11,
                  TReal m12,
                  TReal m20,
                  TReal m21,
                  TReal m22) {
      m_data[0][0] = m00;
      m_data[0][1] = m01;
      m_data[0][2] = m02;
      m_data[1][0] = m10;
      m_data[1][1] = m11;
      m_data[1][2] = m12;
      m_data[2][0] = m20;
      m_data[2][1] = m21;
      m_data[2][2] = m22;
    }

    TReal &operator()(unsigned i, unsigned j) {
      assert(i < 3 && j < 3 && "Subscription out of range.");
      return m_data[i][j];
    }

    const TReal &operator()(unsigned i, unsigned j) const {
      assert(i < 3 && j < 3 && "Subscription out of range.");
      return m_data[i][j];
    }

    Vector3D<TReal> &operator[](unsigned j) {
      assert(j < 3 && "Subscription out of range.");
      return *reinterpret_cast<Vector3D<TReal> *>(m_data[j]);
    }

    const Vector3D<TReal> &operator[](unsigned j) const {
      assert(j < 3 && "Subscription out of range.");
      return *reinterpret_cast<const Vector3D<TReal> *>(m_data[j]);
    }

    Matrix3D &operator*=(const Matrix3D &m) {
      TReal t = m_data[0][0] * m.m_data[0][0] + m_data[0][1] * m.m_data[1][0] +
                m_data[0][2] * m.m_data[2][0];
      TReal u = m_data[0][0] * m.m_data[0][1] + m_data[0][1] * m.m_data[1][1] +
                m_data[0][2] * m.m_data[2][1];
      m_data[0][2] = m_data[0][0] * m.m_data[0][2] + m_data[0][1] * m.m_data[1][2] +
                     m_data[0][2] * m.m_data[2][2];
      m_data[0][0] = t;
      m_data[0][1] = u;

      t            = m_data[1][0] * m.m_data[0][0] + m_data[1][1] * m.m_data[1][0] +
          m_data[1][2] * m.m_data[2][0];
      u = m_data[1][0] * m.m_data[0][1] + m_data[1][1] * m.m_data[1][1] +
          m_data[1][2] * m.m_data[2][1];
      m_data[1][2] = m_data[1][0] * m.m_data[0][2] + m_data[1][1] * m.m_data[1][2] +
                     m_data[1][2] * m.m_data[2][2];
      m_data[1][0] = t;
      m_data[1][1] = u;

      t            = m_data[2][0] * m.m_data[0][0] + m_data[2][1] * m.m_data[1][0] +
          m_data[2][2] * m.m_data[2][0];
      u = m_data[2][0] * m.m_data[0][1] + m_data[2][1] * m.m_data[1][1] +
          m_data[2][2] * m.m_data[2][1];
      m_data[2][2] = m_data[2][0] * m.m_data[0][2] + m_data[2][1] * m.m_data[1][2] +
                     m_data[2][2] * m.m_data[2][2];
      m_data[2][0] = t;
      m_data[2][1] = u;

      return *this;
    }

    Matrix3D &operator*=(TReal scalar) {
      m_data[0][0] *= scalar;
      m_data[1][0] *= scalar;
      m_data[2][0] *= scalar;
      m_data[0][1] *= scalar;
      m_data[1][1] *= scalar;
      m_data[2][1] *= scalar;
      m_data[0][2] *= scalar;
      m_data[1][2] *= scalar;
      m_data[2][2] *= scalar;

      return *this;
    }

    Matrix3D &operator/=(TReal scalar) {
      TReal invScalar = Math::Base<TReal>::REAL_ONE / scalar;
      m_data[0][0] *= invScalar;
      m_data[1][0] *= invScalar;
      m_data[2][0] *= invScalar;
      m_data[0][1] *= invScalar;
      m_data[1][1] *= invScalar;
      m_data[2][1] *= invScalar;
      m_data[0][2] *= invScalar;
      m_data[1][2] *= invScalar;
      m_data[2][2] *= invScalar;

      return *this;
    }

    void operator+=(const Matrix3D &rhs) {
      m_data[0][0] += rhs.m_data[0][0];
      m_data[1][0] += rhs.m_data[1][0];
      m_data[2][0] += rhs.m_data[2][0];
      m_data[0][1] += rhs.m_data[0][1];
      m_data[1][1] += rhs.m_data[1][1];
      m_data[2][1] += rhs.m_data[2][1];
      m_data[0][2] += rhs.m_data[0][2];
      m_data[1][2] += rhs.m_data[1][2];
      m_data[2][2] += rhs.m_data[2][2];
    }

    Matrix3D &SetIdentity() {
      m_data[0][0] = m_data[1][1] = m_data[2][2] = Math::Base<TReal>::REAL_ONE;
      m_data[0][1] = m_data[0][2] = m_data[1][0] = m_data[1][2] = m_data[2][0] = m_data[2][1] =
          Math::Base<TReal>::REAL_ZERO;

      return *this;
    }

    Matrix3D &SetRotationAboutX(TReal angle) {
      TReal s      = Math::Base<TReal>::Sin(angle);
      m_data[0][0] = Math::Base<TReal>::REAL_ONE;
      m_data[0][1] = m_data[0][2] = m_data[1][0] = m_data[2][0] = Math::Base<TReal>::REAL_ZERO;
      m_data[1][1] = m_data[2][2] = Math::Base<TReal>::Cos(angle);
      m_data[2][1]                = -s;
      m_data[1][2]                = s;

      return (*this);
    }

    Matrix3D &SetRotationAboutY(TReal angle) {
      TReal s      = Math::Base<TReal>::Sin(angle);
      m_data[1][1] = Math::Base<TReal>::REAL_ONE;
      m_data[1][0] = m_data[1][2] = m_data[0][1] = m_data[2][1] = Math::Base<TReal>::REAL_ZERO;
      m_data[0][0] = m_data[2][2] = Math::Base<TReal>::Cos(angle);
      m_data[2][0]                = s;
      m_data[0][2]                = -s;

      return (*this);
    }

    Matrix3D &SetRotationAboutZ(TReal angle) {
      TReal s      = Math::Base<TReal>::Sin(angle);
      m_data[2][2] = Math::Base<TReal>::REAL_ONE;
      m_data[2][0] = m_data[2][1] = m_data[0][2] = m_data[1][2] = Math::Base<TReal>::REAL_ZERO;
      m_data[0][0] = m_data[1][1] = Math::Base<TReal>::Cos(angle);
      m_data[1][0]                = -s;
      m_data[0][1]                = s;

      return (*this);
    }

    Matrix3D &SetRotationAboutAxis(TReal angle, const Vector3D<TReal> &axis) {
      TReal s      = Math::Base<TReal>::Sin(angle);
      TReal c      = Cos(angle);
      TReal k      = Math::Base<TReal>::REAL_ONE - c;

      m_data[0][0] = c + k * axis.x * axis.x;
      m_data[1][0] = k * axis.x * axis.y - s * axis.z;
      m_data[2][0] = k * axis.x * axis.z + s * axis.y;
      m_data[0][1] = k * axis.x * axis.y + s * axis.z;
      m_data[1][1] = c + k * axis.y * axis.y;
      m_data[2][1] = k * axis.y * axis.z - s * axis.x;
      m_data[0][2] = k * axis.x * axis.z - s * axis.y;
      m_data[1][2] = k * axis.y * axis.z + s * axis.x;
      m_data[2][2] = c + k * axis.z * axis.z;

      return (*this);
    }

    void GetEulerAngles(TReal &x, TReal &y, TReal &z) const {
      TReal sy = m_data[2][0];
      if (sy < Math::Base<TReal>::REAL_ONE) {
        if (sy > -Math::Base<TReal>::REAL_ONE) {
          x = -Atan(m_data[2][1], m_data[2][2]);
          y = Asin(sy);
          z = -Atan(m_data[1][0], m_data[0][0]);
        } else {
          x = Math::Base<Real>::REAL_ZERO;
          y = -Math::Base<Real>::PI_OVER_TWO;
          z = Math::Base<Real>::Atan(m_data[0][1], m_data[1][1]);
        }
      } else {
        x = Math::Base<Real>::REAL_ZERO;
        y = Math::Base<Real>::PI_OVER_TWO;
        z = Math::Base<Real>::Atan(m_data[0][1], m_data[1][1]);
      }
    }

    Matrix3D &SetEulerAngles(TReal x, TReal y, TReal z) {
      TReal cx     = Cos(x);
      TReal cy     = Cos(y);
      TReal cz     = Cos(z);
      TReal sx     = Sin(x);
      TReal sy     = Sin(y);
      TReal sz     = Sin(z);

      m_data[0][0] = cy * cz;
      m_data[0][1] = cx * sz + sx * sy * cz;
      m_data[0][2] = sx * sz - cx * sy * cz;
      m_data[1][0] = -cy * sz;
      m_data[1][1] = cx * cz - sx * sy * sz;
      m_data[1][2] = sx * cz + cx * sy * sz;
      m_data[2][0] = sy;
      m_data[2][1] = -sx * cy;
      m_data[2][2] = cx * cy;

      return *this;
    }

    Matrix3D &SetScale(TReal t) {
      m_data[0][0] = m_data[1][1] = m_data[2][2] = t;
      m_data[0][1] = m_data[0][2] = m_data[1][0] = m_data[1][2] = m_data[2][0] = m_data[2][1] =
          Math::Base<TReal>::REAL_ZERO;

      return *this;
    }

    Matrix3D &SetScale(TReal r, TReal s, TReal t) {
      m_data[0][0] = r;
      m_data[1][1] = s;
      m_data[2][2] = t;
      m_data[0][1] = m_data[0][2] = m_data[1][0] = m_data[1][2] = m_data[2][0] = m_data[2][1] =
          Math::Base<TReal>::REAL_ZERO;

      return *this;
    }

    void SetSkew(const Vector3D<TReal> vec) {
      m_data[0][0] = 0;
      m_data[0][1] = -vec.z;
      m_data[0][2] = vec.y;

      m_data[1][0] = vec.z;
      m_data[1][1] = 0;
      m_data[1][2] = -vec.x;

      m_data[2][0] = -vec.y;
      m_data[2][1] = vec.x;
      m_data[2][2] = 0;
    }

    Matrix3D &
    Set3Component(const Vector3D<TReal> &c0, const Vector3D<TReal> &c1, const Vector3D<TReal> &c2) {
      m_data[0][0] = c0.x;
      m_data[0][1] = c1.x;
      m_data[0][2] = c2.x;
      m_data[1][0] = c0.y;
      m_data[1][1] = c1.y;
      m_data[1][2] = c2.y;
      m_data[2][0] = c0.z;
      m_data[2][1] = c1.z;
      m_data[2][2] = c2.z;

      return *this;
    }

    Matrix3D &Orthonormalize() {
      Vector3D<TReal> &x = (*this)[0];
      Vector3D<TReal> &y = (*this)[1];
      Vector3D<TReal> &z = (*this)[2];

      x.Normalize();
      (y = y - x * (x * y)).Normalize();
      (z = z - x * (x * z) - y * (y * z)).Normalize();

      return *this;
    }

    template <typename UReal>
    friend Matrix3D<UReal> operator*(const Matrix3D<UReal> &m1, const Matrix3D<UReal> &m2);
    template <typename UReal> friend Matrix3D<UReal> operator*(const Matrix3D<UReal> &m, UReal t);
    template <typename UReal> friend Matrix3D<UReal> operator/(const Matrix3D<UReal> &m, UReal t);
    template <typename UReal>
    friend Vector3D<UReal> operator*(const Matrix3D<UReal> &m, const Vector3D<UReal> &v);
    template <typename UReal>
    friend Vector3D<UReal> operator*(const Vector3D<UReal> &v, const Matrix3D<UReal> &m);
    template <typename UReal>
    friend bool operator==(const Matrix3D<UReal> &m1, const Matrix3D<UReal> &m2);
    template <typename UReal>
    friend bool operator!=(const Matrix3D<UReal> &m1, const Matrix3D<UReal> &m2);
    template <typename UReal>
    friend Matrix4D<UReal> operator*(const Matrix4D<UReal> &m1, const Matrix3D<UReal> &m2);

    static const Matrix3D MATRIX3D_ZERO;
    static const Matrix3D MATRIX3D_IDENTITY;
  };

  // friend Non-Members
  template <typename UReal>
  Matrix3D<UReal> operator*(const Matrix3D<UReal> &m1, const Matrix3D<UReal> &m2) {
    return (Matrix3D<UReal>(m1.m_data[0][0] * m2.m_data[0][0] + m1.m_data[0][1] * m2.m_data[1][0] +
                                m1.m_data[0][2] * m2.m_data[2][0],
                            m1.m_data[0][0] * m2.m_data[0][1] + m1.m_data[0][1] * m2.m_data[1][1] +
                                m1.m_data[0][2] * m2.m_data[2][1],
                            m1.m_data[0][0] * m2.m_data[0][2] + m1.m_data[0][1] * m2.m_data[1][2] +
                                m1.m_data[0][2] * m2.m_data[2][2],
                            m1.m_data[1][0] * m2.m_data[0][0] + m1.m_data[1][1] * m2.m_data[1][0] +
                                m1.m_data[1][2] * m2.m_data[2][0],
                            m1.m_data[1][0] * m2.m_data[0][1] + m1.m_data[1][1] * m2.m_data[1][1] +
                                m1.m_data[1][2] * m2.m_data[2][1],
                            m1.m_data[1][0] * m2.m_data[0][2] + m1.m_data[1][1] * m2.m_data[1][2] +
                                m1.m_data[1][2] * m2.m_data[2][2],
                            m1.m_data[2][0] * m2.m_data[0][0] + m1.m_data[2][1] * m2.m_data[1][0] +
                                m1.m_data[2][2] * m2.m_data[2][0],
                            m1.m_data[2][0] * m2.m_data[0][1] + m1.m_data[2][1] * m2.m_data[1][1] +
                                m1.m_data[2][2] * m2.m_data[2][1],
                            m1.m_data[2][0] * m2.m_data[0][2] + m1.m_data[2][1] * m2.m_data[1][2] +
                                m1.m_data[2][2] * m2.m_data[2][2]));
  }

  template <typename UReal> Matrix3D<UReal> operator*(const Matrix3D<UReal> &m, UReal t) {
    return (Matrix3D<UReal>(m.m_data[0][0] * t, m.m_data[1][0] * t, m.m_data[2][0] * t,
                            m.m_data[0][1] * t, m.m_data[1][1] * t, m.m_data[2][1] * t,
                            m.m_data[0][2] * t, m.m_data[1][2] * t, m.m_data[2][2] * t));
  }

  template <typename UReal> Matrix3D<UReal> operator/(const Matrix3D<UReal> &m, UReal t) {
    UReal f = Math::Base<UReal>::REAL_ONE / t;
    return (Matrix3D<UReal>(m.m_data[0][0] * f, m.m_data[1][0] * f, m.m_data[2][0] * f,
                            m.m_data[0][1] * f, m.m_data[1][1] * f, m.m_data[2][1] * f,
                            m.m_data[0][2] * f, m.m_data[1][2] * f, m.m_data[2][2] * f));
  }

  template <typename UReal>
  Vector3D<UReal> operator*(const Matrix3D<UReal> &m, const Vector3D<UReal> &v) {
    return (Vector3D<UReal>(m.m_data[0][0] * v.x + m.m_data[0][1] * v.y + m.m_data[0][2] * v.z,
                            m.m_data[1][0] * v.x + m.m_data[1][1] * v.y + m.m_data[1][2] * v.z,
                            m.m_data[2][0] * v.x + m.m_data[2][1] * v.y + m.m_data[2][2] * v.z));
  }

  template <typename UReal>
  Vector3D<UReal> operator*(const Vector3D<UReal> &v, const Matrix3D<UReal> &m) {
    return (Vector3D<UReal>(m.m_data[0][0] * v.x + m.m_data[1][0] * v.y + m.m_data[2][0] * v.z,
                            m.m_data[0][1] * v.x + m.m_data[1][1] * v.y + m.m_data[2][1] * v.z,
                            m.m_data[0][2] * v.x + m.m_data[1][2] * v.y + m.m_data[2][2] * v.z));
  }

  template <typename UReal> bool operator==(const Matrix3D<UReal> &m1, const Matrix3D<UReal> &m2) {
    return ((m1.m_data[0][0] == m2.m_data[0][0]) && (m1.m_data[0][1] == m2.m_data[0][1]) &&
            (m1.m_data[0][2] == m2.m_data[0][2]) && (m1.m_data[1][0] == m2.m_data[1][0]) &&
            (m1.m_data[1][1] == m2.m_data[1][1]) && (m1.m_data[1][2] == m2.m_data[1][2]) &&
            (m1.m_data[2][0] == m2.m_data[2][0]) && (m1.m_data[2][1] == m2.m_data[2][1]) &&
            (m1.m_data[2][2] == m2.m_data[2][2]));
  }

  template <typename UReal> bool operator!=(const Matrix3D<UReal> &m1, const Matrix3D<UReal> &m2) {
    return ((m1.m_data[0][0] != m2.m_data[0][0]) || (m1.m_data[0][1] != m2.m_data[0][1]) ||
            (m1.m_data[0][2] != m2.m_data[0][2]) || (m1.m_data[1][0] != m2.m_data[1][0]) ||
            (m1.m_data[1][1] != m2.m_data[1][1]) || (m1.m_data[1][2] != m2.m_data[1][2]) ||
            (m1.m_data[2][0] != m2.m_data[2][0]) || (m1.m_data[2][1] != m2.m_data[2][1]) ||
            (m1.m_data[2][2] != m2.m_data[2][2]));
  }

  // Non-friend Non-members
  template <typename UReal>
  inline Matrix3D<UReal> operator*(UReal scalar, const Matrix3D<UReal> &m) {
    return m * scalar;
  }

  template <typename UReal> UReal Determinant(const Matrix3D<UReal> &m) {
    return (m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) -
            m(0, 1) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)) +
            m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0)));
  }

  template <typename UReal> Matrix3D<UReal> Inverse(const Matrix3D<UReal> &m) {
    if (Math::Base<UReal>::Abs(Determinant(m) < Math::Base<UReal>::EPSILON))
      return Matrix3D<UReal>::MATRIX3D_ZERO;

    UReal n00 = m(0, 0);
    UReal n01 = m(0, 1);
    UReal n02 = m(0, 2);
    UReal n10 = m(1, 0);
    UReal n11 = m(1, 1);
    UReal n12 = m(1, 2);
    UReal n20 = m(2, 0);
    UReal n21 = m(2, 1);
    UReal n22 = m(2, 2);

    UReal p00 = n11 * n22 - n12 * n21;
    UReal p10 = n12 * n20 - n10 * n22;
    UReal p20 = n10 * n21 - n11 * n20;

    UReal t   = Math::Base<UReal>::REAL_ONE / (n00 * p00 + n01 * p10 + n02 * p20);

    return (Matrix3D<UReal>(p00 * t, (n02 * n21 - n01 * n22) * t, (n01 * n12 - n02 * n11) * t,
                            p10 * t, (n00 * n22 - n02 * n20) * t, (n02 * n10 - n00 * n12) * t,
                            p20 * t, (n01 * n20 - n00 * n21) * t, (n00 * n11 - n01 * n10) * t));
  }

  template <typename UReal> Matrix3D<UReal> Adjugate(const Matrix3D<UReal> &m) {
    UReal n00 = m(0, 0);
    UReal n01 = m(0, 1);
    UReal n02 = m(0, 2);
    UReal n10 = m(1, 0);
    UReal n11 = m(1, 1);
    UReal n12 = m(1, 2);
    UReal n20 = m(2, 0);
    UReal n21 = m(2, 1);
    UReal n22 = m(2, 2);

    return (Matrix3D<UReal>(n11 * n22 - n12 * n21, n02 * n21 - n01 * n22, n01 * n12 - n02 * n11,
                            n12 * n20 - n10 * n22, n00 * n22 - n02 * n20, n02 * n10 - n00 * n12,
                            n10 * n21 - n11 * n20, n01 * n20 - n00 * n21, n00 * n11 - n01 * n10));
  }

  template <typename UReal> Matrix3D<UReal> Transpose(const Matrix3D<UReal> &m) {
    return (Matrix3D<UReal>(m(0, 0), m(1, 0), m(2, 0), m(0, 1), m(1, 1), m(2, 1), m(0, 2), m(1, 2),
                            m(2, 2)));
  }

  template <typename UReal> bool IsZero(const Matrix3D<UReal> &m) {
    return m(0, 0) == 0 && m(0, 1) == 0 && m(0, 2) == 0 && m(1, 0) == 0 && m(1, 1) == 0 &&
           m(1, 2) == 0 && m(2, 0) == 0 && m(2, 1) == 0 && m(2, 2) == 0;
  }

  template <> inline const TE::Math::Matrix3D<F32>
      TE::Math::Matrix3D<F32>::MATRIX3D_ZERO(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  template <> inline const TE::Math::Matrix3D<F64>
      TE::Math::Matrix3D<F64>::MATRIX3D_ZERO(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

  template <> inline const TE::Math::Matrix3D<F32> TE::Math::Matrix3D<F32>::MATRIX3D_IDENTITY(1.0f,
                                                                                              0.0f,
                                                                                              0.0f,
                                                                                              0.0f,
                                                                                              1.0f,
                                                                                              0.0f,
                                                                                              0.0f,
                                                                                              0.0f,
                                                                                              1.0f);
  template <> inline const TE::Math::Matrix3D<F64>
      TE::Math::Matrix3D<F64>::MATRIX3D_IDENTITY(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
}

#endif
