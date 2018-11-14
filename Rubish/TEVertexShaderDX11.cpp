#include <TEVertexShaderDX11.h>
#include <TEContextWinDX11.h>
#include <TERenderer.h>
#include <TEVertexShader.h>
#include <d3dx11async.h>
#include <TEBufferLayoutDX11.h>
#include <TEMappingDX11.h>
#include <Cg/cg.h>
#include <Cg/cgD3D11.h>
#include "d3dcommon.h"
#include <iostream>

TE::Render::APIVertexShader::APIVertexShader( Render::APIContext& context, CGcontext& cgContext, const VertexShader& vertexShader )
{
	m_cgProgram = cgCreateProgram(cgContext, CG_SOURCE, vertexShader.GetDataPtr(), CG_PROFILE_VS_4_0, "mainVS", NULL);
	/*CGerror error = cgGetError();
	std::string errorstr = cgGetErrorString(error);
	std::string listeningstr = cgGetLastListing(cgContext);
	std::cout << listeningstr << std::endl;*/
	cgD3D11LoadProgram(m_cgProgram, 0);

	//ID3D10Blob *VS;
	//D3DX11CompileFromMemory(reinterpret_cast<const char*>(&vertexShader.GetDataRef()[0]), vertexShader.GetDataSize(), "", 0, 0, "VShader", "vs_5_0", 0, 0, 0, &VS, 0, 0);
	//std::string fname("Shader0.hlsl");
	//D3DX11CompileFromFile(fname.c_str(), 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);

	//context.device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVS);

	//context.devcontext->VSSetShader(m_pVS, 0, 0);
}

TE::Render::APIVertexShader::~APIVertexShader()
{
	cgDestroyProgram(m_cgProgram);
	//m_pVS->Release();
}

void TE::Render::APIVertexShader::Enable( TE::Render::APIContext& context )
{
	cgD3D11BindProgram(m_cgProgram);
	//context.devcontext->VSSetShader(m_pVS, NULL, 0);
}

void TE::Render::APIVertexShader::Disable(APIContext& context)
{

}

ID3D10Blob* TE::Render::APIVertexShader::GetBlob() const
{
	return cgD3D11GetCompiledProgram(m_cgProgram);
}
