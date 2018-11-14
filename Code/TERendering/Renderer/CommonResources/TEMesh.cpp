#include "TEMesh.h"
#include <assert.h>
#include "TEFileIO.h"
#include <iostream>
//#include <json/value.h>
//#include "json/writer.h"
//#include "json/reader.h"

TE::Render::Mesh::Mesh( const std::string& filePath )
	:
	Resource(filePath)
{

}

TE::Render::Mesh::Mesh( const std::string& filePath, const VertexBufferInfo& vertexBufferInfo, const std::vector<U8>& vertexBufferData, const IndexBufferInfo& indexBufferInfo, const std::vector<U8>& indexBufferData )
	:
	Resource(filePath),
	m_vertexBufferInfo(vertexBufferInfo),
	m_indexBufferInfo(indexBufferInfo)
{
	m_vertexBufferOffset = sizeof(U32);
	m_indexBufferOffset = m_vertexBufferOffset + vertexBufferData.size();
	m_jsonOffset = m_indexBufferOffset + indexBufferData.size();

	std::vector<U8> data;
	IO::WriteU32ToU8Vector(m_jsonOffset, data);

	data.insert(data.end(), vertexBufferData.begin(), vertexBufferData.end());
	data.insert(data.end(), indexBufferData.begin(), indexBufferData.end());

	/*Json::Value jsonMesh;
	JSONSerialize(jsonMesh);
	Json::FastWriter jsonWriter;
	std::string jsonStr = jsonWriter.write(jsonMesh);
	data.insert(data.end(), jsonStr.begin(), jsonStr.end());

	SetData(data.begin(), data.end());*/
}

const TE::Render::VertexBufferInfo& TE::Render::Mesh::GetVertexBufferInfo() const
{
	return m_vertexBufferInfo;
}

const TE::Render::IndexBufferInfo& TE::Render::Mesh::GetIndexBufferInfo() const
{
	return m_indexBufferInfo;
}

const U8* TE::Render::Mesh::GetVertexBufferDataPtr() const
{
    return GetDataFront() + m_vertexBufferOffset;
}

const U8* TE::Render::Mesh::GetIndexBufferDataPtr() const
{
    return GetDataFront() + m_indexBufferOffset;
}

