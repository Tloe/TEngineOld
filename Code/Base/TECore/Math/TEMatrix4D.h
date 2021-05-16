/**
 *	\file		Matrix4D.h
 *  \author		Terje Loe
 *  \brief		Defenitions for Matrix4D class
 */

#ifndef TEMATRIX4D_H
#define TEMATRIX4D_H

#include <TEDataTypes.h>
#include <TEMathBase.h>
#include <assert.h>
#include <iostream>

namespace TE {
    namespace Math {
        template <typename TReal>
        class Matrix3D;
    }
    namespace Math {
        template <typename T>
        class Vector3D;
    }
    namespace Math {
        template <typename T>
        class Vector2D;
    }

    namespace Math {
        template <typename TReal>
        class Matrix4D {
          private:
            TReal m_data[4][4];

          public:
            Matrix4D() {}

            Matrix4D(const Vector3D<TReal> &c0, const Vector3D<TReal> &c1, const Vector3D<TReal> &c2) {
                m_data[0][0] = c0.x;
                m_data[0][1] = c0.y;
                m_data[0][2] = c0.z;
                m_data[1][0] = c1.x;
                m_data[1][1] = c1.y;
                m_data[1][2] = c1.z;
                m_data[2][0] = c2.x;
                m_data[2][1] = c2.y;
                m_data[2][2] = c2.z;
                m_data[0][3] = m_data[1][3] = m_data[2][3] = m_data[3][0] = m_data[3][1] = m_data[3][2] = Math::Base<Real>::REAL_ZERO;
                m_data[3][3]                                                                            = Math::Base<Real>::REAL_ONE;
            }

            Matrix4D(TReal m00, TReal m01, TReal m02, TReal m03, TReal m10, TReal m11, TReal m12, TReal m13, TReal m20, TReal m21, TReal m22, TReal m23, TReal m30, TReal m31, TReal m32, TReal m33) {
                m_data[0][0] = m00;
                m_data[0][1] = m01;
                m_data[0][2] = m02;
                m_data[0][3] = m03;
                m_data[1][0] = m10;
                m_data[1][1] = m11;
                m_data[1][2] = m12;
                m_data[1][3] = m13;
                m_data[2][0] = m20;
                m_data[2][1] = m21;
                m_data[2][2] = m22;
                m_data[2][3] = m23;
                m_data[3][0] = m30;
                m_data[3][1] = m31;
                m_data[3][2] = m32;
                m_data[3][3] = m33;
            }

            Matrix4D(TReal array[]) {
                size_t max = 16 * sizeof(TReal);
                assert(sizeof(&array) == max);
                memcpy(&m_data, array, max);
            }

            Matrix4D &Set(const Vector3D<TReal> &c0, const Vector3D<TReal> &c1, const Vector3D<TReal> &c2) {
                m_data[0][0] = c0.x;
                m_data[0][1] = c0.y;
                m_data[0][2] = c0.z;
                m_data[1][0] = c1.x;
                m_data[1][1] = c1.y;
                m_data[1][2] = c1.z;
                m_data[2][0] = c2.x;
                m_data[2][1] = c2.y;
                m_data[2][2] = c2.z;
                m_data[0][3] = m_data[1][3] = m_data[2][3] = m_data[3][0] = m_data[3][1] = m_data[3][2] = Math::Base<TReal>::REAL_ZERO;
                m_data[3][3]                                                                            = Math::Base<TReal>::REAL_ONE;
            }

            Matrix4D &Set3Component(const Vector3D<TReal> &c0, const Vector3D<TReal> &c1, const Vector3D<TReal> &c2) {
                m_data[0][0] = c0.x;
                m_data[0][1] = c1.x;
                m_data[0][2] = c2.x;
                m_data[1][0] = c0.y;
                m_data[1][1] = c1.y;
                m_data[1][2] = c2.y;
                m_data[2][0] = c0.z;
                m_data[2][1] = c1.z;
                m_data[2][2] = c2.z;
                m_data[0][3] = m_data[1][3] = m_data[2][3] = m_data[3][0] = m_data[3][1] = m_data[3][2] = Math::Base<TReal>::REAL_ZERO;
                m_data[3][3]                                                                            = Math::Base<TReal>::REAL_ONE;

                return *this;
            }

            Matrix4D &Set(TReal m00, TReal m01, TReal m02, TReal m03, TReal m10, TReal m11, TReal m12, TReal m13, TReal m20, TReal m21, TReal m22, TReal m23, TReal m30, TReal m31, TReal m32, TReal m33) {
                m_data[0][0] = m00;
                m_data[0][1] = m01;
                m_data[0][2] = m02;
                m_data[0][3] = m03;
                m_data[1][0] = m10;
                m_data[1][1] = m11;
                m_data[1][2] = m12;
                m_data[1][3] = m13;
                m_data[2][0] = m20;
                m_data[2][1] = m21;
                m_data[2][2] = m22;
                m_data[2][3] = m23;
                m_data[3][0] = m30;
                m_data[3][1] = m31;
                m_data[3][2] = m32;
                m_data[3][3] = m33;
            }

            TReal &operator()(unsigned i, unsigned j) {
                assert(i <= 3 && j <= 3 && "Subscription out of range.");
                return m_data[i][j];
            }

            const TReal &operator()(unsigned i, unsigned j) const {
                assert(i <= 3 && j <= 3 && "Subscription out of range.");
                return m_data[i][j];
            }

