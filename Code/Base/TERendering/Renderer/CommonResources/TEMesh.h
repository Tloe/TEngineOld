#ifndef TEMESH_H
#define TEMESH_H

#include "TEJson.h"
#include "TEMeshStructs.h"
#include "TEResource.h"

namespace TE::Render {
    class Mesh : public Resources::Resource //, public IO::JsonSerializer
    {
      public:
        Mesh(const std::string &filePath);
        Mesh(const std::string &filePath,
             const VertexBufferInfo &vertexBufferInfo,
             const std::vector<U8> &vertexBufferData,
             const IndexBufferInfo &indexBufferInfo,
             const std::vector<U8> &indexBufferData);

        const VertexBufferInfo &GetVertexBufferInfo() const;
        const IndexBufferInfo &GetIndexBufferInfo() const;
        const U8 *GetVertexBufferDataPtr() const;
        const U8 *GetIndexBufferDataPtr() const;

        // virtual void JSONDeserialize( const Json::Value& jsonValue );
        // virtual void JSONSerialize(Json::Value& jsonValue);

        virtual void Load(IO::FileIO &fileIO);
        virtual void Save(IO::FileIO &fileIO);

      private:
        VertexBufferInfo m_vertexBufferInfo;
        IndexBufferInfo m_indexBufferInfo;
        U32 m_vertexBufferOffset;
        U32 m_indexBufferOffset;
        U32 m_jsonOffset;
    };
}

#endif