/*
void TE::Render::Mesh::JSONDeserialize( const Json::Value& jsonMesh )
{
	if (jsonMesh["VertexBufferLayout"].isMember("Position"))
	{
		VertexBufferInfo::LayoutElement layoutElement;
		layoutElement.layoutSemantic = Semantics::POSITION;
		layoutElement.valueType = jsonMesh["VertexBufferLayout"]["Position"]["ValueType"].asInt();
		layoutElement.valueCount = jsonMesh["VertexBufferLayout"]["Position"]["ValueCount"].asInt();
		layoutElement.byteOffset = jsonMesh["VertexBufferLayout"]["Position"]["ByteOffset"].asInt();
		m_vertexBufferInfo.layoutElements.push_back(layoutElement);
	}
	
	if (jsonMesh["VertexBufferLayout"].isMember("Normal"))
	{
		VertexBufferInfo::LayoutElement layoutElement;
		layoutElement.layoutSemantic = Semantics::NORMAL;
		layoutElement.valueType = jsonMesh["VertexBufferLayout"]["Normal"]["ValueType"].asInt();
		layoutElement.valueCount = jsonMesh["VertexBufferLayout"]["Normal"]["ValueCount"].asInt();
		layoutElement.byteOffset = jsonMesh["VertexBufferLayout"]["Normal"]["ByteOffset"].asInt();
		m_vertexBufferInfo.layoutElements.push_back(layoutElement);
	}

	if (jsonMesh["VertexBufferLayout"].isMember("Textures"))
	{
		const Json::Value textures = jsonMesh["VertexBufferLayout"]["Textures"];
		for (U32 i = 0; i < textures.size(); ++i)
		{
			VertexBufferInfo::LayoutElement layoutElement;
			layoutElement.layoutSemantic = Semantics::TEXTURE0 + i;
			layoutElement.valueType = jsonMesh["VertexBufferLayout"]["Textures"][i]["ValueType"].asInt();
			layoutElement.valueCount = jsonMesh["VertexBufferLayout"]["Textures"][i]["ValueCount"].asInt();
			layoutElement.byteOffset = jsonMesh["VertexBufferLayout"]["Textures"][i]["ByteOffset"].asInt();
			m_vertexBufferInfo.layoutElements.push_back(layoutElement);
		}
	}

	m_vertexBufferOffset = jsonMesh["VertexBuffer"]["Offset"].asInt();
	m_vertexBufferInfo.primitiveType = jsonMesh["VertexBuffer"]["PrimitiveType"].asInt();
	m_vertexBufferInfo.usage = jsonMesh["VertexBuffer"]["Usage"].asInt();
	m_vertexBufferInfo.dataElementCount = jsonMesh["VertexBuffer"]["DataElementCount"].asInt();
	m_vertexBufferInfo.dataElementSize = jsonMesh["VertexBuffer"]["DataElementSize"].asInt();
	m_vertexBufferInfo.dataSize = jsonMesh["VertexBuffer"]["DataSize"].asInt();

	m_indexBufferOffset = jsonMesh["IndexBuffer"]["Offset"].asInt();
	m_indexBufferInfo.usage = jsonMesh["IndexBuffer"]["Usage"].asInt();
	m_indexBufferInfo.dataElementCount = jsonMesh["IndexBuffer"]["DataElementCount"].asInt();
	m_indexBufferInfo.dataElementSize = jsonMesh["IndexBuffer"]["DataElementSize"].asInt();
	m_indexBufferInfo.dataSize = jsonMesh["IndexBuffer"]["DataSize"].asInt();
}

void TE::Render::Mesh::JSONSerialize(Json::Value& jsonValue)
{
	std::string semanticName;
	U32 textureIndex = 0;
	for (U32 i = 0; i < m_vertexBufferInfo.layoutElements.size(); ++i)
	{
		switch(m_vertexBufferInfo.layoutElements[i].layoutSemantic)
		{
			case Semantics::POSITION:
				jsonValue["VertexBufferLayout"]["Position"]["ValueType"] = m_vertexBufferInfo.layoutElements[i].valueType;
				jsonValue["VertexBufferLayout"]["Position"]["ValueCount"] = m_vertexBufferInfo.layoutElements[i].valueCount;
				jsonValue["VertexBufferLayout"]["Position"]["ByteOffset"] = m_vertexBufferInfo.layoutElements[i].byteOffset;
				break;
			case Semantics::NORMAL:
				jsonValue["VertexBufferLayout"]["Normal"]["ValueType"] = m_vertexBufferInfo.layoutElements[i].valueType;
				jsonValue["VertexBufferLayout"]["Normal"]["ValueCount"] = m_vertexBufferInfo.layoutElements[i].valueCount;
				jsonValue["VertexBufferLayout"]["Normal"]["ByteOffset"] = m_vertexBufferInfo.layoutElements[i].byteOffset;
				break;
			case Semantics::TEXTURE0:
			case Semantics::TEXTURE1:
			case Semantics::TEXTURE2:
			case Semantics::TEXTURE3:
			case Semantics::TEXTURE4:
			case Semantics::TEXTURE5:
			case Semantics::TEXTURE6:
			case Semantics::TEXTURE7:
				jsonValue["VertexBufferLayout"]["Textures"][textureIndex]["ValueType"] = m_vertexBufferInfo.layoutElements[i].valueType;
				jsonValue["VertexBufferLayout"]["Textures"][textureIndex]["ValueCount"] = m_vertexBufferInfo.layoutElements[i].valueCount;
				jsonValue["VertexBufferLayout"]["Textures"][textureIndex]["ByteOffset"] = m_vertexBufferInfo.layoutElements[i].byteOffset;
				++textureIndex;
				break;
			default:
				assert(false && "Unknown layout semantics");
				break;
		}
	}
	
	jsonValue["VertexBuffer"]["Offset"] = m_vertexBufferOffset;
	jsonValue["VertexBuffer"]["PrimitiveType"] = m_vertexBufferInfo.primitiveType;
	jsonValue["VertexBuffer"]["Usage"] = m_vertexBufferInfo.usage;
	jsonValue["VertexBuffer"]["DataElementCount"] = m_vertexBufferInfo.dataElementCount;
	jsonValue["VertexBuffer"]["DataElementSize"] = m_vertexBufferInfo.dataElementSize;
	jsonValue["VertexBuffer"]["DataSize"] = m_vertexBufferInfo.dataSize;
	
	jsonValue["IndexBuffer"]["Offset"] = m_indexBufferOffset;
	jsonValue["IndexBuffer"]["Usage"] = m_indexBufferInfo.usage;
	jsonValue["IndexBuffer"]["DataElementCount"] = m_indexBufferInfo.dataElementCount;
	jsonValue["IndexBuffer"]["DataElementSize"] = m_indexBufferInfo.dataElementSize;
	jsonValue["IndexBuffer"]["DataSize"] = m_indexBufferInfo.dataSize;
	
	Json::StyledWriter writer;
	std::cout << writer.write(jsonValue);
}
*/

void TE::Render::Mesh::Load( IO::FileIO& fileIO )
{
	Resource::Load(fileIO);

    IO::ReadU32FromU8Array(m_jsonOffset, GetDataFront());

	/*Json::Value jsonMesh;
	IO::JsonValueFromData(GetDataFront()+m_jsonOffset, GetDataFront()+GetDataSize(), jsonMesh);
	JSONDeserialize(jsonMesh);*/
}

void TE::Render::Mesh::Save( IO::FileIO& fileIO )
{
	Resource::Save(fileIO);
}
