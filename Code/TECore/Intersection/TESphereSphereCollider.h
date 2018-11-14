/**
 *	\file		SphereSphereCollider.h
 *  \author		Terje Loe
 *  \brief		Defenitions for SphereSphereCollider class
 */
#ifndef TESPHERESPHERECOLLIDER_H
#define TESPHERESPHERECOLLIDER_H

#include <cstdlib>

namespace TE
{
	namespace Intersection { struct BSphere; }
	namespace Intersection { struct ContactSet; }


	namespace Intersection
	{
		/**
		 *	\brief		SphereSphereCollider class. Checks for collision between two bounding volumes.
		 *	\author		Terje Loe
		 *	\version	1.00 - 10/08/10 - Initial version
		 *	\date		10/08/10
		 */
		struct SphereSphereCollider
		{
			static bool Collide(const BSphere& bsphere0, const BSphere& bsphere1, bool coarse, ContactSet* contacts = NULL);
		};

	}
}

#endif