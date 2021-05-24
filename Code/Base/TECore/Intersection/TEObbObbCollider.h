/**
 *	\file		ObbObbCollider.h
 *  \author		Terje Loe
 *  \brief		Based on collision paper by David Eberly
 *(http://www.geometrictools.com/Documentation/DynamicCollisionDetection.pdf) and from his code base
 *located at http://www.geometrictools.com/
 */

#ifndef TEOBBOBBCOLLIDER_H
#define TEOBBOBBCOLLIDER_H

/**
 *	\file		Obb.h
 *  \author		Terje Loe
 *  \brief		Defenitions for Oriented Bounding Box class
 */
#include <TEDataTypes.h>
#include <cstdlib>

namespace TE::Math {
  template <typename T> class Vector3D;
}

namespace TE::Intersection {
  struct Obb;
  struct ContactSet;
  class intersectConfig;
  struct ObbObbCollider {
  public:
    static bool Collide(const Obb &obb0,
                        const Obb &obb1,
                        Real dt,
                        bool coarse,
                        bool symetric,
                        const Math::Vector3D<Real> *pos0    = NULL,
                        const Math::Vector3D<Real> *pos1    = NULL,
                        const Math::Vector3D<Real> *vel0    = NULL,
                        const Math::Vector3D<Real> *vel1    = NULL,
                        const Math::Vector3D<Real> *angvel0 = NULL,
                        const Math::Vector3D<Real> *angvel1 = NULL,
                        ContactSet *contacts                = NULL);

  private:
    static Real s_minAxisPenetrationDepth;
    static Real s_contactTime;
    static Math::Vector3D<Real> s_contactNormal;

    /**
     *  \brief		Static check, used for fast collision check
     *	\return		bool
     */
    static bool StaticCheck(const Obb &obb0, const Obb &obb1);

    /**
     *  \brief		Dynamic check, first time of contact(if any) is computed. No contact
     *info \Param		F32 tmax \Param		Math::Vector3D<Real> velocity0 \Param
     *Math::Vector3D<Real> velocity1 \Param		Obb obbs[] \return		bool
     */
    static bool DynamicCheck(const Obb &obb0,
                             const Obb &obb1,
                             F32 tmax,
                             Math::Vector3D<Real> velocity0,
                             Math::Vector3D<Real> velocity1);

    /**
     *  \brief		Derives the contact info from first time of contact
     *	\Param		F32 tmax
     *	\Param		const Math::Vector3D<Real> & velocity0
     *	\Param		const Math::Vector3D<Real> & velocity1
     *	\return		bool
     */
    static bool DeriveContacts(const Obb &obb0,
                               const Obb &obb1,
                               F32 tmax,
                               const Math::Vector3D<Real> &velocity0,
                               const Math::Vector3D<Real> &velocity1,
                               ContactSet *contacts = NULL);

    /**
     *  \brief		Checks if obbs are separate along one axis in the time interval
     *	\Param		F32 min0
     *	\Param		F32 max0
     *	\Param		F32 min1
     *	\Param		F32 max1
     *	\Param		F32 speed
     *	\Param		F32 tmax
     *	\Param		F32 & tlast
     *	\return		bool
     */
    static bool
    IsSeparated(F32 min0, F32 max0, F32 min1, F32 max1, F32 speed, F32 tmax, F32 &tlast);

    /**
     *  \brief		Find the intersection along one axis
     *	\Param		const Math::Vector3D<Real> & axis
     *	\Param		const Obb obbs[]
     *	\Param		const Math::Vector3D<Real> & velocity
     *	\Param		F32 tmax
     *	\Param		F32 & tfirst
     *	\Param		F32 & tlast
     *	\Param		I32 & side
     *	\Param		intersectConfig & box0CfgFinal
     *	\Param		intersectConfig & box1CfgFinal
     *	\return		bool
     */
    static bool FindintersectionOnAxis(const Obb &obb0,
                                       const Obb &obb1,
                                       const Math::Vector3D<Real> &axis,
                                       const Math::Vector3D<Real> &velocity,
                                       F32 tmax,
                                       F32 &tfirst,
                                       F32 &tlast,
                                       I32 &side,
                                       intersectConfig &box0CfgFinal,
                                       intersectConfig &box1CfgFinal);

    /**
     *  \brief		finds the contact set based on 2 intersection configurations from 2
     *Obb's \Param		const Obb obbs[] \Param		const Math::Vector3D<Real> &
     *velocity0 \Param		const Math::Vector3D<Real> & velocity1 \Param		I32
     *side \Param		const intersectConfig & box0Cfg \Param		const
     *intersectConfig & box1Cfg \Param		F32 tfirst \return		void
     */
    static void FindContactSet(const Obb &obb0,
                               const Obb &obb1,
                               const Math::Vector3D<Real> &velocity0,
                               const Math::Vector3D<Real> &velocity1,
                               I32 side,
                               const intersectConfig &box0Cfg,
                               const intersectConfig &box1Cfg,
                               F32 tfirst,
                               ContactSet *contacts = NULL);
  };
}

#endif
