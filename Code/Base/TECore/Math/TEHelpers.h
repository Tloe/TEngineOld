#ifndef TEHELPERS_H
#define TEHELPERS_H

#include <TEDataTypes.h>
#include <cstring>

namespace TE
{
	namespace Math { template<typename T> class Vector3D; }
	namespace Math { template<typename T> class Quaternion; }
	namespace Math { template<typename T> class Matrix4D; }
	namespace Math { template<typename T> class Matrix3D; }

	namespace Math
	{
		template <typename Real>
		class Helpers
		{
		public:
			/**
			 *  \brief		calculates a covariance matrix from points
			 *	\Param		Matrix4D<Real> & cov
			 *	\Param		const Real * vertexData
			 *	\Param		unsigned vDataCount
			 *	\return		void
			 */	
			static void covarianceMatrixOfPts(Matrix4D<Real> &cov, const Real *vertexData, U64 dataCount);
	
			/**
			 *  \brief		calculates covariance matrix from triangles. (NOT WORKING PROPERLY)
			 *	\Param		Matrix4D<Real> & cov
			 *	\Param		const Real * vertexData
			 *	\Param		unsigned vDataCount
			 *	\return		void
			 */	
			//static  void covarianceMatrixOfTris(Matrix4D<Real> &cov, const Real *vertexData, unsigned vDataCount);
	
			/**
			 *  \brief		calculates the extreme points along a direction
			 *	\Param		Vector3D<Real> dir
			 *	\Param		const Real * vertexData
			 *	\Param		unsigned vDataCount
			 *	\Param		I32 & imin
			 *	\Param		I32 & imax
			 *	\return		void
			 */	
			static void extremePointsAlongDirection(Vector3D<Real> dir, const Real *vertexData, unsigned vDataCount, I32 &imin, I32 &imax);
	
			/**
			 *  \brief		calculates a sym schur 2d matrix used in jacobi rotations
			 *	\Param		Matrix4D<Real> & a
			 *	\Param		I32 p
			 *	\Param		I32 q
			 *	\Param		Real & c
			 *	\Param		Real & s
			 *	\return		void
			 */	
			static void symSchur2(Matrix4D<Real> &a, I32 p, I32 q, Real &c, Real &s);
	
			/**
			 *  \brief		implements jacobi rotations to find eigen-vector/values
			 *	\Param		Matrix4D<Real> & a
			 *	\Param		Matrix4D<Real> & v
			 *	\return		void
			 */	
			static void jacobi(Matrix4D<Real> &a, Matrix4D<Real> &v);
	
			/**
			 *  \brief		checks if face is visible to point
			 *	\Param		const Vector3D<Real> & faceNormal
			 *	\Param		const Vector3D<Real> & facePt
			 *	\Param		const Vector3D<Real> & pt
			 *	\return		bool
			 */	
			static bool faceVisibleToPoint(const Vector3D<Real> &faceNormal, const Vector3D<Real> &facePt, const Vector3D<Real> &pt);
	
			/**
			 *  \brief		calculates center of mass from points (NOT TESTED)
			 *	\Param		const Real * vertexData
			 *	\Param		unsigned vDataCount
			 *	\Param		Real totalMass
			 *	\return		TE::Collision::Vector3D<Real>
			 */	
			static Vector3D<Real> cOfMassFromVertex(const Real *vertexData, unsigned vDataCount, Real totalMass);
	
			/**
			 *  \brief		calculates inertia tensor from points (NOT WORKING YET)
			 *	\Param		const Real * vertexData
			 *	\Param		unsigned vDataCount
			 *	\return		Matrix4D<Real> &
			 */	
			//static Matrix4D<Real> &calcInertiaTensor(const Real *vertexData, unsigned vDataCount);
	
			/**
			 *  \brief		calculates inertia tensor of solid cuboid
			 *	\Param		Real mass
			 *	\Param		Real hight
			 *	\Param		Real width
			 *	\Param		Real depth
			 *	\return		TE::Collision::Matrix4D<Real>
			 */	
			static Matrix3D<Real> inertiaTensorOfSolidCuboid(Real mass, Real hight, Real width, Real depth);
	
			/**
			 *  \brief		calculates inertia tensor of solid sphere
			 *	\Param		Real mass
			 *	\Param		Real radius
			 *	\return		TE::Collision::Matrix4D<Real>
			 */	
			static Matrix3D<Real> inertiaTensorOfSolidSphere(Real mass, Real radius);
	
