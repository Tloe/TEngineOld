/**
 *	\file		ObbPlaneCollider.h
 *  \author		Terje Loe
 *  \brief		Defenitions for ObbPlaneCollider class
 */
#ifndef TEOBBPLANECOLLIDER_H
#define TEOBBPLANECOLLIDER_H

#include <cstdlib>

namespace TE::Intersection {
  struct Obb;
  struct Plane;
  struct ContactSet;

  struct ObbPlaneCollider {
    static bool Collide(const Obb &obb,
                        const Plane &plane,
                        bool coarse,
                        bool symetric,
                        ContactSet *contacts = NULL);
  };
}

#endif
