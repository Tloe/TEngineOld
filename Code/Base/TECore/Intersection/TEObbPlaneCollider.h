/**
 *	\file		ObbPlaneCollider.h
 *  \author		Terje Loe
 *  \brief		Defenitions for ObbPlaneCollider class
 */
#ifndef TEOBBPLANECOLLIDER_H
#define TEOBBPLANECOLLIDER_H

#include <cstdlib>

namespace TE {
    namespace Intersection {
        struct Obb;
    }
    namespace Intersection {
        struct Plane;
    }
    namespace Intersection {
        struct ContactSet;
    }

    namespace Intersection {
        struct ObbPlaneCollider {
            static bool Collide(const Obb &obb, const Plane &plane, bool coarse, bool symetric, ContactSet *contacts = NULL);
        };
    }
}

#endif