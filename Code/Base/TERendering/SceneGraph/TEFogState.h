#ifndef TEFOGSTATE_H
#define TEFOGSTATE_H

#include <TEColor.h>
#include <TEDataTypes.h>
#include <TEGlobalState.h>

namespace TE {
namespace SceneGraph {
    class FogState : public GlobalState {
        enum {
            DENSITYFN_LINEAR,
            DENSITYFN_EXP,
            DENSITYFN_EXPSQR,
            DENSITYFN_COUNT
        };

        enum {
            APPLYFN_PER_VERTEX,
            APPLYFN_PER_PIXEL,
            APPLYFN_COUNT
        };

        FogState()
            : m_enabled(false),
              m_start(static_cast<Real>(0.0)),
              m_end(static_cast<Real>(1.0)),
              m_density(static_cast<Real>(1.0)),
              m_color(static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(1.0)),
              m_densityFunction(DENSITYFN_LINEAR),
              m_applayFunction(APPLYFN_PER_VERTEX) {
        }
        virtual ~FogState() {
        }

        virtual I32 GetGlobalSateType() const {
            return STATE_FOG;
        }

        bool m_enabled;
        Real m_start;
        Real m_end;
        Real m_density;
        ColorRGBA m_color;
        I32 m_densityFunction;
        I32 m_applayFunction;
    };
}
}

#endif