/**
 *	\file		SpereObbCollider.h
 *  \author		Terje Loe
 *  \brief		Defenitions for SphereObbCollider class
 */
#ifndef SPHEREOBBCOLLIDER_H
#define SPHEREOBBCOLLIDER_H

#include <cstdlib>

namespace TE::Intersection {
  struct BSphere;
  struct Obb;
  struct ContactSet;

  struct SphereObbCollider {
    static bool Collide(const BSphere &bsphere,
                        const Obb &obb,
                        bool coarse,
                        bool symetric,
                        ContactSet *contacts = NULL);
  };
}

#endif
