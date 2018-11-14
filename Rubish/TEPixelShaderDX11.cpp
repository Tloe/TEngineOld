#include <TEPixelShaderDX11.h>
#include <string>
#include <d3dx11async.h>
#include <TEContextWinDX11.h>
#include "Cg/cgD3D11.h"
#include "TEPixelShader.h"

TE::Render::APIPixelShader::APIPixelShader( APIContext& context, CGcontext& cgContext, const PixelShader& pixelShader )
{
	m_cgProgram = cgCreateProgram(cgContext, CG_SOURCE, pixelShader.GetDataPtr(), CG_PROFILE_PS_4_0, "mainPS", NULL);

	cgD3D11LoadProgram(m_cgProgram, 0);


	/*ID3D10Blob *PS;
	//D3DX11CompileFromMemory(reinterpret_cast<const char*>(&pixelShader.GetDataRef()[0]), pixelShader.GetDataSize(), "", 0, 0, "PShader", "ps_5_0", 0, 0, 0, &PS, 0, 0);
	std::string fname("Shader0.hlsl");
	
	D3DX11CompileFromFile(fname.c_str(), 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

	context.device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPS);
	context.devcontext->PSSetShader(m_pPS, 0, 0);*/
}

TE::Render::APIPixelShader::~APIPixelShader()
{
	cgDestroyProgram(m_cgProgram);
	//m_pPS->Release();
}

void TE::Render::APIPixelShader::Enable( APIContext& context )
{
	cgD3D11BindProgram(m_cgProgram);
	//context.devcontext->PSSetShader(m_pPS, NULL, 0);
}

void TE::Render::APIPixelShader::Disable(APIContext& context)
{

}