			/**
			 *  \brief		clipp convex polygon against plain
			 *	\Param		const Vector3D<Real> & normal
			 *	\Param		Real constant
			 *	\Param		I32 & numPts
			 *	\Param		Vector3D<Real> * pts
			 *	\return		void
			 */	
			static void clipConvexPolygonAgainstPlane (const Vector3D<Real>& normal, Real constant, I32& numPts, Vector3D<Real>* pts);
	
			/**
			 *  \brief		findes points from two rectangles
			 *	\Param		const Vector3D<Real> rectangle0[4]
			 *	\Param		const Vector3D<Real> rectangle1[4]
			 *	\Param		I32 & numPts
			 *	\Param		Vector3D<Real> * pts
			 *	\return		void
			 */	
			static void coplanarRectangleRectangle(const Vector3D<Real> rectangle0[4], const Vector3D<Real> rectangle1[4], I32& numPts, Vector3D<Real>* pts);
	
			/**
			 *  \brief		find points from segment and rectangle
			 *	\Param		const Vector3D<Real> segment[2]
			 *	\Param		const Vector3D<Real> rectangle[4]
			 *	\Param		I32 & numPts
			 *	\Param		Vector3D<Real> * pts
			 *	\return		void
			 */	
			static void coplanarSegmentRectangle(const Vector3D<Real> segment[2], const Vector3D<Real> rectangle[4], I32& numPts, Vector3D<Real>* pts);
	
			/**
			 *  \brief		find points from two segments
			 *	\Param		const Vector3D<Real> segment0[2]
			 *	\Param		const Vector3D<Real> segment1[2]
			 *	\Param		I32 & numPts
			 *	\Param		Vector3D<Real> * pts
			 *	\return		void
			 */	
			static void segmentSegment(const Vector3D<Real> segment0[2], const Vector3D<Real> segment1[2], I32& numPts, Vector3D<Real>* pts);
	
			/**
			 *  \brief		finds points from two colinear segments
			 *	\Param		const Vector3D<Real> segment0[2]
			 *	\Param		const Vector3D<Real> segment1[2]
			 *	\Param		I32 & numPts
			 *	\Param		Vector3D<Real> * pts
			 *	\return		void
			 */	
			static void colinearSegments(const Vector3D<Real> segment0[2], const Vector3D<Real> segment1[2], I32& numPts, Vector3D<Real>* pts);
	
			/**
			 *  \brief		finds points from segment through plane
			 *	\Param		const Vector3D<Real> segment[2]
			 *	\Param		const Vector3D<Real> & planeOrigin
			 *	\Param		const Vector3D<Real> & planeNormal
			 *	\Param		I32 & numPts
			 *	\Param		Vector3D<Real> * pts
			 *	\return		void
			 */	
			static void segmentThroughPlane(const Vector3D<Real> segment[2], const Vector3D<Real>& planeOrigin,	const Vector3D<Real>& planeNormal, I32& numPts, Vector3D<Real>* pts);

			static Matrix4D<Real> CreateTransformMatrix4D(const Vector3D<Real>& translation, const Vector3D<Real> &scale, const Quaternion<Real> &quat);

			static Matrix3D<Real> Matrix3DFromQuaternion(const Quaternion<Real> &quat);
		};



		template<typename Real>
		void TE::Math::Helpers<Real>::covarianceMatrixOfPts( TE::Math::Matrix4D<Real> &cov, const Real *vertexData, U64 vDataCount )
		{
			cov.SetIdentity();
			I32 numPts = vDataCount / 3;
			Real oon = Math::Base<Real>::REAL_ONE / numPts;
			TE::Math::Vector3D<Real> c = TE::Math::Vector3D<Real>::VECTOR3D_ZERO;
			Real e00, e11, e22, e01, e02, e12;

			//Compute center of mass
			for (unsigned i = 0; i < vDataCount;)
			{
				c.x += vertexData[i++];
				c.y += vertexData[i++];
				c.z += vertexData[i++];
			}
			c *= oon;

			//Compute covariance elements
			e00 = e11 = e22 = e01 = e02 = e12 = Math::Base<Real>::REAL_ZERO;
			TE::Math::Vector3D<Real> curr;
			for (unsigned i = 0; i < vDataCount;)
			{
				curr.x = vertexData[i++];
				curr.y = vertexData[i++];
				curr.z = vertexData[i++];

				//translate points so center of mass is at origin
				TE::Math::Vector3D<Real> p = curr - c;

				e00 += p.x * p.x;
				e11 += p.y * p.y;
				e22 += p.z * p.z;
				e01 += p.x * p.y;
				e02 += p.x * p.z;
				e12 += p.y * p.z;
			}

			//fill in covariance matrix
			cov(0,0) = e00 * oon;
			cov(1,1) = e11 * oon;
			cov(2,2) = e22 * oon;
			cov(0,1) = cov(1,0) = e01 * oon;
			cov(0,2) = cov(2,0) = e02 * oon;
			cov(1,2) = cov(2,1) = e12 * oon;
		}

