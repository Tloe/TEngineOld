#ifndef TEASSETIMPORTER_H
#define TEASSETIMPORTER_H

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <set>
#include <stdint.h>
#include "TEMatrix4D.h"
#include "TEMesh.h"

namespace TE
{
	namespace Intersection { struct Obb; }
	namespace Intersection { struct BSphere; }
	
	enum
	{
		VERTEXBUFFER_POSITION = 0x01,
		VERTEXBUFFER_NORMALS = 0x02,
		VERTEXBUFFER_TEXTURECOORDS = 0x04
	};

	class AssetImporter
	{
	public:
		AssetImporter();
			
		bool OpenFile(const std::string& filePath);
		void GetMesheNames(std::vector<std::string>& mesheNames);
		TE::Intersection::BSphere GetBShere(const std::string& meshName);
		TE::Intersection::Obb GetObb(const std::string& meshName);
		Render::Mesh GetMesh(const std::string& meshName, I32 vertexBufferFlags, Enum vertexBufferUsage, Enum indexBufferUsage);
	private:
		struct MeshNode 
		{
			std::string meshName;
			unsigned index;
			Math::Matrix4D<Real> transform;
		};

		typedef std::unordered_map<std::string, MeshNode> MeshNodeMap;
		typedef std::set<unsigned> BSphereMeshIndexSet;
		typedef std::set<unsigned> ObbMeshIndexSet;

		void GetVertexBuffer(const std::string& meshName, I32 flags, std::vector<U8>& data, Render::VertexBufferInfo& vertexBufferInfo);
		void GetIndexBuffer(const std::string& meshName, std::vector<U8>& data, Render::IndexBufferInfo& indexBufferInfo);
		void GetLayoutElements(const std::string& meshName, I32 vertexBufferFlags, std::vector<Render::VertexBufferInfo::LayoutElement> &layoutElements);
		void SetupMeshIndexMaps(aiNode* assimpNode);
		void RecurseGatherMeshes(aiNode* assimpNode, std::list<MeshNode>& meshes);
		void FillMeshIndexMap(std::list<MeshNode>& meshes);
		void FillMeshBoundingVolumeContainers(std::list<MeshNode>& meshes);
		const aiScene* m_assimpScene;
		Assimp::Importer m_assimpImporter;

		MeshNodeMap m_meshIndexMap;
		BSphereMeshIndexSet m_bsphereSet;
		ObbMeshIndexSet m_obbSet;
	};

	Math::Matrix4D<Real> ConvertAssimpTranform(aiMatrix4x4& transform);
}

#endif