            Matrix4D<TReal> &operator=(const Matrix3D<TReal> &m) {
                m_data[0][0] = m.m_data[0][0];
                m_data[0][1] = m.m_data[0][1];
                m_data[0][2] = m.m_data[0][2];
                m_data[1][0] = m.m_data[1][0];
                m_data[1][1] = m.m_data[1][1];
                m_data[1][2] = m.m_data[1][2];
                m_data[2][0] = m.m_data[2][0];
                m_data[2][1] = m.m_data[2][1];
                m_data[2][2] = m.m_data[2][2];

                m_data[0][3] = m_data[1][3] = m_data[2][3] = m_data[3][0] = m_data[3][1] = m_data[3][2] = Math::Base<TReal>::REAL_ZERO;
                m_data[3][3]                                                                            = Math::Base<TReal>::REAL_ONE;

                return (*this);
            }

            Matrix4D &operator*=(const Matrix4D &m) {
                TReal x      = m_data[0][0];
                TReal y      = m_data[0][1];
                TReal z      = m_data[0][2];
                TReal w      = m_data[0][3];
                m_data[0][0] = x * m.m_data[0][0] + y * m.m_data[1][0] + z * m.m_data[2][0] + w * m.m_data[3][0];
                m_data[0][1] = x * m.m_data[0][1] + y * m.m_data[1][1] + z * m.m_data[2][1] + w * m.m_data[3][1];
                m_data[0][2] = x * m.m_data[0][2] + y * m.m_data[1][2] + z * m.m_data[2][2] + w * m.m_data[3][2];
                m_data[0][3] = x * m.m_data[0][3] + y * m.m_data[1][3] + z * m.m_data[2][3] + w * m.m_data[3][3];

                x            = m_data[1][0];
                y            = m_data[1][1];
                z            = m_data[1][2];
                w            = m_data[1][3];
                m_data[1][0] = x * m.m_data[0][0] + y * m.m_data[1][0] + z * m.m_data[2][0] + w * m.m_data[3][0];
                m_data[1][1] = x * m.m_data[0][1] + y * m.m_data[1][1] + z * m.m_data[2][1] + w * m.m_data[3][1];
                m_data[1][2] = x * m.m_data[0][2] + y * m.m_data[1][2] + z * m.m_data[2][2] + w * m.m_data[3][2];
                m_data[1][3] = x * m.m_data[0][3] + y * m.m_data[1][3] + z * m.m_data[2][3] + w * m.m_data[3][3];

                x            = m_data[2][0];
                y            = m_data[2][1];
                z            = m_data[2][2];
                w            = m_data[2][3];
                m_data[2][0] = x * m.m_data[0][0] + y * m.m_data[1][0] + z * m.m_data[2][0] + w * m.m_data[3][0];
                m_data[2][1] = x * m.m_data[0][1] + y * m.m_data[1][1] + z * m.m_data[2][1] + w * m.m_data[3][1];
                m_data[2][2] = x * m.m_data[0][2] + y * m.m_data[1][2] + z * m.m_data[2][2] + w * m.m_data[3][2];
                m_data[2][3] = x * m.m_data[0][3] + y * m.m_data[1][3] + z * m.m_data[2][3] + w * m.m_data[3][3];

                x            = m_data[3][0];
                y            = m_data[3][1];
                z            = m_data[3][2];
                w            = m_data[3][3];
                m_data[3][0] = x * m.m_data[0][0] + y * m.m_data[1][0] + z * m.m_data[2][0] + w * m.m_data[3][0];
                m_data[3][1] = x * m.m_data[0][1] + y * m.m_data[1][1] + z * m.m_data[2][1] + w * m.m_data[3][1];
                m_data[3][2] = x * m.m_data[0][2] + y * m.m_data[1][2] + z * m.m_data[2][2] + w * m.m_data[3][2];
                m_data[3][3] = x * m.m_data[0][3] + y * m.m_data[1][3] + z * m.m_data[2][3] + w * m.m_data[3][3];

                return (*this);
            }

            Matrix4D<TReal> &operator*=(const Matrix3D<TReal> &m) {
                TReal x      = m_data[0][0];
                TReal y      = m_data[0][1];
                TReal z      = m_data[0][2];
                m_data[0][0] = x * m.m_data[0][0] + y * m.m_data[1][0] + z * m.m_data[2][0];
                m_data[0][1] = x * m.m_data[0][1] + y * m.m_data[1][1] + z * m.m_data[2][1];
                m_data[0][2] = x * m.m_data[0][2] + y * m.m_data[1][2] + z * m.m_data[2][2];

                x            = m_data[1][0];
                y            = m_data[1][1];
                z            = m_data[1][2];
                m_data[1][0] = x * m.m_data[0][0] + y * m.m_data[1][0] + z * m.m_data[2][0];
                m_data[1][1] = x * m.m_data[0][1] + y * m.m_data[1][1] + z * m.m_data[2][1];
                m_data[1][2] = x * m.m_data[0][2] + y * m.m_data[1][2] + z * m.m_data[2][2];

                x            = m_data[2][0];
                y            = m_data[2][1];
                z            = m_data[2][2];
                m_data[2][0] = x * m.m_data[0][0] + y * m.m_data[1][0] + z * m.m_data[2][0];
                m_data[2][1] = x * m.m_data[0][1] + y * m.m_data[1][1] + z * m.m_data[2][1];
                m_data[2][2] = x * m.m_data[0][2] + y * m.m_data[1][2] + z * m.m_data[2][2];

                x            = m_data[3][0];
                y            = m_data[3][1];
                z            = m_data[3][2];
                m_data[3][0] = x * m.m_data[0][0] + y * m.m_data[1][0] + z * m.m_data[2][0];
                m_data[3][1] = x * m.m_data[0][1] + y * m.m_data[1][1] + z * m.m_data[2][1];
                m_data[3][2] = x * m.m_data[0][2] + y * m.m_data[1][2] + z * m.m_data[2][2];

                return (*this);
            }

