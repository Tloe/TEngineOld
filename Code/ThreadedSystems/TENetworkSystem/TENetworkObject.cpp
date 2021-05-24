#include "TENetworkObject.h"
#include "TEEventManager.h"
#include "TEMessageHandler.h"
#include "TEOrientationEvent.h"
#include "TEPacket.h"
#include "TEQuaternion.h"
#include "TEScaleEvent.h"
#include "TETranslationEvent.h"
#include "TEValue.h"
#include "TEVector3D.h"

namespace {
    namespace PacketChanges {
        enum { Position = (1 << 0), Scale = (1 << 1), Orientation = (1 << 2) };
    }

    U8 GetPacketChangeMask(bool positionUpdated, bool scaleUpdated, bool orientationUpdated) {
        U8 mask = 0;
        if (positionUpdated)
            mask |= PacketChanges::Position;
        if (scaleUpdated)
            mask |= PacketChanges::Scale;
        if (orientationUpdated)
            mask |= PacketChanges::Orientation;

        return mask;
    }

    inline I8 MostRecentCircular(I8 s1, I8 s2, I8 maxSequenceNo = 99) {
        if (((s1 > s2) && (s1 - s2 <= maxSequenceNo / 2)) ||
            ((s2 > s1) && (s2 - s1 > maxSequenceNo / 2)))
            return s1;

        return s2;
    }

    inline bool IsMoreRecentCircular(I8 s1, I8 s2, I8 maxSequenceNo = 99) {
        return ((s1 > s2) && (s1 - s2 <= maxSequenceNo / 2)) ||
               ((s2 > s1) && (s2 - s1 > maxSequenceNo / 2));
    }

    U32 ReadCircular100Index(TE::Net::Packet &packet) {
        I8 temp;
        packet.ReadI8(temp);
        U32 index = static_cast<U32>(temp) + 1;
        if (index == 100)
            index = 0;

        return index;
    }

    Bitmask UpdatePosition(TE::Math::Vector3D<F32> &position,
                           TE::Net::Packet &packet,
                           TE::Utils::CircularQue<TE::Math::Vector3D<F32>, 100> &storedTranslations,
                           U32 startTranslationIndex) {
        if (!IsMoreRecentCircular(storedTranslations.GetHeadIndex(), startTranslationIndex)) {
            position = ReadVector(packet);
            storedTranslations.PopToIndex(startTranslationIndex);
            while (!storedTranslations.Empty()) {
                position += storedTranslations.GetHead();
                storedTranslations.Pop();
            }
            return TE::Engine::Change::Transform::Position;
        } else {
            ReadVector(packet);
            return TE::Engine::Change::NotSet;
        }
    }

    Bitmask
    UpdateOrientation(TE::Math::Quaternion<F32> &orientation,
                      TE::Net::Packet &packet,
                      TE::Utils::CircularQue<TE::Math::Quaternion<F32>, 100> &storedRotations,
                      U32 startRotationIndex) {
        if (!IsMoreRecentCircular(storedRotations.GetHeadIndex(), startRotationIndex)) {
            orientation = ReadQuaternion(packet);
            storedRotations.PopToIndex(startRotationIndex);
            while (!storedRotations.Empty()) {
                orientation *= storedRotations.GetHead();
                storedRotations.Pop();
            }
            return TE::Engine::Change::Transform::Orientation;
        } else {
            ReadQuaternion(packet);
            return TE::Engine::Change::NotSet;
        }
    }
}

TE::Network::NetworkObject::NetworkObject(I32 objectId,
                                          Event::EventManager &eventManager,
                                          MessageHandler &messageHandler)
    : m_objectId(objectId),
      m_position(Math::Vector3D<F32>::VECTOR3D_ZERO),
      m_scale(Math::Vector3D<F32>::VECTOR3D_ONE),
      m_orientation(Math::Quaternion<F32>::QUATERNION_IDENTITY),
      m_messageHandler(messageHandler),
      m_eventManager(eventManager),
      m_lastProcessedTranslation(0),
      m_lastProcessedRotation(0) {}

void TE::Network::NetworkObject::HandleEvent(TE::Event::TranslationEvent &event) {
    // Subscribed only on client
    Net::Packet packet;
    packet.BeginPacket();
    packet.WriteMessageType(MessageType::TranslationEvent);

    packet.WriteU8(static_cast<U8>(m_storedTranslations.GetTailIndex()));
    const Math::Vector3D<F32> &translation = event.GetTranslation();
    m_storedTranslations.Push(translation);
    WriteVector(translation, packet);

    packet.EndPacket();

    m_messageHandler.QueBroadcastMessage(packet, true);
}

void TE::Network::NetworkObject::HandleEvent(TE::Event::ScaleEvent &event) {
    // Subscribed only on client
}

void TE::Network::NetworkObject::HandleEvent(TE::Event::OrientationEvent &event) {
    // Subscribed only on client
    Net::Packet packet;
    packet.BeginPacket();
    packet.WriteMessageType(MessageType::OrientationEvent);

    packet.WriteU8(static_cast<U8>(m_storedRotations.GetTailIndex()));
    const Math::Quaternion<F32> &orientation = event.GetOrientation();
    m_storedRotations.Push(orientation);
    WriteQuaternion(orientation, packet);

    packet.EndPacket();

    m_messageHandler.QueBroadcastMessage(packet, true);
}