		/*
		template<typename Real>
		void TE::Math::Helpers<Real>::covarianceMatrixOfTris( TE::Math::Matrix4D<Real> &cov, const Real *vertexData, unsigned vDataCount )
		{
			//WARNING! Does not seem to produce the right results, needs more debugging

			cov.Identity();
			TE::Math::Vector3D<Real> p, q, r;	//Triangle
			TE::Math::Vector3D<Real> M_k;		//Centroid of triangle
			TE::Math::Vector3D<Real> M_h;		//Centroid of convex hull
			Real A_k;					//Area of triangle

			//Calculate A_h and M_h
			Real A_h = Math::Base<Real>::REAL_ZERO;
			for (unsigned k = 0; k < vDataCount - 8; k += 9)
			{
				p = TE::Math::Vector3D<Real>(vertexData[k], vertexData[k + 1], vertexData[k + 2]);
				q = TE::Math::Vector3D<Real>(vertexData[k + 3], vertexData[k + 4], vertexData[k + 5]);
				r = TE::Math::Vector3D<Real>(vertexData[k + 6], vertexData[k + 7], vertexData[k + 8]);
				A_k = ((q - p).Cross(r - p)).Length() / 2;
				A_h += A_k;

				M_k = (p + q + r) / 3;
				M_h += A_k * M_k;
			}
			M_h = (1 / A_h) * M_h;

			//Calculate covariance matrix
			for(unsigned i = 0; i < 3; ++i)
				for(unsigned j = 0; j < 3; ++j)
				{
					Real step; //step in calculation
					for (unsigned k = 0; k < vDataCount - 8; k += 9)
					{
						p = TE::Math::Vector3D<Real>(vertexData[k], vertexData[k + 1], vertexData[k + 2]);
						q = TE::Math::Vector3D<Real>(vertexData[k + 3], vertexData[k + 4], vertexData[k + 5]);
						r = TE::Math::Vector3D<Real>(vertexData[k + 6], vertexData[k + 7], vertexData[k + 8]);
						A_k = ((q - p).Cross(r - p)).Length() / 2;
						M_k = (p + q + r) / 3;
						step = ( A_k / 12 )*( (9 * M_k[i] * M_k[j]) + ( p[i] * p[j] ) + ( q[i] * q[j] ) + ( r[i] * r[j] ) );
					}

					cov(i,j) = ((1 / A_h) * step) - (M_h[i] * M_h[j]);
				}
		}
		*/

		template<typename Real>
		void TE::Math::Helpers<Real>::extremePointsAlongDirection( TE::Math::Vector3D<Real> dir, const Real *vertexData, unsigned vDataCount, I32 &imin, I32 &imax )
		{
            Real minproj = Math::Base<Real>::MAX_REAL;
            Real maxproj = -Math::Base<Real>::MAX_REAL;

			I32 i = 0;

			for (unsigned j = 0; j < vDataCount-2;)
			{
                TE::Math::Vector3D<Real> curr;
                curr.x = vertexData[j++];
                curr.y = vertexData[j++];
                curr.z = vertexData[j++];

				Real proj = Dot(curr,dir);
				if (proj < minproj)
				{
					minproj = proj;
					imin = i;
				}

				if (proj > maxproj)
				{
					maxproj = proj;
					imax = i;
				}

				i += 3;
			}

		}