            Matrix4D &SetIdentity() {
                m_data[0][0] = m_data[1][1] = m_data[2][2] = m_data[3][3] = Math::Base<TReal>::REAL_ONE;
                m_data[1][0] = m_data[2][0] = m_data[3][0] = m_data[0][1] = m_data[2][1] = m_data[3][1] = m_data[0][2] = m_data[1][2] = m_data[3][2] = m_data[0][3] = m_data[1][3] = m_data[2][3] = Math::Base<TReal>::REAL_ZERO;
                return (*this);
            }

            Matrix4D &SetRotationAboutX(TReal angle) {
                TReal s      = Math::Base<TReal>::Sin(angle);
                m_data[0][0] = m_data[3][3] = Math::Base<TReal>::REAL_ONE;
                m_data[0][1] = m_data[0][2] = m_data[0][3] = m_data[1][0] = m_data[1][3] = m_data[2][0] = m_data[2][3] = m_data[3][0] = m_data[3][1] = m_data[3][2] = Math::Base<TReal>::REAL_ZERO;
                m_data[1][1] = m_data[2][2] = Math::Base<TReal>::Cos(angle);
                m_data[2][1]                = -s;
                m_data[1][2]                = s;

                return (*this);
            }

            Matrix4D &SetRotationAboutY(TReal angle) {
                TReal s      = Sin(angle);
                m_data[1][1] = m_data[3][3] = 1.0F;
                m_data[0][1] = m_data[0][3] = m_data[1][0] = m_data[1][2] = m_data[1][3] = m_data[2][1] = m_data[2][3] = m_data[3][0] = m_data[3][1] = m_data[3][2] = Math::Base<TReal>::REAL_ZERO;
                m_data[0][0] = m_data[2][2] = Math::Base<TReal>::Cos(angle);
                m_data[2][0]                = s;
                m_data[0][2]                = -s;

                return (*this);
            }

            Matrix4D &SetRotationAboutZ(TReal angle) {
                TReal s      = Sin(angle);
                m_data[2][2] = m_data[3][3] = Math::Base<TReal>::REAL_ONE;
                m_data[0][2] = m_data[0][3] = m_data[1][2] = m_data[1][3] = m_data[2][0] = m_data[2][1] = m_data[2][3] = m_data[3][0] = m_data[3][1] = m_data[3][2] = Math::Base<TReal>::REAL_ZERO;
                m_data[0][0] = m_data[1][1] = Math::Base<TReal>::Cos(angle);
                m_data[1][0]                = -s;
                m_data[0][1]                = s;

                return (*this);
            }

            Matrix4D &SetRotationAboutAxis(TReal angle, const Vector3D<TReal> &axis) {
                TReal s      = Math::Base<TReal>::Sin(angle);
                TReal c      = Math::Base<TReal>::Cos(angle);
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

                m_data[3][3] = Math::Base<TReal>::REAL_ONE;
                m_data[0][3] = m_data[1][3] = m_data[2][3] = m_data[3][0] = m_data[3][1] = m_data[3][2] = Math::Base<TReal>::REAL_ZERO;

                return (*this);
            }

            void GetEulerAngles(TReal &x, TReal &y, TReal &z) const {
                TReal sy = m_data[2][0];
                if (sy < Math::Base<TReal>::REAL_ONE) {
                    if (sy > -Math::Base<TReal>::REAL_ONE) {
                        x = -Math::Base<TReal>::Atan(m_data[2][1], m_data[2][2]);
                        y = Math::Base<TReal>::Asin(sy);
                        z = -Math::Base<TReal>::Atan(m_data[1][0], m_data[0][0]);
                    } else {
                        x = Math::Base<TReal>::REAL_ZERO;
                        y = -Math::Base<TReal>::HALF_PI;
                        z = Math::Base<TReal>::Atan(m_data[0][1], m_data[1][1]);
                    }
                } else {
                    x = Math::Base<TReal>::REAL_ZERO;
                    y = Math::Base<TReal>::HALF_PI;
                    z = Math::Base<TReal>::Atan(m_data[0][1], m_data[1][1]);
                }
            }

            Matrix4D &SetEulerAngles(TReal x, TReal y, TReal z) {
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

                return (*this);
            }

            Matrix4D &SetScale(TReal t) {
                m_data[0][0] = m_data[1][1] = m_data[2][2] = t;
                m_data[3][3]                               = Math::Base<TReal>::REAL_ONE;
                m_data[1][0] = m_data[2][0] = m_data[3][0] = m_data[0][1] = m_data[2][1] = m_data[3][1] = m_data[0][2] = m_data[1][2] = m_data[3][2] = m_data[0][3] = m_data[1][3] = m_data[2][3] = Math::Base<TReal>::REAL_ZERO;
                return (*this);
            }

