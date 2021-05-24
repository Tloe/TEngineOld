#include <TEContextWinDX11.h>
#include <TEMappingDX11.h>
#include <TEMesh.h>
#include <TEVertexBufferDX11.h>
#include <d3d11.h>
#include <iostream>
#include <winerror.h>

TE::Render::APIVertexBuffer::APIVertexBuffer(TE::Context::APIContext &apiContext, const Mesh &mesh)
    : m_usageCount(1),
      m_mesh(mesh),
      m_apiContext(apiContext) {
    const VertexBufferInfo &bufferInfo = mesh.GetVertexBufferInfo();

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage     = APIMapping::s_bufferUsage[bufferInfo.usage];
    bd.ByteWidth = bufferInfo.dataSize;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    if (bufferInfo.usage == Usage::STATIC)
        bd.CPUAccessFlags = 0;
    else
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA subData;
    subData.pSysMem = reinterpret_cast<const void *>(mesh.GetVertexBufferDataPtr());
    apiContext.GetDevice()->CreateBuffer(&bd, &subData, &m_D3DvertexBuffer);
}

TE::Render::APIVertexBuffer::~APIVertexBuffer() {}

void TE::Render::APIVertexBuffer::Enable() {
    const VertexBufferInfo &bufferInfo = m_mesh.GetVertexBufferInfo();

    U32 stride                         = bufferInfo.dataElementSize * 8;
    U32 offset                         = 0;
    m_apiContext.GetDeviceContext()->IASetVertexBuffers(0, 1, &m_D3DvertexBuffer, &stride, &offset);
    D3D11_PRIMITIVE_TOPOLOGY primitiveTopology =
        APIMapping::s_primitiveType[bufferInfo.primitiveType];
    m_apiContext.GetDeviceContext()->IASetPrimitiveTopology(primitiveTopology);
}

void TE::Render::APIVertexBuffer::Disable() {}

U32 TE::Render::APIVertexBuffer::IncreaseUsageCount() { return ++m_usageCount; }

U32 TE::Render::APIVertexBuffer::DecreaseUsageCount() { return --m_usageCount; }
