#include "AssetImporterTest.h"
#include "TEAssetImporter.h"
#include "TEFileSystemIO.h"
#include "TEMesh.h"
#include <vector>

int AssetImporterTest() {
    TE::AssetImporter assetImporter;

    assetImporter.OpenFile("D:/coding/tengine/resources/space_frigate_6.3ds");

    std::vector<std::string> meshes;
    assetImporter.GetMesheNames(meshes);

    TE::Render::Mesh cube01 = assetImporter.GetMesh(
        "space_frig",
        TE::VERTEXBUFFER_POSITION | TE::VERTEXBUFFER_NORMALS | TE::VERTEXBUFFER_TEXTURECOORDS,
        TE::Render::Usage::DYNAMIC, TE::Render::Usage::DYNAMIC);

    TE::IO::FileSystemIO fileIO("D:/coding/tengine/Executables/EngineTest");
    cube01.SetFilePath("/Meshes/space_frigate.mesh");
    cube01.Save(fileIO);

    return 0;
}
