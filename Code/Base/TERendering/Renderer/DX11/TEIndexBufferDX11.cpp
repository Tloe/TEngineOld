#include <TEContextWinDX11.h>
#include <TEIndexBufferDX11.h>
#include <TEMappingDX11.h>
#include <TEMesh.h>
#include <d3d11.h>
#include <iostream>

TE::Render::APIIndexBuffer::APIIndexBuffer(Context::APIContext &apiContext, const Mesh &mesh)
    : m_usageCount(1),
      m_mesh(mesh),
      m_apiContext(apiContext) {
    const IndexBufferInfo &bufferInfo = mesh.GetIndexBufferInfo();

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = APIMapping::s_bufferUsage[bufferInfo.usage]; // write access access by CPU and GPU
    bd.ByteWidth = bufferInfo.dataSize;                     // size of data
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;                 // use as a index buffer
    if (bufferInfo.usage == Usage::STATIC)
        bd.CPUAccessFlags = 0;
    else
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA subData;
    subData.pSysMem = reinterpret_cast<const void *>(mesh.GetIndexBufferDataPtr());
    apiContext.GetDevice()->CreateBuffer(&bd, &subData, &m_D3DindexBuffer);

    /*D3D11_MAPPED_SUBRESOURCE ms;
    context.devcontext->Map(m_D3DindexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);   // map
    the buffer memcpy(ms.pData, indexBuffer.GetDataPtr(), m_indexBuffer.GetDataSize());           //
    copy the data context.devcontext->Unmap(m_D3DindexBuffer, NULL); // unmap the buffer*/
}

TE::Render::APIIndexBuffer::~APIIndexBuffer() {}

void TE::Render::APIIndexBuffer::Enable() {
    m_apiContext.GetDeviceContext()->IASetIndexBuffer(m_D3DindexBuffer, DXGI_FORMAT_R16_UINT, 0);
}

void TE::Render::APIIndexBuffer::Disable() {}

U32 TE::Render::APIIndexBuffer::IncreaseUsageCount() { return ++m_usageCount; }

U32 TE::Render::APIIndexBuffer::DecreaseUsageCount() { return ++m_usageCount; }
