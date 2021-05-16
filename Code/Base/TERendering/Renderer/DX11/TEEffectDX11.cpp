#include "Cg/cgD3D11.h"
#include "TEEffect.h"
#include "d3dcommon.h"
#include <TEEffectDX11.h>
#include <iostream>

TE::Render::APIEffect::APIEffect(APIContext &context, CGcontext &cgContext, const Effect &effect)
    : m_effect(effect),
      m_firstPass(true) {
}

TE::Render::APIEffect::~APIEffect() {
}

void TE::Render::APIEffect::Enable(APIContext &context) {
}

void TE::Render::APIEffect::Disable(APIContext &context) {
}

ID3D10Blob *TE::Render::APIEffect::GetD3DBlob() const {

    return cgD3D11GetIASignatureByPass(firstPass);
}

bool TE::Render::APIEffect::SetupNextPass() {
}