            Matrix4D &SetScale(TReal r, TReal s, TReal t) {
                m_data[0][0] = r;
                m_data[1][1] = s;
                m_data[2][2] = t;
                m_data[3][3] = Math::Base<TReal>::REAL_ONE;
                m_data[1][0] = m_data[2][0] = m_data[3][0] = m_data[0][1] = m_data[2][1] = m_data[3][1] = m_data[0][2] = m_data[1][2] = m_data[3][2] = m_data[0][3] = m_data[1][3] = m_data[2][3] = Math::Base<TReal>::REAL_ZERO;
                return (*this);
            }

            /*void SetSkew(const Vector3D<TReal> vec)
            {
                    m_data[0][0]  = 0;
                    m_data[0][1]  = -vec.z;
                    m_data[0][2]  = vec.y;
                    m_data[0][3]  = 0;

                    m_data[1][0]  = vec.z;
                    m_data[1][1]  = 0;
                    m_data[1][2]  = -vec.x;
                    m_data[1][3]  = 0;

                    m_data[2][0]  = -vec.y;
                    m_data[2][1]  = vec.x;
                    m_data[2][2] = 0;
                    m_data[2][3]  = 0;

                    m_data[3][0]  = 0;
                    m_data[3][1]  = 0;
                    m_data[3][2]  = 0;
                    m_data[3][3]  = 1;
            }*/

            Matrix4D &SetTranslation(const Vector3D<TReal> &t) {
                m_data[3][0] = t.x;
                m_data[3][1] = t.y;
                m_data[3][2] = t.z;
                m_data[0][0] = m_data[1][1] = m_data[2][2] = m_data[3][3] = Math::Base<TReal>::REAL_ONE;
                m_data[1][0] = m_data[2][0] = m_data[0][1] = m_data[2][1] = m_data[0][2] = m_data[1][2] = m_data[0][3] = m_data[1][3] = m_data[2][3] = Math::Base<TReal>::REAL_ZERO;
                return (*this);
            }

            template <typename UReal>
            friend Matrix4D<UReal> operator*(const Matrix4D<UReal> &m1, const Matrix4D<UReal> &m2);
            template <typename UReal>
            friend Matrix4D<UReal> operator*(const Matrix4D<UReal> &m1, const Matrix3D<UReal> &m2);
            template <typename UReal>
            friend Vector3D<UReal> operator*(const Matrix4D<UReal> &m, const Vector3D<UReal> &v);
            template <typename UReal>
            friend Vector3D<UReal> operator*(const Vector3D<UReal> &v, const Matrix4D<UReal> &m);
            template <typename UReal>
            friend Vector2D<UReal> operator*(const Matrix4D<UReal> &m, const Vector2D<UReal> &v);
            template <typename UReal>
            friend Vector2D<UReal> operator*(const Vector2D<UReal> &v, const Matrix4D<UReal> &m);
            template <typename UReal>
            friend bool operator==(const Matrix4D<UReal> &m1, const Matrix4D<UReal> &m2);
            template <typename UReal>
            friend bool operator!=(const Matrix4D<UReal> &m1, const Matrix4D<UReal> &m2);

            static const Matrix4D MATRIX4D_ZERO;
            static const Matrix4D MATRIX4D_IDENTITY;
        };