		template<typename Real>
		void TE::Math::Helpers<Real>::symSchur2( TE::Math::Matrix4D<Real> &a, I32 p, I32 q, Real &c, Real &s )
		{
			if (Math::Base<Real>::Abs(a(p,q)) > TE::Math::Base<Real>::EPSILON)
			{
				Real r = (a(q,q) - a(p,p)) / (Math::Base<Real>::REAL_TWO * a(p,q));
				Real t;
				if (r >= Math::Base<Real>::REAL_ZERO)
					t = Math::Base<Real>::REAL_ONE / (r + sqrt(Math::Base<Real>::REAL_ONE + r*r));
				else
					t = -Math::Base<Real>::REAL_ONE / (-r + sqrt(Math::Base<Real>::REAL_ONE + r*r));
				c = Math::Base<Real>::REAL_ONE / sqrt(Math::Base<Real>::REAL_ONE + t*t);
				s = t * c;
			}
			else
			{
				c = Math::Base<Real>::REAL_ONE;
				s = Math::Base<Real>::REAL_ZERO;
			}
		}


		template<typename Real>
		void TE::Math::Helpers<Real>::jacobi( TE::Math::Matrix4D<Real> &a, TE::Math::Matrix4D<Real> &v )
		{
			I32 i,j,n,p,q;
			Real prevoff, c, s;
			TE::Math::Matrix4D<Real> J;

			v.SetIdentity();

			const I32 MAX_ITERATIONS = 50;
			for (n = 0; n < MAX_ITERATIONS; ++n)
			{
				p = 0; q = 1;
				for (i = 0; i < 3; ++i)
				{
					for (j = 0; j < 3; ++j)
					{
						if(i == j) continue;
						if (Math::Base<Real>::Abs(a(i,j)) > Math::Base<Real>::Abs(a(p,q)))
						{
							p = i;
							q = j;
						}
					}
				}

				symSchur2(a, p ,q, c, s);
				J.SetIdentity();
				J(p,p) = c; J(p,q) = s;
				J(q,p) = -s; J(q,q) = c;

				v = v*J;

				a = (Transpose(J) * a) * J;

				Real off = Math::Base<Real>::REAL_ZERO;

				for (i = 0; i < 3; ++i)
				{
					for (j = 0; j < 3; ++j)
					{
						if (i == j) continue;
						off += a(i,j) * a(i,j);
					}
				}

				if (n == 0 && off < TE::Math::Base<Real>::EPSILON)
				{
					v.SetIdentity();
					return;
				}
				else if (n > 2 && off >= prevoff)
					return;

				prevoff = off;
			}
		}

		template<typename Real>
		bool TE::Math::Helpers<Real>::faceVisibleToPoint( const TE::Math::Vector3D<Real> &faceNormal, const TE::Math::Vector3D<Real> &facePt, const TE::Math::Vector3D<Real> &pt )
		{
			//Find closest pt on plane
			Real t = (Dot(faceNormal,pt) - Dot(faceNormal,facePt)) / Dot(faceNormal,faceNormal);
			TE::Math::Vector3D<Real> closestPtPlane = pt - t * faceNormal;

			//Find dot product of the normal and the vector from the face pt towards the pt in space
			Real dotProd = Dot(faceNormal,closestPtPlane - pt);

			//Sign tells if visible or not
			if (dotProd < 0)
				return true;
			else
				return false;
		}



		template<typename Real>
		TE::Math::Vector3D<Real> TE::Math::Helpers<Real>::cOfMassFromVertex( const Real *vertexData, unsigned vDataCount, Real totalMass )
		{
			TE::Math::Vector3D<Real> centerOfMass;
			for (unsigned i = 0; i < vDataCount;)
			{
				assert(i + 2 < vDataCount);

				//X_c
				centerOfMass.x = vertexData[i++] / totalMass;
				//Y_c
				centerOfMass.y = vertexData[i++] / totalMass;
				//Z_c
				centerOfMass.z = vertexData[i++] / totalMass;
			}

			return centerOfMass;
		}


		/*

		template<typename Real>
		TE::Math::Matrix4D<Real> TE::Math::Helpers<Real>::calcInertiaTensor( const Real *vertexData, unsigned vDataCount )
		{

		}*/