void TE::Network::NetworkObject::SetValue(Core::Value &value) {
    switch (value.GetValueType()) {
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

void TE::Network::NetworkObject::Initialize() {}

void TE::Network::NetworkObject::Cleanup() {}

Bitmask64 TE::Network::NetworkObject::GetDesiredSystemChanges() {
    return Engine::Change::Transform::All;
}

Bitmask64 TE::Network::NetworkObject::GetPotentialSystemChanges() {
    return Engine::Change::Transform::All;
}

TE::Engine::Change::ChangeDataPtrVar
TE::Network::NetworkObject::GetChangeData(Bitmask64 changeBits) {
    static Engine::Change::TransformChange transformChange;

    transformChange.position =
        (changeBits & Engine::Change::Transform::Position) ? &m_position : nullptr;
    transformChange.scale = (changeBits & Engine::Change::Transform::Scale) ? &m_scale : nullptr;
    transformChange.orientation =
        (changeBits & Engine::Change::Transform::Position) ? &m_orientation : nullptr;

    return Engine::Change::ChangeDataPtrVar(transformChange);
}

void TE::Network::NetworkObject::OnSubjectChange(Subject *subject, Bitmask64 changeBits) {
    if (changeBits & Engine::Change::Transform::Position) {
        auto transformChange =
            Engine::GetChangeData<Engine::Change::TransformChange>(subject, changeBits);

        if (changeBits & Engine::Change::Transform::Position) {
            m_position        = *transformChange.position;
            m_positionUpdated = true;
        }
        if (changeBits & Engine::Change::Transform::Scale) {
            m_scale        = *transformChange.scale;
            m_scaleUpdated = true;
        }
        if (changeBits & Engine::Change::Transform::Orientation) {
            m_orientation        = *transformChange.orientation;
            m_orientationUpdated = true;
        }
    }
}

I32 TE::Network::NetworkObject::GetObjectId() const { return m_objectId; }

TE::Engine::Subject::Priority TE::Network::NetworkObject::GetPriority() const {
    return Priority::Level4;
}

TE::Net::Packet TE::Network::NetworkObject::CreateUpdatePacket() {
    // Server side only
    Net::Packet packet;
    packet.BeginPacket();
    packet.WriteI32(m_objectId);

    packet.WriteU8(::GetPacketChangeMask(m_positionUpdated, m_scaleUpdated, m_orientationUpdated));
    if (m_positionUpdated) {
        packet.WriteI8(m_lastProcessedTranslation);
        WriteVector(m_position, packet);
        m_positionUpdated = false;
    }
    if (m_scaleUpdated) {
        WriteVector(m_scale, packet);
        m_scaleUpdated = false;
    }
    if (m_orientationUpdated) {
        packet.WriteI8(m_lastProcessedRotation);
        WriteQuaternion(m_orientation, packet);
        m_orientationUpdated = false;
    }

    packet.EndPacket();
    return packet;
}

void TE::Network::NetworkObject::RemoteObjectUpdate(TE::Net::Packet &packet) {
    // Client side only
    U8 updatedMask;
    packet.ReadU8(updatedMask);
    Bitmask64 changeMask = Engine::Change::NotSet;
    if (updatedMask & PacketChanges::Position) {
        U32 startTranslationIndex = ReadCircular100Index(packet);

        changeMask |=
            UpdatePosition(m_position, packet, m_storedTranslations, startTranslationIndex);
    }
    if (updatedMask & PacketChanges::Scale) {
        m_scale = ReadVector(packet);
        changeMask |= Engine::Change::Transform::Scale;
    }
    if (updatedMask & PacketChanges::Orientation) {
        U32 startOrientationIndex = ReadCircular100Index(packet);

        changeMask |=
            UpdateOrientation(m_orientation, packet, m_storedRotations, startOrientationIndex);
    }

    if (changeMask != Engine::Change::NotSet) {
        PostSubjectChanges(changeMask);
    }
}

void TE::Network::NetworkObject::RemoteTranslationEvent(TE::Net::Packet &packet, U64 time) {
    // Server side only
    I8 translationIndex;
    packet.ReadI8(translationIndex);
    m_position += ReadVector(packet);
    m_positionUpdated          = true;

    m_lastProcessedTranslation = ::MostRecentCircular(m_lastProcessedTranslation, translationIndex);

    PostSubjectChanges(Engine::Change::Transform::Position);
}

void TE::Network::NetworkObject::RemoteScaleEvent(TE::Net::Packet &packet, U64 time) {
    // Server side only
    Math::Vector3D<F32> scale = ReadVector(packet);
    m_scale += scale;
    m_scaleUpdated = true;
    PostSubjectChanges(Engine::Change::Transform::Scale);
}

void TE::Network::NetworkObject::RemoteOrientationEvent(TE::Net::Packet &packet, U64 time) {
    // Server side only
    I8 orientationIndex;
    packet.ReadI8(orientationIndex);
    m_orientation *= ReadQuaternion(packet);
    ;
    m_orientationUpdated    = true;

    m_lastProcessedRotation = ::MostRecentCircular(m_lastProcessedRotation, orientationIndex);

    PostSubjectChanges(Engine::Change::Transform::Orientation);
}

void TE::Network::NetworkObject::RemoteAddForceEvent(TE::Net::Packet &packet, U64 time) {}