        // friend Non-Members
        template <typename UReal>
        Matrix4D<UReal> operator*(const Matrix4D<UReal> &m1, const Matrix4D<UReal> &m2) {
            return (Matrix4D<UReal>(m1.m_data[0][0] * m2.m_data[0][0] + m1.m_data[0][1] * m2.m_data[1][0] + m1.m_data[0][2] * m2.m_data[2][0] + m1.m_data[0][3] * m2.m_data[3][0],
                                    m1.m_data[0][0] * m2.m_data[0][1] + m1.m_data[0][1] * m2.m_data[1][1] + m1.m_data[0][2] * m2.m_data[2][1] + m1.m_data[0][3] * m2.m_data[3][1],
                                    m1.m_data[0][0] * m2.m_data[0][2] + m1.m_data[0][1] * m2.m_data[1][2] + m1.m_data[0][2] * m2.m_data[2][2] + m1.m_data[0][3] * m2.m_data[3][2],
                                    m1.m_data[0][0] * m2.m_data[0][3] + m1.m_data[0][1] * m2.m_data[1][3] + m1.m_data[0][2] * m2.m_data[2][3] + m1.m_data[0][3] * m2.m_data[3][3],

                                    m1.m_data[1][0] * m2.m_data[0][0] + m1.m_data[1][1] * m2.m_data[1][0] + m1.m_data[1][2] * m2.m_data[2][0] + m1.m_data[1][3] * m2.m_data[3][0],
                                    m1.m_data[1][0] * m2.m_data[0][1] + m1.m_data[1][1] * m2.m_data[1][1] + m1.m_data[1][2] * m2.m_data[2][1] + m1.m_data[1][3] * m2.m_data[3][1],
                                    m1.m_data[1][0] * m2.m_data[0][2] + m1.m_data[1][1] * m2.m_data[1][2] + m1.m_data[1][2] * m2.m_data[2][2] + m1.m_data[1][3] * m2.m_data[3][2],
                                    m1.m_data[1][0] * m2.m_data[0][3] + m1.m_data[1][1] * m2.m_data[1][3] + m1.m_data[1][2] * m2.m_data[2][3] + m1.m_data[1][3] * m2.m_data[3][3],

                                    m1.m_data[2][0] * m2.m_data[0][0] + m1.m_data[2][1] * m2.m_data[1][0] + m1.m_data[2][2] * m2.m_data[2][0] + m1.m_data[2][3] * m2.m_data[3][0],
                                    m1.m_data[2][0] * m2.m_data[0][1] + m1.m_data[2][1] * m2.m_data[1][1] + m1.m_data[2][2] * m2.m_data[2][1] + m1.m_data[2][3] * m2.m_data[3][1],
                                    m1.m_data[2][0] * m2.m_data[0][2] + m1.m_data[2][1] * m2.m_data[1][2] + m1.m_data[2][2] * m2.m_data[2][2] + m1.m_data[2][3] * m2.m_data[3][2],
                                    m1.m_data[2][0] * m2.m_data[0][3] + m1.m_data[2][1] * m2.m_data[1][3] + m1.m_data[2][2] * m2.m_data[2][3] + m1.m_data[2][3] * m2.m_data[3][3],

                                    m1.m_data[3][0] * m2.m_data[0][0] + m1.m_data[3][1] * m2.m_data[1][0] + m1.m_data[3][2] * m2.m_data[2][0] + m1.m_data[3][3] * m2.m_data[3][0],
                                    m1.m_data[3][0] * m2.m_data[0][1] + m1.m_data[3][1] * m2.m_data[1][1] + m1.m_data[3][2] * m2.m_data[2][1] + m1.m_data[3][3] * m2.m_data[3][1],
                                    m1.m_data[3][0] * m2.m_data[0][2] + m1.m_data[3][1] * m2.m_data[1][2] + m1.m_data[3][2] * m2.m_data[2][2] + m1.m_data[3][3] * m2.m_data[3][2],
                                    m1.m_data[3][0] * m2.m_data[0][3] + m1.m_data[3][1] * m2.m_data[1][3] + m1.m_data[3][2] * m2.m_data[2][3] + m1.m_data[3][3] * m2.m_data[3][3]));
        }

        template <typename UReal>
        Matrix4D<UReal> operator*(const Matrix4D<UReal> &m1, const Matrix3D<UReal> &m2) {
            return (Matrix4D<UReal>(m1.m_data[0][0] * m2.m_data[0][0] + m1.m_data[0][1] * m2.m_data[1][0] + m1.m_data[0][2] * m2.m_data[2][0],
                                    m1.m_data[0][0] * m2.m_data[0][1] + m1.m_data[0][1] * m2.m_data[1][1] + m1.m_data[0][2] * m2.m_data[2][1],
                                    m1.m_data[0][0] * m2.m_data[0][2] + m1.m_data[0][1] * m2.m_data[1][2] + m1.m_data[0][2] * m2.m_data[2][2],
                                    m1.m_data[0][3],
                                    m1.m_data[1][0] * m2.m_data[0][0] + m1.m_data[1][1] * m2.m_data[1][0] + m1.m_data[1][2] * m2.m_data[2][0],
                                    m1.m_data[1][0] * m2.m_data[0][1] + m1.m_data[1][1] * m2.m_data[1][1] + m1.m_data[1][2] * m2.m_data[2][1],
                                    m1.m_data[1][0] * m2.m_data[0][2] + m1.m_data[1][1] * m2.m_data[1][2] + m1.m_data[1][2] * m2.m_data[2][2],
                                    m1.m_data[1][3],
                                    m1.m_data[2][0] * m2.m_data[0][0] + m1.m_data[2][1] * m2.m_data[1][0] + m1.m_data[2][2] * m2.m_data[2][0],
                                    m1.m_data[2][0] * m2.m_data[0][1] + m1.m_data[2][1] * m2.m_data[1][1] + m1.m_data[2][2] * m2.m_data[2][1],
                                    m1.m_data[2][0] * m2.m_data[0][2] + m1.m_data[2][1] * m2.m_data[1][2] + m1.m_data[2][2] * m2.m_data[2][2],
                                    m1.m_data[2][3],
                                    m1.m_data[3][0] * m2.m_data[0][0] + m1.m_data[3][1] * m2.m_data[1][0] + m1.m_data[3][2] * m2.m_data[2][0],
                                    m1.m_data[3][0] * m2.m_data[0][1] + m1.m_data[3][1] * m2.m_data[1][1] + m1.m_data[3][2] * m2.m_data[2][1],
                                    m1.m_data[3][0] * m2.m_data[0][2] + m1.m_data[3][1] * m2.m_data[1][2] + m1.m_data[3][2] * m2.m_data[2][2],
                                    m1.m_data[3][3]));
        }

        template <typename UReal>
        Vector3D<UReal> operator*(const Vector3D<UReal> &v, const Matrix4D<UReal> &m) {
            return (Vector3D<UReal>(m.m_data[0][0] * v.x + m.m_data[1][0] * v.y + m.m_data[2][0] * v.z + m.m_data[0][3],
                                    m.m_data[0][1] * v.x + m.m_data[1][1] * v.y + m.m_data[2][1] * v.z + m.m_data[1][3],
                                    m.m_data[0][2] * v.x + m.m_data[1][2] * v.y + m.m_data[2][2] * v.z + +m.m_data[2][3]));
        }

