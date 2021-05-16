/**
 *	\file		Collider.h
 *  \author		Terje Loe
 *  \brief		Defenitions for base Collider class
 */
#ifndef TECOLLIDER_H
#define TECOLLIDER_H

#include <TEContactSet.h>
#include <TEDataTypes.h>
#include <TEMathBase.h>
#include <vector>

namespace TE {
    namespace Math {
        template <typename T>
        class Vector3D;
    }

    namespace Intersection {
        /**
         *	\brief		base Collider class. Checks for collision between two bounding volumes.
         *	\author		Terje Loe
         *	\version	1.00 - 10/08/10 - Initial version
         *	\date		10/08/10
         */
        class Collider {
          public:
            /**
             *  \brief		constructs the base collider
             *	\Param		std::vector<Contact> * contacts
             *	\Param		bool coarse
             *	\Param		Real dt
             *	\Param		bool symetric
             *	\return
             */
            Collider(bool coarse, bool symetric, Real dt = Math::Base<Real>::REAL_ZERO,
                     const Math::Vector3D<Real> *pos0 = NULL, const Math::Vector3D<Real> *pos1 = NULL,
                     const Math::Vector3D<Real> *vel0 = NULL, const Math::Vector3D<Real> *vel1 = NULL,
                     const Math::Vector3D<Real> *angvel0 = NULL, const Math::Vector3D<Real> *angvel1 = NULL)
                : m_symetric(symetric),
                  m_coarse(coarse),
                  m_dt(dt) {
                m_pos[0]    = pos0;
                m_pos[1]    = pos1;
                m_vel[0]    = vel0;
                m_vel[1]    = vel1;
                m_angvel[0] = angvel0;
                m_angvel[1] = angvel1;
            }

            Collider(const Collider &src) {
                m_pos[0]      = src.m_pos[0];
                m_pos[1]      = src.m_pos[1];
                m_vel[0]      = src.m_vel[0];
                m_vel[1]      = src.m_vel[1];
                m_angvel[0]   = src.m_angvel[0];
                m_angvel[1]   = src.m_angvel[1];

                m_contacts    = src.m_contacts;
                m_symetric    = src.m_symetric;
                m_coarse      = src.m_coarse;
                m_dt          = src.m_dt;
                m_contactTime = src.m_contactTime;
            }

            /**
             *  \brief		virtual. executes the collision test returns true if there is a collision
             *	\return		bool
             */
            virtual bool execute() {
                assert(false);
                return false;
            }

            ContactSet GetContactSet() {
                return m_contacts;
            }

          protected:
            ContactSet m_contacts;
            bool m_symetric;
            bool m_coarse;
            Real m_dt;
            Real m_contactTime;
            const Math::Vector3D<Real> *m_pos[2];
            const Math::Vector3D<Real> *m_vel[2];
            const Math::Vector3D<Real> *m_angvel[2];
        };
    }
}

#endif
