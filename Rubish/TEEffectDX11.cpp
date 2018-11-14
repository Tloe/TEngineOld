#include <TEEffectDX11.h>
#include "TEEffect.h"
#include <iostream>
#include "d3dcommon.h"
#include "Cg/cgD3D11.h"

TE::Render::APIEffect::APIEffect( APIContext& context, CGcontext& cgContext, const Effect& effect )
	:
	m_effect(effect),
	m_firstPass(true)
{

}

TE::Render::APIEffect::~APIEffect()
{
	cgDestroyEffect(m_cgEffect);
}

void TE::Render::APIEffect::Enable( APIContext& context )
{

}

void TE::Render::APIEffect::Disable( APIContext& context )
{

}

ID3D10Blob* TE::Render::APIEffect::GetD3DBlob() const
{
	CGpass firstPass = cgGetFirstPass(m_cgTechnique);
	return cgD3D11GetIASignatureByPass(firstPass);
}

bool TE::Render::APIEffect::SetupNextPass()
{
	if (m_cgPass)
	{
		cgResetPassState(m_cgPass);
		m_cgPass = cgGetNextPass(m_cgPass);
	}
	else
	{
		m_cgPass = cgGetFirstPass(m_cgTechnique);
	}

	if (m_cgPass)
	{
		cgSetPassState(m_cgPass);
		return true;
	}
	else
	{
		return false;
	}
}

