#include "TETransformObject.h"
#include "TEEventManager.h"
#include "TEOrientationEvent.h"
#include "TEScaleEvent.h"
#include "TETransformSystem.h"
#include "TETranslationEvent.h"
#include "TEValue.h"

TE::Transform::TransformObject::TransformObject(I32 objectId, Event::EventManager &eventManager)
    : m_position(Math::Vector3D<F32>::VECTOR3D_ZERO),
      m_scale(Math::Vector3D<F32>::VECTOR3D_ONE),
      m_orientation(Math::Quaternion<F32>::QUATERNION_IDENTITY),
      m_objectId(objectId),
      m_eventManager(eventManager) {}

TE::Transform::TransformObject::~TransformObject() {}

void TE::Transform::TransformObject::SetValue(Core::Value &value) {
    switch (value.GetValueType()) {
    case Values::Position:
        m_position = GetVector(value);
        PostSubjectChanges(Engine::Change::Transform::Position);
        break;
    case Values::Scale:
        m_scale = GetVector(value);
        PostSubjectChanges(Engine::Change::Transform::Scale);
        break;
    case Values::Orientation:
        m_orientation = GetQuaternion(value);
        PostSubjectChanges(Engine::Change::Transform::Orientation);
        break;
    case Values::SubscribeTranslationEvent:
        if (value.GetBool())
            m_eventManager.Subscribe<TE::Event::TranslationEvent>(this);
        else
            m_eventManager.UnSubscribe<TE::Event::TranslationEvent>(this);
        break;
    case Values::SubscribeScaleEvent:
        if (value.GetBool())
            m_eventManager.Subscribe<TE::Event::ScaleEvent>(this);
        else
            m_eventManager.UnSubscribe<TE::Event::ScaleEvent>(this);
        break;
    case Values::SubscribeOrientationEvent:
        if (value.GetBool())
            m_eventManager.Subscribe<TE::Event::OrientationEvent>(this);
        else
            m_eventManager.UnSubscribe<TE::Event::OrientationEvent>(this);
        break;
    }
}

void TE::Transform::TransformObject::Initialize() {
    PostSubjectChanges(Engine::Change::Transform::All);
}

void TE::Transform::TransformObject::Cleanup() {}

I32 TE::Transform::TransformObject::GetObjectId() const { return m_objectId; }

/*void TE::Transform::TransformObject::JSONDeserialize( const Json::Value& jsonValue )
{
    Core::Value value(Values::Position);
    value.AddF32(static_cast<F32>(jsonValue["Position"]["x"].asDouble()));
    value.AddF32(static_cast<F32>(jsonValue["Position"]["y"].asDouble()));
    value.AddF32(static_cast<F32>(jsonValue["Position"]["z"].asDouble()));
    SetValue(value);

    value.Reset(Values::Scale);
    value.AddF32(static_cast<F32>(jsonValue["Scale"]["x"].asDouble()));
    value.AddF32(static_cast<F32>(jsonValue["Scale"]["y"].asDouble()));
    value.AddF32(static_cast<F32>(jsonValue["Scale"]["z"].asDouble()));
    SetValue(value);

    value.Reset(Values::Orientation);
    value.AddF32(static_cast<F32>(jsonValue["Orientation"]["x"].asDouble()));
    value.AddF32(static_cast<F32>(jsonValue["Orientation"]["y"].asDouble()));
    value.AddF32(static_cast<F32>(jsonValue["Orientation"]["z"].asDouble()));
    value.AddF32(static_cast<F32>(jsonValue["Orientation"]["w"].asDouble()));
    SetValue(value);
}

void TE::Transform::TransformObject::JSONSerialize(Json::Value& jsonValue)
{

}
*/

Bitmask64 TE::Transform::TransformObject::GetDesiredSystemChanges() {
    return Engine::Change::Transform::All;
}

Bitmask64 TE::Transform::TransformObject::GetPotentialSystemChanges() {
    return Engine::Change::Transform::All;
}

void TE::Transform::TransformObject::OnSubjectChange(Subject *subject, Bitmask64 changeBits) {
    if (changeBits & Engine::Change::Transform::All) {
        auto transformChange =
            Engine::GetChangeData<Engine::Change::TransformChange>(subject, changeBits);

        if (changeBits & Engine::Change::Transform::Position) {
            m_position = *transformChange.position;
        }
        if (changeBits & Engine::Change::Transform::Scale) {
            m_scale = *transformChange.scale;
        }
        if (changeBits & Engine::Change::Transform::Orientation) {
            m_orientation = *transformChange.orientation;
        }
    }
}

void TE::Transform::TransformObject::HandleEvent(Event::TranslationEvent &translationEvent) {
    m_position += translationEvent.GetTranslation();

    PostSubjectChanges(Engine::Change::Transform::Position);
}

void TE::Transform::TransformObject::HandleEvent(TE::Event::ScaleEvent &scaleEvent) {
    m_scale += scaleEvent.GetScale();

    PostSubjectChanges(Engine::Change::Transform::Scale);
}

void TE::Transform::TransformObject::HandleEvent(TE::Event::OrientationEvent &orientationEvent) {
    m_orientation *= orientationEvent.GetOrientation();

    PostSubjectChanges(Engine::Change::Transform::Orientation);
}

TE::Engine::Change::ChangeDataPtrVar
TE::Transform::TransformObject::GetChangeData(Bitmask64 changeBits) {
    static Engine::Change::TransformChange transformChange;

    transformChange.position =
        (changeBits & Engine::Change::Transform::Position) ? &m_position : nullptr;
    transformChange.scale = (changeBits & Engine::Change::Transform::Scale) ? &m_scale : nullptr;
    transformChange.orientation =
        (changeBits & Engine::Change::Transform::Position) ? &m_orientation : nullptr;

    return Engine::Change::ChangeDataPtrVar(transformChange);
}
