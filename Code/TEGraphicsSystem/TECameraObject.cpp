#include <TECameraObject.h>
#include "TECamera.h"
#include "TECameraNode.h"
#include "TETransformChange.h"
#include "TESubjectVisitors.h"
#include "TEValue.h"

TE::Graphics::CameraObject::CameraObject( I32 objectId, SceneGraph::SceneManager& sceneManager)
    : GraphicsObject(objectId, GraphicsObjectType::Camera, sceneManager)
    , m_sceneManager(sceneManager)
    , m_cameraNode(m_camera)
{

}

void TE::Graphics::CameraObject::SetValue(Core::Value & value)
{
    switch(value.GetValueType())
    {
    case Values::Frustrum:
        if(value.GetI32() == FrustrumType::FromFov)
        {
            F32 fov = value.GetF32();
            F32 aspectRatio = value.GetF32();
            F32 directionMin = value.GetF32();
            F32 directionMax = value.GetF32();

            m_camera.SetFrustrum(fov, aspectRatio, directionMin, directionMax);
        }
        break;
    case Values::ActiveCamera:
        if(value.GetBool())
            GetSceneManager().SetActiveCamera(m_camera);
        break;
    case Values::Parrent:
        m_sceneManager.AddToNode(value.GetString(), m_cameraNode);
        break;
    }
}

void TE::Graphics::CameraObject::Initialize()
{
}

void TE::Graphics::CameraObject::Cleanup()
{
}

/*void TE::Graphics::CameraObject::JSONDeserialize( const Json::Value& jsonValue )
{
    Core::Value value(Values::Frustrum);

	if (jsonValue["Frustrum"]["Type"] == FrustrumType::FromFov)
	{
        F32 fov = static_cast<F32>(jsonValue["Frustrum"]["Fov"].asDouble());
        F32 aspectRatio = static_cast<F32>(jsonValue["Frustrum"]["AspectRatio"].asDouble());
        F32 directionMin = static_cast<F32>(jsonValue["Frustrum"]["DirMin"].asDouble());
        F32 directionMax = static_cast<F32>(jsonValue["Frustrum"]["DirMax"].asDouble());

        value.AddI32(FrustrumType::FromFov);
        value.AddF32(fov);
        value.AddF32(aspectRatio);
        value.AddF32(directionMin);
        value.AddF32(directionMax);

        SetValue(value);
	}

    value.Reset(Values::ActiveCamera);
    value.AddBool(jsonValue["ActiveCamera"].asBool());
    SetValue(value);

    value.Reset(Values::Parrent);
    value.AddString(jsonValue["Parrent"].asString());
    SetValue(value);
}

void TE::Graphics::CameraObject::JSONSerialize(Json::Value& jsonValue)
{

}
*/
void TE::Graphics::CameraObject::OnSubjectChange( Subject* subject, Bitmask64 changeBits )
{
	if (changeBits & Engine::Change::Transform::All)
	{
		Engine::ChangeVisitor<Engine::TransformChange> visitor;
		subject->AcceptSubjectVisitor(visitor);

		if (changeBits & Engine::Change::Transform::Position)
		{
			m_cameraNode.SetTranslation(visitor.GetChangeInterface()->GetPosition());
		}
		if (changeBits & Engine::Change::Transform::Orientation)
		{
			m_cameraNode.SetOrientation(visitor.GetChangeInterface()->GetOrientation());
		}
		if (changeBits & Engine::Change::Transform::Scale)
		{
			m_cameraNode.SetScale(visitor.GetChangeInterface()->GetScale());
		}
		
		m_cameraNode.Update();
	}
}
