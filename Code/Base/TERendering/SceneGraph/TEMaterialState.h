#ifndef TEMATERIALSTATE_H
#define TEMATERIALSTATE_H

#include <TEColor.h>
#include <TEGlobalState.h>
#include <TEMathBase.h>

namespace TE::SceneGraph {
  struct MaterialState : public GlobalState {
    MaterialState()
        : m_emissive(Math::Base<Real>::REAL_ZERO,
                     Math::Base<Real>::REAL_ZERO,
                     Math::Base<Real>::REAL_ZERO,
                     Math::Base<Real>::REAL_ONE),
          m_ambient(static_cast<Real>(0.2),
                    static_cast<Real>(0.2),
                    static_cast<Real>(0.2),
                    Math::Base<Real>::REAL_ONE),
          m_diffuse(static_cast<Real>(0.8),
                    static_cast<Real>(0.8),
                    static_cast<Real>(0.8),
                    Math::Base<Real>::REAL_ONE),
          m_specular(Math::Base<Real>::REAL_ZERO,
                     Math::Base<Real>::REAL_ZERO,
                     Math::Base<Real>::REAL_ZERO,
                     Math::Base<Real>::REAL_ONE),
          m_shininess(Math::Base<Real>::REAL_ONE) {
      s_default[STATE_MATERIAL].reset(new0 MaterialState);
    }

    virtual ~MaterialState() {}

    virtual I32 GetGlobalSateType() const { return STATE_MATERIAL; }

    ColorRGBA m_emissive;
    ColorRGBA m_ambient;
    ColorRGBA m_diffuse;
    ColorRGBA m_specular;
    Real m_shininess;
  };
}

#endif