        template <typename UReal>
        Vector3D<UReal> operator*(const Matrix4D<UReal> &m, const Vector3D<UReal> &v) {
            return (Vector3D<UReal>(m.m_data[0][0] * v.x + m.m_data[1][0] * v.y + m.m_data[2][0] * v.z + m.m_data[0][3],
                                    m.m_data[0][1] * v.x + m.m_data[1][1] * v.y + m.m_data[2][1] * v.z + m.m_data[1][3],
                                    m.m_data[0][2] * v.x + m.m_data[1][2] * v.y + m.m_data[2][2] * v.z + m.m_data[2][3]));
        }

        template <typename UReal>
        Vector2D<UReal> operator*(const Matrix4D<UReal> &m, const Vector2D<UReal> &v) {
            return (Vector2D<UReal>(m.m_data[0][0] * v.x + m.m_data[0][1] * v.y,
                                    m.m_data[1][0] * v.x + m.m_data[1][1] * v.y));
        }

        template <typename UReal>
        Vector2D<UReal> operator*(const Vector2D<UReal> &v, const Matrix4D<UReal> &m) {
            return (Vector2D<UReal>(m.m_data[0][0] * v.x + m.m_data[1][0] * v.y,
                                    m.m_data[0][1] * v.x + m.m_data[1][1] * v.y));
        }

        template <typename UReal>
        bool operator==(const Matrix4D<UReal> &m1, const Matrix4D<UReal> &m2) {
            return ((m1.m_data[0][0] == m2.m_data[0][0]) && (m1.m_data[0][1] == m2.m_data[0][1]) && (m1.m_data[0][2] == m2.m_data[0][2]) && (m1.m_data[0][3] == m2.m_data[0][3]) && (m1.m_data[1][0] == m2.m_data[1][0]) && (m1.m_data[1][1] == m2.m_data[1][1]) && (m1.m_data[1][2] == m2.m_data[1][2]) && (m1.m_data[1][3] == m2.m_data[1][3]) && (m1.m_data[2][0] == m2.m_data[2][0]) && (m1.m_data[2][1] == m2.m_data[2][1]) && (m1.m_data[2][2] == m2.m_data[2][2]) && (m1.m_data[2][3] == m2.m_data[2][3]) && (m1.m_data[3][0] == m2.m_data[3][0]) && (m1.m_data[3][1] == m2.m_data[3][1]) && (m1.m_data[3][2] == m2.m_data[3][2]) && (m1.m_data[3][3] == m2.m_data[3][3]));
        }

        template <typename UReal>
        bool operator!=(const Matrix4D<UReal> &m1, const Matrix4D<UReal> &m2) {
            return ((m1.m_data[0][0] != m2.m_data[0][0]) || (m1.m_data[0][1] != m2.m_data[0][1]) || (m1.m_data[0][2] != m2.m_data[0][2]) || (m1.m_data[0][3] != m2.m_data[0][3]) || (m1.m_data[1][0] != m2.m_data[1][0]) || (m1.m_data[1][1] != m2.m_data[1][1]) || (m1.m_data[1][2] != m2.m_data[1][2]) || (m1.m_data[1][3] != m2.m_data[1][3]) || (m1.m_data[2][0] != m2.m_data[2][0]) || (m1.m_data[2][1] != m2.m_data[2][1]) || (m1.m_data[2][2] != m2.m_data[2][2]) || (m1.m_data[2][3] != m2.m_data[2][3]) || (m1.m_data[3][0] != m2.m_data[3][0]) || (m1.m_data[3][1] != m2.m_data[3][1]) || (m1.m_data[3][2] != m2.m_data[3][2]) || (m1.m_data[3][3] != m2.m_data[3][3]));
        }

        // Non-friend Non-member
        template <typename UReal>
        std::ostream &operator<<(std::ostream &ostr, const Matrix4D<UReal> &m) {
            ostr << m(0, 0) << " " << m(0, 1) << " " << m(0, 2) << " " << m(0, 3) << std::endl
                 << m(1, 0) << " " << m(1, 1) << " " << m(1, 2) << " " << m(1, 3) << std::endl
                 << m(2, 0) << " " << m(2, 1) << " " << m(2, 2) << " " << m(2, 3) << std::endl
                 << m(3, 0) << " " << m(3, 1) << " " << m(3, 2) << " " << m(3, 3) << std::endl;

            return ostr;
        }

        template <typename UReal>
        UReal Determinant(const Matrix4D<UReal> &m) {
            UReal n00 = m(0, 0);
            UReal n01 = m(0, 1);
            UReal n02 = m(0, 2);
            UReal n03 = m(0, 3);

            UReal n10 = m(1, 0);
            UReal n11 = m(1, 1);
            UReal n12 = m(1, 2);
            UReal n13 = m(1, 3);

            UReal n20 = m(2, 0);
            UReal n21 = m(2, 1);
            UReal n22 = m(2, 2);
            UReal n23 = m(2, 3);

            UReal n30 = m(3, 0);
            UReal n31 = m(3, 1);
            UReal n32 = m(3, 2);
            UReal n33 = m(3, 3);

            return (n00 * (n11 * (n22 * n33 - n23 * n32) + n12 * (n23 * n31 - n21 * n33) + n13 * (n21 * n32 - n22 * n31)) +
                    n01 * (n10 * (n23 * n32 - n22 * n33) + n12 * (n20 * n33 - n23 * n30) + n13 * (n22 * n30 - n20 * n32)) +
                    n02 * (n10 * (n21 * n33 - n23 * n31) + n11 * (n23 * n30 - n20 * n33) + n13 * (n20 * n31 - n21 * n30)) +
                    n03 * (n10 * (n22 * n31 - n21 * n32) + n11 * (n20 * n32 - n22 * n30) + n12 * (n21 * n30 - n20 * n31)));
        }