		template<typename Real>
		TE::Math::Matrix3D<Real> TE::Math::Helpers<Real>::inertiaTensorOfSolidCuboid( Real mass, Real hight, Real width, Real depth )
		{
			TE::Math::Matrix3D<Real> retMat;
			retMat.SetIdentity();

			retMat(0,0) = 0.0833f*mass*(hight*hight+depth*depth);
			retMat(1,1) = 0.0833f*mass*(width*width+depth*depth);
			retMat(2,2) = 0.0833f*mass*(width*width+hight*hight);

			return retMat;
		}

		template<typename Real>
		TE::Math::Matrix3D<Real> TE::Math::Helpers<Real>::inertiaTensorOfSolidSphere( Real mass, Real radius )
		{
			TE::Math::Matrix3D<Real> retMat;
			retMat.SetIdentity();

			retMat(0,0) = 0.4f*mass*(radius*radius);
			retMat(1,1) = 0.4f*mass*(radius*radius);
			retMat(2,2) = 0.4f*mass*(radius*radius);

			return retMat;
		}


		template<typename Real>
		void TE::Math::Helpers<Real>::clipConvexPolygonAgainstPlane( const TE::Math::Vector3D<Real>& normal, Real constant, I32& numPts, TE::Math::Vector3D<Real>* pts )
		{
			// The input vertices are assumed to be in counterclockwise order.  The
			// ordering is an invariant of this function.  The size of array P is
			// assumed to be large enough to store the clipped polygon vertices.

			// test on which side of line are the vertices
			I32 positive = 0, negative = 0, pIndex = -1;
			I32 currCount = numPts;

			Real test[8];
			I32 i;
			for (i = 0; i < numPts; ++i)
			{
				// An epsilon is used here because it is possible for the dot product
				// and 'constant' to be exactly equal to each other (in theory), but
				// differ slightly because of Realing point problems.  Thus, add a
				// little to the test number to push actually equal numbers over the
				// edge towards the positive.

				// TODO: This should probably be a relative tolerance.  Multiplying
				// by the constant is probably not the best way to do this.
				test[i] = Dot(normal,pts[i]) - constant + Math::Base<Real>::Abs(constant) * TE::Math::Base<Real>::EPSILON;

				if (test[i] >= Math::Base<Real>::REAL_ZERO)
				{
					++positive;
					if (pIndex < 0)
					{
						pIndex = i;
					}
				}
				else
				{
					++negative;
				}
			}

			if (numPts == 2)
			{
				// Lines are a little different, in that clipping the segment
				// cannot create a new segment, as clipping a polygon would
				if (positive > 0)
				{
					if (negative > 0) 
					{
						I32 clip;

						if (pIndex == 0)
						{
							// vertex0 positive, vertex1 is clipped
							clip = 1;
						}
						else // pIndex == 1
						{
							// vertex1 positive, vertex0 clipped
							clip = 0;
						}

						Real t = test[pIndex]/(test[pIndex] - test[clip]);
						pts[clip] = pts[pIndex] + t*(pts[clip] - pts[pIndex]);
					}
					// otherwise both positive, no clipping
				}
				else
				{
					// Assert:  The entire line is clipped, but we should not
					// get here.
					numPts = 0;
				}
			}
			else
			{
				if (positive > 0)
				{
					if (negative > 0)
					{
						// plane transversely intersects polygon
						TE::Math::Vector3D<Real> CV[8];
						I32 cCount = 0, cur, prv;
						Real t;

						if (pIndex > 0)
						{
							// first clip vertex on line
							cur = pIndex;
							prv = cur - 1;
							t = test[cur]/(test[cur] - test[prv]);
							CV[cCount++] = pts[cur] + t*(pts[prv] - pts[cur]);

							// vertices on positive side of line
							while (cur < currCount && test[cur] >= Math::Base<Real>::REAL_ZERO)
							{
								CV[cCount++] = pts[cur++];
							}

							// last clip vertex on line
							if (cur < currCount)
							{
								prv = cur - 1;
							}
							else
							{
								cur = 0;
								prv = currCount - 1;
							}
							t = test[cur]/(test[cur] - test[prv]);
							CV[cCount++] = pts[cur] + t*(pts[prv] - pts[cur]);
						}
						else  // pIndex is 0
						{
							// vertices on positive side of line
							cur = 0;
							while (cur < currCount && test[cur] >= Math::Base<Real>::REAL_ZERO)
							{
								CV[cCount++] = pts[cur++];
							}

							// last clip vertex on line
							prv = cur - 1;
							t = test[cur]/(test[cur] - test[prv]);
							CV[cCount++] = pts[cur] + t*(pts[prv] - pts[cur]);

							// skip vertices on negative side
							while (cur < currCount && test[cur] < Math::Base<Real>::REAL_ZERO)
							{
								cur++;
							}

							// first clip vertex on line
							if (cur < currCount)
							{
								prv = cur - 1;
								t = test[cur]/(test[cur] - test[prv]);
								CV[cCount++] = pts[cur] + t*(pts[prv] - pts[cur]);

								// vertices on positive side of line
								while (cur < currCount && test[cur] >= Math::Base<Real>::REAL_ZERO)
								{
									CV[cCount++] = pts[cur++];
								}
							}
							else
							{
								// cur = 0
								prv = currCount - 1;
								t = test[0]/(test[0] - test[prv]);
								CV[cCount++] = pts[0] + t*(pts[prv] - pts[0]);
							}
						}

						currCount = cCount;
						std::memcpy(pts, CV, cCount*sizeof(TE::Math::Vector3D<Real>));
					}
					// else polygon fully on positive side of plane, nothing to do

					numPts = currCount;
				}
				else
				{
					// Polygon does not intersect positive side of plane, clip all.
					// This should not ever happen if called by the findintersect
					// routines after an intersection has been determined.
					numPts = 0;
				}    
			}
		}


