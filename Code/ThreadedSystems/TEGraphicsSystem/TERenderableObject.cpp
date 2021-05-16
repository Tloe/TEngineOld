#include "TERenderableObject.h"
#include "TEFile.h"
#include "TEFileIO.h"
#include "TERenderable.h"
#include "TERenderer.h"
#include "TESceneManager.h"
#include "TEValue.h"
#include "TEVariant.h"

TE::Graphics::RenderableObject::RenderableObject(I32 objectId, SceneGraph::SceneManager &sceneManager)
    : GraphicsObject(objectId, GraphicsObjectType::Renderable, sceneManager),
      m_sceneManager(sceneManager) {
}

TE::Graphics::RenderableObject::~RenderableObject() {
}

void TE::Graphics::RenderableObject::SetValue(Core::Value &value) {
    switch (value.GetValueType()) {
    case Values::Mesh: {
        auto meshHandle = m_sceneManager.GetRenderer().GetMeshHandle(value.GetString());
        m_renderable.SetMesh(meshHandle);
        break;
    }
    case Values::Texture: {
        auto textureHandle = m_sceneManager.GetRenderer().GetTextureHandle(value.GetString());
        m_renderable.AddTexture(textureHandle);
        break;
    }
    case Values::Effect: {
        auto effectHandle = m_sceneManager.GetRenderer().GetEffectHandle(value.GetString());
        m_renderable.SetEffect(effectHandle);
        break;
    }
    case Values::BoundingVolume: {
        if (value.GetString() == "Sphere") {
            Intersection::BSphere bounding;
            // TODO: This will calculate bounding with all float values in the vertex buffer
            //		(including coords, normals,++)
            auto meshHandle = m_renderable.GetMesh();
            BSphereFromVertexData(bounding,
                                  reinterpret_cast<const F32 *>(meshHandle->GetVertexBufferDataPtr()),
                                  meshHandle->GetVertexBufferInfo().dataElementCount);
            m_renderable.SetBounding(bounding);
        }
        break;
    }
    case Values::Parrent: {
        m_sceneManager.AddToNode(value.GetString(), m_renderable);
        break;
    }
    }
}

void TE::Graphics::RenderableObject::Initialize() {
    m_sceneManager.InitRenderable(m_renderable);
}

void TE::Graphics::RenderableObject::Cleanup() {
    m_sceneManager.CleanupRenderable(m_renderable);
}

/*
void TE::Graphics::RenderableObject::JSONDeserialize( const Json::Value& jsonValue )
{
    Core::Value value(Values::Mesh);
    value.AddString(jsonValue["Mesh"].asString());
    SetValue(value);

    const Json::Value textures = jsonValue["Textures"];
        for(U32 i = 0; i < textures.size(); ++i)
        {
        value.Reset(Values::Texture);
        value.AddString(textures[i].asString());
        SetValue(value);
    }

        const Json::Value effects = jsonValue["Effects"];
    assert(effects.size() <= 1 && "Needs more logic");
    for(U32 i = 0; i < effects.size(); ++i)
        {
        value.Reset(Values::Effect);
        value.AddString(effects[i].asString());
        SetValue(value);
        }

    const Json::Value boundings = jsonValue["BoundingVolumes"];
    for(U32 i = 0; i < boundings.size(); ++i)
        {
                if (boundings[i].asString() == "Sphere")
                {
            value.Reset(Values::BoundingVolume);
            value.AddString("Sphere");
            SetValue(value);
                }
        }

    value.Reset(Values::Parrent);
    value.AddString(jsonValue["Parrent"].asString());
    SetValue(value);
}

void TE::Graphics::RenderableObject::JSONSerialize(Json::Value& jsonValue)
{

}
*/

void TE::Graphics::RenderableObject::OnSubjectChange(Subject *subject, Bitmask64 changeBits) {
    if (changeBits & Engine::Change::Transform::All) {
        auto transformChange = Engine::GetChangeData<Engine::Change::TransformChange>(subject, changeBits);

        if (changeBits & Engine::Change::Transform::Position) {
            m_renderable.SetTranslation(*transformChange.position);
        }
        if (changeBits & Engine::Change::Transform::Scale) {
            m_renderable.SetScale(*transformChange.scale);
        }
        if (changeBits & Engine::Change::Transform::Orientation) {
            m_renderable.SetOrientation(*transformChange.orientation);
        }

        m_renderable.Update();
    }
}