        template <typename UReal>
        Matrix4D<UReal> Inverse(const Matrix4D<UReal> &m) {
            UReal n00 = m(0, 0);
            UReal n01 = m(0, 1);
            UReal n02 = m(0, 2);
            UReal n03 = m(0, 3);

            UReal n10 = m(1, 0);
            UReal n11 = m(1, 1);
            UReal n12 = m(1, 2);
            UReal n13 = m(1, 3);

            UReal n20 = m(2, 0);
            UReal n21 = m(2, 1);
            UReal n22 = m(2, 2);
            UReal n23 = m(2, 3);

            UReal n30 = m(3, 0);
            UReal n31 = m(3, 1);
            UReal n32 = m(3, 2);
            UReal n33 = m(3, 3);

            UReal p00 = n11 * (n22 * n33 - n23 * n32) + n12 * (n23 * n31 - n21 * n33) + n13 * (n21 * n32 - n22 * n31);
            UReal p10 = n10 * (n23 * n32 - n22 * n33) + n12 * (n20 * n33 - n23 * n30) + n13 * (n22 * n30 - n20 * n32);
            UReal p20 = n10 * (n21 * n33 - n23 * n31) + n11 * (n23 * n30 - n20 * n33) + n13 * (n20 * n31 - n21 * n30);
            UReal p30 = n10 * (n22 * n31 - n21 * n32) + n11 * (n20 * n32 - n22 * n30) + n12 * (n21 * n30 - n20 * n31);

            UReal t   = Math::Base<UReal>::REAL_ONE / (n00 * p00 + n01 * p10 + n02 * p20 + n03 * p30);

            return (Matrix4D<UReal>(p00 * t,
                                    (n01 * (n23 * n32 - n22 * n33) + n02 * (n21 * n33 - n23 * n31) + n03 * (n22 * n31 - n21 * n32)) * t,
                                    (n01 * (n12 * n33 - n13 * n32) + n02 * (n13 * n31 - n11 * n33) + n03 * (n11 * n32 - n12 * n31)) * t,
                                    (n01 * (n13 * n22 - n12 * n23) + n02 * (n11 * n23 - n13 * n21) + n03 * (n12 * n21 - n11 * n22)) * t,
                                    p10 * t,
                                    (n00 * (n22 * n33 - n23 * n32) + n02 * (n23 * n30 - n20 * n33) + n03 * (n20 * n32 - n22 * n30)) * t,
                                    (n00 * (n13 * n32 - n12 * n33) + n02 * (n10 * n33 - n13 * n30) + n03 * (n12 * n30 - n10 * n32)) * t,
                                    (n00 * (n12 * n23 - n13 * n22) + n02 * (n13 * n20 - n10 * n23) + n03 * (n10 * n22 - n12 * n20)) * t,
                                    p20 * t,
                                    (n00 * (n23 * n31 - n21 * n33) + n01 * (n20 * n33 - n23 * n30) + n03 * (n21 * n30 - n20 * n31)) * t,
                                    (n00 * (n11 * n33 - n13 * n31) + n01 * (n13 * n30 - n10 * n33) + n03 * (n10 * n31 - n11 * n30)) * t,
                                    (n00 * (n13 * n21 - n11 * n23) + n01 * (n10 * n23 - n13 * n20) + n03 * (n11 * n20 - n10 * n21)) * t,
                                    p30 * t,
                                    (n00 * (n21 * n32 - n22 * n31) + n01 * (n22 * n30 - n20 * n32) + n02 * (n20 * n31 - n21 * n30)) * t,
                                    (n00 * (n12 * n31 - n11 * n32) + n01 * (n10 * n32 - n12 * n30) + n02 * (n11 * n30 - n10 * n31)) * t,
                                    (n00 * (n11 * n22 - n12 * n21) + n01 * (n12 * n20 - n10 * n22) + n02 * (n10 * n21 - n11 * n20)) * t));
        }

