#include <TEBSphere.h>
#include <TEMathBase.h>
#include <TEMatrix4D.h>
#include "TEHelpers.h"
#include <cstdlib>
#include <time.h>
#include <vector>

TE::Intersection::BSphere& TE::Intersection::BSphere::operator=( const TE::Intersection::BSphere& rhs )
{
	if (this != &rhs)
	{
		m_center = rhs.m_center;
		m_radius = rhs.m_radius;
	}

	return *this;
}

Real TE::Intersection::Size( const BSphere &bsphere )
{
	return static_cast<Real>(1.333333) * TE::Math::Base<Real>::PI * bsphere.m_radius * bsphere.m_radius * bsphere.m_radius;
}

void TE::Intersection::BSphereFromVertexData( BSphere &bsphere, const F32 *vertexData, unsigned vDataCount )
{
	//	Calculates a iterative sphere

	std::vector<F32> vDataCopy(vertexData, vertexData+vDataCount);

	//12 iterations gives a close fitted sphere. All spheres should be calculated at load time anyways!
	const unsigned NUM_ITER = 12;
	unsigned numPts = vDataCount / 3;

	RitterEigenSphere(bsphere, &vDataCopy[0], vDataCopy.size());

	TE::Intersection::BSphere bsphere2 = bsphere;
	for (unsigned k = 0; k < NUM_ITER; ++k)
	{
		bsphere2.m_radius = bsphere2.m_radius * 0.95f;

		I32 random;
		F32 tempX, tempY, tempZ;
		TE::Math::Vector3D<Real> tempVec;
		for (unsigned i = 0; i < numPts-3; ++i)
		{
			//Swap a random point, pt[i] with pt[random] where random from interval [i+1, numPts-1]
			srand((unsigned)time(0));
			random = (rand() % ((numPts-4) - i + 1)) + (i + 1);
			random *= 3;
			tempX = vDataCopy[(random)];
			tempY = vDataCopy[random+1];
			tempZ = vDataCopy[random+2];
			vDataCopy[random] = vDataCopy[(i*3)];
			vDataCopy[random+1] = vDataCopy[(i*3)+1];
			vDataCopy[random+2] = vDataCopy[(i*3)+2];
			vDataCopy[(i*3)] = tempX;
			vDataCopy[(i*3)+1] = tempY;
			vDataCopy[(i*3)+2] = tempZ;


			tempVec.x = vDataCopy[i*3];
			tempVec.y = vDataCopy[(i*3)+1];
			tempVec.z = vDataCopy[(i*3)+2];
			BSphereFromBSphereAndPoint(bsphere2, tempVec);
		}

		if (bsphere2.m_radius < bsphere.m_radius)
			bsphere = bsphere2;
	}

}

void TE::Intersection::RitterEigenSphere( BSphere &bsphere, const F32 *vertexData, U32 vDataCount )
{
	EigenSphere(bsphere, vertexData, vDataCount);

	for (unsigned i = 0; i < vDataCount - 2; i += 3)
	{
			TE::Math::Vector3D<Real> tempVec;
			tempVec.x = vertexData[i];
			tempVec.y = vertexData[i+1];
			tempVec.z = vertexData[i+2];
			BSphereFromBSphereAndPoint(bsphere, tempVec);
	}
}

void TE::Intersection::BSphereFromBSphereAndPoint( BSphere &bsphere, Math::Vector3D<Real> &p )
{
	TE::Math::Vector3D<Real> d = p - bsphere.m_center;
	F32 dist2 = Dot(d,d);
	if(dist2 > bsphere.m_radius * bsphere.m_radius)
	{
		F32 dist = sqrt(dist2);
		F32 newRadius = (bsphere.m_radius + dist) * 0.5f;
		F32 k = (newRadius - bsphere.m_radius) / dist;
		bsphere.m_radius = newRadius;
		bsphere.m_center += d*k;
	}
}

void TE::Intersection::EigenSphere( BSphere &bsphere, const F32 *vertexData, U32 vDataCount )
{
	TE::Math::Matrix4D<Real> m,v;

	TE::Math::Helpers<Real>::covarianceMatrixOfPts(m, vertexData, vDataCount);

	TE::Math::Helpers<Real>::jacobi(m,v);

	//Find component with largest magnitude eigenvalue(largest spread)
	TE::Math::Vector3D<Real> e;
	I32 maxc = 0;
	F32 maxf, maxe = std::abs(m(0,0));
	if ((maxf = std::abs(m(1,1))) > maxe) maxc = 1, maxe = maxf;
	if ((maxf = std::abs(m(2,2))) > maxe) maxc = 2, maxe = maxf;
	e[0] = v(0,maxc);
	e[1] = v(1,maxc);
	e[2] = v(2,maxc);

	//Find most extreme points along direction 'e'
	I32 imin, imax;
	TE::Math::Helpers<Real>::extremePointsAlongDirection(e, vertexData, vDataCount, imin,imax);
	TE::Math::Vector3D<Real> minpt(vertexData[imin],vertexData[imin + 1], vertexData[imin + 2]);
	TE::Math::Vector3D<Real> maxpt(vertexData[imax],vertexData[imax + 1], vertexData[imax + 2]);

	F32 dist = sqrt(Dot((maxpt - minpt),maxpt - minpt));
	bsphere.m_radius = dist * 0.5f;
	bsphere.m_center = (minpt + maxpt) * 0.5f;
}

void TE::Intersection::Grow( BSphere &bsphere0, const BSphere& bsphere1 )
{
	TE::Math::Vector3D<Real> centreOffset = bsphere1.m_center - bsphere0.m_center;
	F32 distance = MagnitudeSqr(centreOffset);
	F32 radiusDiff = bsphere1.m_radius - bsphere0.m_radius;

	if (radiusDiff*radiusDiff >= distance)
	{
		if (bsphere0.m_radius <= bsphere1.m_radius)
		{
			bsphere0.m_center = bsphere1.m_center;
			bsphere0.m_radius = bsphere1.m_radius;
		}
	}
	else
	{
		distance = sqrt(distance);
		F32 radius = (distance + bsphere0.m_radius + bsphere1.m_radius) * 0.5f;


		if (distance > 0)
		{
			bsphere0.m_center += (centreOffset * ((radius - bsphere0.m_radius)/distance));
		}
		bsphere0.m_radius = radius;
	}
}
