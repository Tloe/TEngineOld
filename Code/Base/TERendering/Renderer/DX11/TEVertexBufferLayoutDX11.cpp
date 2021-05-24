#include "Cg/cgD3D11.h"
#include "TEEffect.h"
#include "TEMesh.h"
#include "d3dcommon.h"
#include <TEContextWinDX11.h>
#include <TEVertexBufferLayoutDX11.h>

TE::Render::APIVertexBufferLayout::APIVertexBufferLayout(Context::APIContext &apiContext,
                                                         const Render::Mesh &mesh,
                                                         const Render::Effect &effect)
    : m_usageCount(1),
      m_apiContext(apiContext) {
    /*unsigned layoutElementCount = apiLayout.GetBufferLayoutRef().ElementCount();
    std::vector<D3D11_INPUT_ELEMENT_DESC> ied(layoutElementCount);
    for (I32 i = 0; i < layoutElementCount; ++i)
    {
            const LayoutElement& layoutElement = apiLayout.GetBufferLayoutRef().GetElementRef(i);
            ied[i].SemanticName =
    "POSITION";//APIMapping::s_layoutSemantic[layoutElement.layoutSemantic].c_str();
            ied[i].SemanticIndex = layoutElement.semanticIndex;
            ied[i].Format = static_cast<DXGI_FORMAT>(layoutElement.format);
            ied[i].InputSlot = layoutElement.inputSlot;
            ied[i].AlignedByteOffset = layoutElement.byteOffset;
            ied[i].InputSlotClass =
    static_cast<D3D11_INPUT_CLASSIFICATION>(layoutElement.typeOfData); ied[i].InstanceDataStepRate =
    layoutElement.dataStepRate;
    }*/

    D3D11_INPUT_ELEMENT_DESC ied[] = {
        {"ATTR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"ATTR", 2, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"ATTR", 8, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}};
    unsigned numElements = ARRAYSIZE(ied);

    CGpass cgPass        = effect.GetFirstPass();
    ID3D10Blob *blob     = cgD3D11GetIASignatureByPass(cgPass);
    apiContext.GetDevice()->CreateInputLayout(ied, numElements, blob->GetBufferPointer(),
                                              blob->GetBufferSize(), &m_D3D11layout);

    apiContext.GetDeviceContext()->IASetInputLayout(m_D3D11layout);
}

TE::Render::APIVertexBufferLayout::~APIVertexBufferLayout() {}

void TE::Render::APIVertexBufferLayout::Enable() {
    m_apiContext.GetDeviceContext()->IASetInputLayout(m_D3D11layout);
}

void TE::Render::APIVertexBufferLayout::Disable() {}

U32 TE::Render::APIVertexBufferLayout::IncreaseUsageCount() { return ++m_usageCount; }

U32 TE::Render::APIVertexBufferLayout::DecreaseUsageCount() { return --m_usageCount; }
