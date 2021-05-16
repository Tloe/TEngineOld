#include <TEMappingDX11.h>

const std::string TE::Render::APIMapping::s_layoutSemantic[] =
    {
        "POSITION",
        "COLOR",
        "TEXTURE"};

const DXGI_FORMAT TE::Render::APIMapping::s_layoutFormat[] =
    {
        DXGI_FORMAT_R32_FLOAT,          // TYPE_F321
        DXGI_FORMAT_R32G32_FLOAT,       // TYPE_F322
        DXGI_FORMAT_R32G32B32_FLOAT,    // TYPE_F323
        DXGI_FORMAT_R32G32B32A32_FLOAT, // TYPE_F324
        DXGI_FORMAT_R16_SINT,           // TYPE_SHORT1
        DXGI_FORMAT_R16G16_SINT,        // TYPE_SHORT2
        DXGI_FORMAT_UNKNOWN,            //(Not suported)
        DXGI_FORMAT_R16G16B16A16_SINT   // TYPE_SHORT4
};

const D3D11_INPUT_CLASSIFICATION TE::Render::APIMapping::s_layoutTypeOfData[] =
    {
        D3D11_INPUT_PER_VERTEX_DATA,
        D3D11_INPUT_PER_INSTANCE_DATA};

const D3D11_PRIMITIVE_TOPOLOGY TE::Render::APIMapping::s_primitiveType[] =
    {

        D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
        D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
        D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
};

const D3D11_USAGE TE::Render::APIMapping::s_bufferUsage[] =
    {
        D3D11_USAGE_IMMUTABLE,
        D3D11_USAGE_DYNAMIC};
