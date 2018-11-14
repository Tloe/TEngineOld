/**
 *	\file		SpereObbCollider.h
 *  \author		Terje Loe
 *  \brief		Defenitions for SphereObbCollider class
 */
#ifndef SPHEREOBBCOLLIDER_H
#define SPHEREOBBCOLLIDER_H

#include <cstdlib>

namespace TE
{
	namespace Intersection { struct BSphere; }
	namespace Intersection { struct Obb; }
	namespace Intersection { struct ContactSet; }

	namespace Intersection
	{
		struct SphereObbCollider
		{
			static bool Collide(const BSphere& bsphere, const Obb& obb, bool coarse, bool symetric, ContactSet* contacts = NULL);
		};
	}
}

#endif