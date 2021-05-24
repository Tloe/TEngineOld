/**
 *	\file		SpherePlaneCollider.h
 *  \author		Terje Loe
 *  \brief		Defenitions for SpherePlaneCollider class
 */
#ifndef TESPHEREPLANECOLLIDER_H
#define TESPHEREPLANECOLLIDER_H

#include <cstdlib>

namespace TE::Intersection {
  struct BSphere;
  struct Plane;
  struct ContactSet;

  struct SpherePlaneCollider {
    static bool Collide(const BSphere &bsphere,
                        const Plane &plane,
                        bool coarse,
                        bool symetric,
                        ContactSet *contacts = NULL);
  };
}

#endif
