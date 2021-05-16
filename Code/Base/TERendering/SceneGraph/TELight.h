#ifndef TELIGHT_H
#define TELIGHT_H

#include <TEColor.h>
#include <TEVector3D.h>

namespace TE {
namespace SceneGraph {
    struct Light {
        enum {
            LIGHT_AMBIENT,
            LIGHT_DIRECTIONAL,
            LIGHT_POint,
            LIGHT_SPOT,
            LIGHT_COUNT
        };

        Light(I32 lightType = LIGHT_AMBIENT)
            : m_lightType(lightType) {}

        I32 m_lightType;
        ColorRGBA m_ambient;
        ColorRGBA m_diffuse;
        ColorRGBA m_specular;
        Real m_intensity;
        Real m_constant;
        Real m_linear;
        Real m_quadric;
        bool m_attenuate;
        bool m_on;

        Math::Vector3D<Real> m_position;
        Math::Vector3D<Real> m_direction;
        Math::Vector3D<Real> m_up;
        Math::Vector3D<Real> m_right;

        // Spotlight parameters
        Real m_exponent;
        Real m_angle;
    };

    void SetLightDirection(Light &light, const Math::Vector3D<Real> &direction);
}
}

#endif
