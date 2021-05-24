#include <TEAssetImporter.h>
#include <TEBSphere.h>
#include <TEObb.h>
#include <algorithm>
#include <iostream>

TE::AssetImporter::AssetImporter() {}

bool TE::AssetImporter::OpenFile(const std::string &filePath) {
    m_assimpScene = m_assimpImporter.ReadFile(
        filePath, aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                      aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

    if (!m_assimpScene)
        return false;

    SetupMeshIndexMaps(m_assimpScene->mRootNode);
    return true;
}

void TE::AssetImporter::GetMesheNames(std::vector<std::string> &meshNames) {
    meshNames.reserve(m_meshIndexMap.size());
    for (MeshNodeMap::iterator itr = m_meshIndexMap.begin(); itr != m_meshIndexMap.end(); ++itr) {
        meshNames.push_back(itr->first);
    }
}

void TE::AssetImporter::RecurseGatherMeshes(aiNode *assimpNode, std::list<MeshNode> &meshes) {
    for (unsigned i = 0; i < assimpNode->mNumMeshes; ++i) {
        MeshNode newNode;
        if (assimpNode->mName.data == "") {
            newNode.meshName = "No name";
        } else {
            newNode.meshName = assimpNode->mName.data;
        }

        newNode.index     = assimpNode->mMeshes[i];
        newNode.transform = ConvertAssimpTranform(assimpNode->mTransformation);

        meshes.push_back(newNode);
    }

    for (unsigned i = 0; i < assimpNode->mNumChildren; i++) {
        RecurseGatherMeshes(assimpNode->mChildren[i], meshes);
    }
}

void TE::AssetImporter::FillMeshIndexMap(std::list<MeshNode> &meshes) {
    std::string meshName;
    std::list<MeshNode>::iterator itr = meshes.begin();
    while (itr != meshes.end()) {
        meshName = itr->meshName;
        for (unsigned i = 0; i < meshName.size(); ++i)
            meshName[i] = tolower(meshName[i]);

        if (meshName.find("obb") != 0 && meshName.find("bsphere") != 0 &&
            meshName.find("plane") != 0) {
            m_meshIndexMap.insert(std::make_pair(itr->meshName, *itr));
            itr = meshes.erase(itr);
        } else {
            ++itr;
        }
    }
}

void TE::AssetImporter::FillMeshBoundingVolumeContainers(std::list<MeshNode> &meshes) {
    std::string meshName;
    std::list<MeshNode>::iterator itr;
    for (itr = meshes.begin(); itr != meshes.end(); ++itr) {
        meshName = itr->meshName;
        for (unsigned i = 0; i < meshName.size(); ++i)
            meshName[i] = tolower(meshName[i]);

        if (size_t pos = meshName.find_first_of("obb")) {
            MeshNodeMap::iterator findItr = m_meshIndexMap.find(meshName.substr(pos + 1));
            if (findItr != m_meshIndexMap.end()) {
                m_obbSet.insert(findItr->second.index);
            }
        } else if (size_t pos = meshName.find_first_of("bsphere")) {
            MeshNodeMap::iterator findItr = m_meshIndexMap.find(meshName.substr(pos + 1));
            if (findItr != m_meshIndexMap.end()) {
                m_bsphereSet.insert(findItr->second.index);
            }
        }
    }
}

void TE::AssetImporter::SetupMeshIndexMaps(aiNode *assimpNode) {
    m_meshIndexMap.clear();

    std::list<MeshNode> meshes;
    RecurseGatherMeshes(m_assimpScene->mRootNode, meshes);

    FillMeshIndexMap(meshes);

    FillMeshBoundingVolumeContainers(meshes);
}

TE::Intersection::BSphere TE::AssetImporter::GetBShere(const std::string &meshName) {
    MeshNodeMap::iterator meshFindItr = m_meshIndexMap.find(meshName);

    TE::Intersection::BSphere bsphere;
    if (meshFindItr != m_meshIndexMap.end()) {
        BSphereMeshIndexSet::iterator boundMeshFindItr =
            m_bsphereSet.find(meshFindItr->second.index);
        if (boundMeshFindItr != m_bsphereSet.end()) {
            BSphereFromVertexData(bsphere, &m_assimpScene->mMeshes[*boundMeshFindItr]->mVertices->x,
                                  m_assimpScene->mMeshes[*boundMeshFindItr]->mNumVertices);
        } else {
            BSphereFromVertexData(bsphere,
                                  &m_assimpScene->mMeshes[meshFindItr->second.index]->mVertices->x,
                                  m_assimpScene->mMeshes[meshFindItr->second.index]->mNumVertices);
        }
    }

    return bsphere;
}

TE::Intersection::Obb TE::AssetImporter::GetObb(const std::string &meshName) {
    MeshNodeMap::iterator meshFindItr = m_meshIndexMap.find(meshName);

    TE::Intersection::Obb obb;
    if (meshFindItr != m_meshIndexMap.end()) {
        ObbMeshIndexSet::iterator boundMeshFindItr = m_obbSet.find(meshFindItr->second.index);
        if (boundMeshFindItr != m_obbSet.end()) {
            ObbFromVertexData(obb, &m_assimpScene->mMeshes[*boundMeshFindItr]->mVertices->x,
                              m_assimpScene->mMeshes[*boundMeshFindItr]->mNumVertices);
        } else {
            ObbFromVertexData(obb, &m_assimpScene->mMeshes[meshFindItr->second.index]->mVertices->x,
                              m_assimpScene->mMeshes[meshFindItr->second.index]->mNumVertices);
        }
    }

    return obb;
}

void TE::AssetImporter::GetVertexBuffer(const std::string &meshName,
                                        I32 vertexBufferFlags,
                                        std::vector<U8> &data,
                                        Render::VertexBufferInfo &vertexBufferInfo) {
    std::vector<F32> buffer;
    assert(m_meshIndexMap.find(meshName) != m_meshIndexMap.end() && "meshName not found!");
    aiMesh *pMesh = m_assimpScene->mMeshes[m_meshIndexMap[meshName].index];

    for (unsigned i = 0; i < pMesh->mNumVertices; ++i) {
        if (vertexBufferFlags & VERTEXBUFFER_POSITION) {
            Math::Vector3D<F32> vertice(pMesh->mVertices[i].x, pMesh->mVertices[i].y,
                                        pMesh->mVertices[i].z);
            vertice = vertice * m_meshIndexMap[meshName].transform;
            buffer.push_back(vertice.x);
            buffer.push_back(vertice.y);
            buffer.push_back(vertice.z);
        }
        if (vertexBufferFlags & VERTEXBUFFER_NORMALS) {
            buffer.push_back(pMesh->mNormals[i].x);
            buffer.push_back(pMesh->mNormals[i].y);
            buffer.push_back(pMesh->mNormals[i].z);
        }
        if (vertexBufferFlags & VERTEXBUFFER_TEXTURECOORDS) {
            for (U32 j = 0; j < pMesh->GetNumUVChannels(); ++j) {
                buffer.push_back(pMesh->mTextureCoords[j][i].x);
                buffer.push_back(pMesh->mTextureCoords[j][i].y);
            }
        }
    }

    data.resize(buffer.size() * sizeof(F32));
    memcpy(&data[0], &buffer[0], buffer.size() * sizeof(F32));

    vertexBufferInfo.dataElementCount = data.size() / sizeof(F32);
    vertexBufferInfo.dataSize         = data.size();
    vertexBufferInfo.dataElementSize  = sizeof(F32);

    switch (pMesh->mPrimitiveTypes) {
    case aiPrimitiveType_POINT:
        vertexBufferInfo.primitiveType = TE::Render::PrimitiveType::POINTS;
        break;
    case aiPrimitiveType_LINE:
        vertexBufferInfo.primitiveType = TE::Render::PrimitiveType::LINES;
        break;
    case aiPrimitiveType_TRIANGLE:
        vertexBufferInfo.primitiveType = TE::Render::PrimitiveType::TRIANGLES;
        break;
    default:
        assert(false && "Should not get here!");
        break;
    }

    GetLayoutElements(meshName, vertexBufferFlags, vertexBufferInfo.layoutElements);
}

void TE::AssetImporter::GetIndexBuffer(const std::string &meshName,
                                       std::vector<U8> &data,
                                       Render::IndexBufferInfo &indexBufferInfo) {
    int si = sizeof(I16);
    std::vector<I16> buffer;
    assert(m_meshIndexMap.find(meshName) != m_meshIndexMap.end() && "meshName not found!");
    aiMesh *pMesh = m_assimpScene->mMeshes[m_meshIndexMap[meshName].index];
    for (unsigned i = 0; i < pMesh->mNumFaces; ++i) {
        for (unsigned j = 0; j < pMesh->mFaces[i].mNumIndices; ++j) {
            buffer.push_back(static_cast<I16>(pMesh->mFaces[i].mIndices[j]));
        }
    }

    data.resize(buffer.size() * sizeof(I16));
    memcpy(&data[0], &buffer[0], buffer.size() * sizeof(I16));

    indexBufferInfo.dataElementCount = data.size() / sizeof(I16);
    indexBufferInfo.dataSize         = data.size();
    indexBufferInfo.dataElementSize  = sizeof(I16);
}

TE::Render::Mesh TE::AssetImporter::GetMesh(const std::string &meshName,
                                            I32 vertexBufferFlags,
                                            Enum vertexBufferUsage,
                                            Enum indexBufferUsage) {
    std::vector<U8> vertexBuffer;
    TE::Render::VertexBufferInfo vertexBufferInfo;
    GetVertexBuffer(meshName, vertexBufferFlags, vertexBuffer, vertexBufferInfo);
    vertexBufferInfo.usage = vertexBufferUsage;

    std::vector<U8> indexBuffer;
    TE::Render::IndexBufferInfo indexBufferInfo;
    GetIndexBuffer(meshName, indexBuffer, indexBufferInfo);
    indexBufferInfo.usage = indexBufferUsage;

    return TE::Render::Mesh("/" + meshName, vertexBufferInfo, vertexBuffer, indexBufferInfo,
                            indexBuffer);
}

void TE::AssetImporter::GetLayoutElements(
    const std::string &meshName,
    I32 vertexBufferFlags,
    std::vector<Render::VertexBufferInfo::LayoutElement> &layoutElements) {
    U32 byteOffset = 0;
    if (vertexBufferFlags & VERTEXBUFFER_POSITION) {
        TE::Render::VertexBufferInfo::LayoutElement layoutElement;

        layoutElement.layoutSemantic = TE::Render::Semantics::POSITION;
        layoutElement.byteOffset     = byteOffset;
        layoutElement.valueCount     = 3;
        layoutElement.valueType      = TE::Render::LayoutElementValueType::F32;

        layoutElements.push_back(layoutElement);

        byteOffset += sizeof(F32) * layoutElement.valueCount;
    }

    if (vertexBufferFlags & VERTEXBUFFER_NORMALS) {
        TE::Render::VertexBufferInfo::LayoutElement layoutElement;

        layoutElement.layoutSemantic = TE::Render::Semantics::NORMAL;
        layoutElement.byteOffset     = byteOffset;
        layoutElement.valueCount     = 3;
        layoutElement.valueType      = TE::Render::LayoutElementValueType::F32;

        layoutElements.push_back(layoutElement);

        byteOffset += sizeof(F32) * layoutElement.valueCount;
    }

    if (vertexBufferFlags & VERTEXBUFFER_TEXTURECOORDS) {
        TE::Render::VertexBufferInfo::LayoutElement layoutElement;

        layoutElement.layoutSemantic = TE::Render::Semantics::TEXTURE0;
        layoutElement.byteOffset     = byteOffset;
        layoutElement.valueType      = TE::Render::LayoutElementValueType::F32;

        aiMesh *pMesh                = m_assimpScene->mMeshes[m_meshIndexMap[meshName].index];
        layoutElement.valueCount     = 2 * pMesh->GetNumUVChannels();

        layoutElements.push_back(layoutElement);

        byteOffset += sizeof(F32) * layoutElement.valueCount;
    }
}

TE::Math::Matrix4D<Real> TE::ConvertAssimpTranform(aiMatrix4x4 &transform) {
    return Math::Matrix4D<Real>(transform.a1, transform.a2, transform.a3, transform.a4,
                                transform.b1, transform.b2, transform.b3, transform.b4,
                                transform.c1, transform.c2, transform.c3, transform.c4,
                                transform.d1, transform.d2, transform.d3, transform.d4);
}
