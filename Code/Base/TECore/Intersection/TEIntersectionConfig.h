/**
 *	\file		intersectionConfig.h
 *  \author		Terje Loe
 *  \brief		Defenitions for intersection Configuration class.
 *  \brief		Based on collision paper by David Eberly (http://www.geometrictools.com/Documentation/DynamicCollisionDetection.pdf)
 *				and from his code base located at http://www.geometrictools.com/
 */
#ifndef TEintERSECTIONCONFIG_H
#define TEintERSECTIONCONFIG_H

#include <TEDataTypes.h>

namespace TE {
    namespace Math {
        template <typename T>
        class Vector3D;
    }

    namespace Intersection {
        struct Obb;

        /**
         *	\brief		intersectionConfig class. Sets up a map of where on the obb the collision is located
         *	\author		Terje Loe
         *	\version	1.00 - 10/08/10 - Initial version
         *	\date		10/08/10
         */
        class intersectConfig {
          public:
            // ContactSide (order of the intervals of projection).
            enum {
                LEFT,
                RIGHT,
                NONE
            };

            // VertexProjectionMap (how the vertices are projected to the minimum
            // and maximum points of the interval).
            enum {
                m2,
                m11, // segments
                m3,
                m21,
                m12,
                m111, // triangles
                m44,
                m2_2,
                m1_1 // boxes
            };

            // The VertexProjectionMap value for the configuration.
            I32 m_map;

            // The order of the vertices.
            I32 m_index[8];

            // Projection interval.
            F32 m_min, m_max;

            /**
             *  \brief		sets up the configuration based on passed in axis and obb
             *	\Param		const Math::Vector3D<Real> & axis
             *	\Param		const Obb * obb
             *	\return		void
             */
            void setConfiguration(const Math::Vector3D<Real> &axis, const Obb &obb);
        };
    }
}

#endif