        template <typename UReal>
        Matrix4D<UReal> Adjugate(const Matrix4D<UReal> &m) {
            UReal n00 = m(0, 0);
            UReal n01 = m(0, 1);
            UReal n02 = m(0, 2);
            UReal n03 = m(0, 3);

            UReal n10 = m(1, 0);
            UReal n11 = m(1, 1);
            UReal n12 = m(1, 2);
            UReal n13 = m(1, 3);

            UReal n20 = m(2, 0);
            UReal n21 = m(2, 1);
            UReal n22 = m(2, 2);
            UReal n23 = m(2, 3);

            UReal n30 = m(3, 0);
            UReal n31 = m(3, 1);
            UReal n32 = m(3, 2);
            UReal n33 = m(3, 3);

            return (Matrix4D<UReal>(n11 * (n22 * n33 - n23 * n32) + n12 * (n23 * n31 - n21 * n33) + n13 * (n21 * n32 - n22 * n31),
                                    n01 * (n23 * n32 - n22 * n33) + n02 * (n21 * n33 - n23 * n31) + n03 * (n22 * n31 - n21 * n32),
                                    n01 * (n12 * n33 - n13 * n32) + n02 * (n13 * n31 - n11 * n33) + n03 * (n11 * n32 - n12 * n31),
                                    n01 * (n13 * n22 - n12 * n23) + n02 * (n11 * n23 - n13 * n21) + n03 * (n12 * n21 - n11 * n22),
                                    n10 * (n23 * n32 - n22 * n33) + n12 * (n20 * n33 - n23 * n30) + n13 * (n22 * n30 - n20 * n32),
                                    n00 * (n22 * n33 - n23 * n32) + n02 * (n23 * n30 - n20 * n33) + n03 * (n20 * n32 - n22 * n30),
                                    n00 * (n13 * n32 - n12 * n33) + n02 * (n10 * n33 - n13 * n30) + n03 * (n12 * n30 - n10 * n32),
                                    n00 * (n12 * n23 - n13 * n22) + n02 * (n13 * n20 - n10 * n23) + n03 * (n10 * n22 - n12 * n20),
                                    n10 * (n21 * n33 - n23 * n31) + n11 * (n23 * n30 - n20 * n33) + n13 * (n20 * n31 - n21 * n30),
                                    n00 * (n23 * n31 - n21 * n33) + n01 * (n20 * n33 - n23 * n30) + n03 * (n21 * n30 - n20 * n31),
                                    n00 * (n11 * n33 - n13 * n31) + n01 * (n13 * n30 - n10 * n33) + n03 * (n10 * n31 - n11 * n30),
                                    n00 * (n13 * n21 - n11 * n23) + n01 * (n10 * n23 - n13 * n20) + n03 * (n11 * n20 - n10 * n21),
                                    n10 * (n22 * n31 - n21 * n32) + n11 * (n20 * n32 - n22 * n30) + n12 * (n21 * n30 - n20 * n31),
                                    n00 * (n21 * n32 - n22 * n31) + n01 * (n22 * n30 - n20 * n32) + n02 * (n20 * n31 - n21 * n30),
                                    n00 * (n12 * n31 - n11 * n32) + n01 * (n10 * n32 - n12 * n30) + n02 * (n11 * n30 - n10 * n31),
                                    n00 * (n11 * n22 - n12 * n21) + n01 * (n12 * n20 - n10 * n22) + n02 * (n10 * n21 - n11 * n20)));
        }

        template <typename UReal>
        Matrix4D<UReal> Transpose(const Matrix4D<UReal> &m) {
            return (Matrix4D<UReal>(m(0, 0), m(1, 0), m(2, 0), m(3, 0), m(0, 1), m(1, 1), m(2, 1), m(3, 1), m(0, 2), m(1, 2), m(2, 2), m(3, 2), m(0, 3), m(1, 3), m(2, 3), m(3, 3)));
        }

        template <typename UReal>
        bool IsZero(const Matrix4D<UReal> &m) {
            return m(0, 0) == 0 &&
                   m(0, 1) == 0 &&
                   m(0, 2) == 0 &&
                   m(0, 3) == 0 &&
                   m(1, 0) == 0 &&
                   m(1, 1) == 0 &&
                   m(1, 2) == 0 &&
                   m(1, 3) == 0 &&
                   m(2, 0) == 0 &&
                   m(2, 1) == 0 &&
                   m(2, 2) == 0 &&
                   m(2, 3) == 0 &&
                   m(3, 0) == 0 &&
                   m(3, 1) == 0 &&
                   m(3, 2) == 0 &&
                   m(3, 3) == 0;
        }

        template <>
        inline const TE::Math::Matrix4D<F32> TE::Math::Matrix4D<F32>::MATRIX4D_ZERO(0.0f, 0.0f, 0.0f, 0.0f,
                                                                                    0.0f, 0.0f, 0.0f, 0.0f,
                                                                                    0.0f, 0.0f, 0.0f, 0.0f,
                                                                                    0.0f, 0.0f, 0.0f, 0.0f);
        template <>
        inline const TE::Math::Matrix4D<F64> TE::Math::Matrix4D<F64>::MATRIX4D_ZERO(0.0, 0.0, 0.0, 0.0,
                                                                                    0.0, 0.0, 0.0, 0.0,
                                                                                    0.0, 0.0, 0.0, 0.0,
                                                                                    0.0, 0.0, 0.0, 0.0);

        template <>
        inline const TE::Math::Matrix4D<F32> TE::Math::Matrix4D<F32>::MATRIX4D_IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
                                                                                        0.0f, 1.0f, 0.0f, 0.0f,
                                                                                        0.0f, 0.0f, 1.0f, 0.0f,
                                                                                        0.0f, 0.0f, 0.0f, 1.0f);
        template <>
        inline const TE::Math::Matrix4D<F64> TE::Math::Matrix4D<F64>::MATRIX4D_IDENTITY(1.0, 0.0, 0.0, 0.0,
                                                                                        0.0, 1.0, 0.0, 0.0,
                                                                                        0.0, 0.0, 1.0, 0.0,
                                                                                        0.0, 0.0, 0.0, 1.0);
    }
}

#endif