		template<typename Real>
		void TE::Math::Helpers<Real>::coplanarRectangleRectangle( const TE::Math::Vector3D<Real> rectangle0[4], const TE::Math::Vector3D<Real> rectangle1[4], I32& numPts, TE::Math::Vector3D<Real>* pts )
		{
			// The potential intersection is initialized to face 0, and then clipped
			// against the four sides of face 1.
			numPts = 4;
			for (I32 i = 0; i < 4; ++i)
				pts[i] = rectangle0[i];

			for (I32 i0 = 3, i1 = 0; i1 < 4; i0 = i1++)
			{
				TE::Math::Vector3D<Real> normal = rectangle1[i1] - rectangle1[i0];
				Real constant = Dot(normal,rectangle1[i0]);
				clipConvexPolygonAgainstPlane(normal, constant, numPts, pts);
			}
		}


		template<typename Real>
		void TE::Math::Helpers<Real>::coplanarSegmentRectangle( const TE::Math::Vector3D<Real> segment[2], const TE::Math::Vector3D<Real> rectangle[4], I32& numPts, TE::Math::Vector3D<Real>* pts )
		{
			// The potential intersection is initialized to the line segment and then
			// clipped against the four sides of the rect
			numPts = 2;
			for (I32 i = 0; i < 2; ++i)
				pts[i] = segment[i];

			for (I32 i0 = 3, i1 = 0; i1 < 4; i0 = i1++)
			{
				TE::Math::Vector3D<Real> normal = rectangle[i1] - rectangle[i0];
				Real constant = Dot(normal,rectangle[i0]);
				clipConvexPolygonAgainstPlane(normal, constant, numPts, pts);
			}
		}


		template<typename Real>
		void TE::Math::Helpers<Real>::segmentSegment( const TE::Math::Vector3D<Real> segment0[2], const TE::Math::Vector3D<Real> segment1[2], I32& numPts, TE::Math::Vector3D<Real>* pts )
		{
			TE::Math::Vector3D<Real> dir0 = segment0[1] - segment0[0];
			TE::Math::Vector3D<Real> dir1 = segment1[1] - segment1[0];
			TE::Math::Vector3D<Real> normal = Cross(dir0,dir1);

			// The comparison is sin(kDir0,kDir1) < epsilon.
			Real sqrLen0 = MagnitudeSqr(dir0);
			Real sqrLen1 = MagnitudeSqr(dir1);
			Real sqrLenN = MagnitudeSqr(normal);
			if (sqrLenN < TE::Math::Base<Real>::EPSILON * sqrLen0 * sqrLen1)
				TE::Math::Helpers<Real>::colinearSegments(segment0, segment1, numPts, pts);
			else
				TE::Math::Helpers<Real>::segmentThroughPlane(segment1, segment0[0], Cross(normal,segment0[1]-segment0[0]), numPts, pts);
		}

		template<typename Real>
		void TE::Math::Helpers<Real>::colinearSegments( const TE::Math::Vector3D<Real> segment0[2], const TE::Math::Vector3D<Real> segment1[2], I32& numPts, TE::Math::Vector3D<Real>* pts )
		{
			// The potential intersection is initialized to segment0 and clipped
			// against segment1.
			numPts = 2;
			for (I32 i = 0; i < 2; ++i)
				pts[i] = segment0[i];

			// point 0
			TE::Math::Vector3D<Real> V = segment1[1] - segment1[0];
			Real c = Dot(V,segment1[0]);
			TE::Math::Helpers<Real>::clipConvexPolygonAgainstPlane(V, c, numPts, pts);

			// point 1
			V = -V;
			c = Dot(V,segment1[1]);
			TE::Math::Helpers<Real>::clipConvexPolygonAgainstPlane(V, c, numPts, pts);
		}

		template<typename Real>
		void TE::Math::Helpers<Real>::segmentThroughPlane( const TE::Math::Vector3D<Real> segment[2], const TE::Math::Vector3D<Real>& planeOrigin, const TE::Math::Vector3D<Real>& planeNormal, I32& numPts, TE::Math::Vector3D<Real>* pts )
		{
			numPts = 1;

			Real u = Dot(planeNormal,planeOrigin);
			Real v0 = Dot(planeNormal,segment[0]);
			Real v1 = Dot(planeNormal,segment[1]);

			// Now that there it has been reduced to a 1-dimensional problem via
			// projection, it becomes easy to find the ratio along V that V 
			// intersects with U.
			Real ratio = (u - v0)/(v1 - v0);
			pts[0] = segment[0] + ratio*(segment[1] - segment[0]);

		}

		template<typename Real>
		TE::Math::Matrix4D<Real> TE::Math::Helpers<Real>::CreateTransformMatrix4D(const TE::Math::Vector3D<Real>& translation, const TE::Math::Vector3D<Real> &scale, const TE::Math::Quaternion<Real> &quat)
		{
			// Create rotation transformation from quaternion
			TE::Math::Matrix4D<Real> returnMat(
				1 - (2 * quat.y * quat.y) - (2 * quat.z * quat.z),
				(2 * quat.x * quat.y) - (2 * quat.z * quat.w),
				(2 * quat.x * quat.z) + (2 * quat.y * quat.w),
				0.0,

				(2 * quat.x * quat.y) + (2 * quat.z * quat.w),
				1 - (2 * quat.x * quat.x) - (2 * quat.z * quat.z),
				(2 * quat.y * quat.z) - (2 * quat.x * quat.w),
				0.0,

				(2 * quat.x * quat.z) - (2 * quat.y * quat.w),
				(2 * quat.y * quat.z) + (2 * quat.x * quat.w),
				1 - (2 * quat.x * quat.x) - (2 * quat.y * quat.y),
				0.0,

				0.0,
				0.0,
				0.0,
				1.0);

			// Create scale transformation
			TE::Math::Matrix4D<Real> scaleMat;
			scaleMat.SetScale(scale.x, scale.y, scale.z);

			// Premultiply the scale transformation by the rotation
			returnMat = returnMat * scaleMat;

			// Apply the translation
			returnMat(0,3) = translation.x;
			returnMat(1,3) = translation.y;
			returnMat(2,3) = translation.z;

			returnMat = Transpose(returnMat);

			return returnMat;
		}

		template<typename Real>
		TE::Math::Matrix3D<Real> TE::Math::Helpers<Real>::Matrix3DFromQuaternion(const TE::Math::Quaternion<Real> &quat)
		{
			// Create rotation transformation from quaternion
			return TE::Math::Matrix3D<Real>(
				1 - (2 * quat.y * quat.y) - (2 * quat.z * quat.z),
				(2 * quat.x * quat.y) - (2 * quat.z * quat.w),
				(2 * quat.x * quat.z) + (2 * quat.y * quat.w),

				(2 * quat.x * quat.y) + (2 * quat.z * quat.w),
				1 - (2 * quat.x * quat.x) - (2 * quat.z * quat.z),
				(2 * quat.y * quat.z) - (2 * quat.x * quat.w),

				(2 * quat.x * quat.z) - (2 * quat.y * quat.w),
				(2 * quat.y * quat.z) + (2 * quat.x * quat.w),
				1 - (2 * quat.x * quat.x) - (2 * quat.y * quat.y)
				);
		}

	}
}

#endif
