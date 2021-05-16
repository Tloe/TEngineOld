#ifndef TENETWORKOBJECT_H
#define TENETWORKOBJECT_H

#include "TEChangeData.h"
#include "TECircularQue.h"
#include "TEEventHandler.h"
#include "TEPacket.h"
#include "TEQuaternion.h"
#include "TESystemObject.h"
#include "TEVector3D.h"

namespace TE {
    namespace Engine {
        class SubjectVisitor;
    }
    namespace Network {
        class MessageHandler;
    }
    namespace Event {
        class EventManager;
    }
    namespace Net {
        class Packet;
    }

    namespace Network {
        class NetworkObject
            : public Engine::SystemObject,
              public Event::EventHandler {
          public:
            struct Values {
                enum {
                    SubscribeTranslationEvent,
                    SubscribeScaleEvent,
                    SubscribeOrientationEvent
                };
            };

            NetworkObject(I32 objectId, Event::EventManager &eventManager, MessageHandler &messageHandler);

            virtual void SetValue(Core::Value &value);
            virtual void Initialize();
            virtual void Cleanup();

            virtual Bitmask64 GetDesiredSystemChanges();
            virtual Bitmask64 GetPotentialSystemChanges();
            virtual Engine::Change::ChangeDataPtrVar GetChangeData(Bitmask64 changeBits);

            virtual void OnSubjectChange(Subject *subject, Bitmask64 changeBits);

            virtual I32 GetObjectId() const;
            virtual Priority GetPriority() const;
            virtual void HandleEvent(Event::TranslationEvent &translationEvent);
            virtual void HandleEvent(Event::ScaleEvent &scaleEvent);
            virtual void HandleEvent(Event::OrientationEvent &orientationEvent);

            virtual std::string GetME() { return "Network"; }

            Net::Packet CreateUpdatePacket();
            void RemoteObjectUpdate(Net::Packet &packet);
            void RemoteTranslationEvent(Net::Packet &packet, U64 time);
            void RemoteScaleEvent(Net::Packet &packet, U64 time);
            void RemoteOrientationEvent(Net::Packet &packet, U64 time);
            void RemoteAddForceEvent(Net::Packet &packet, U64 time);

          private:
            I32 m_objectId;
            Math::Vector3D<Real> m_position;
            Math::Vector3D<Real> m_scale;
            Math::Quaternion<Real> m_orientation;
            bool m_positionUpdated;
            bool m_scaleUpdated;
            bool m_orientationUpdated;
            MessageHandler &m_messageHandler;
            Event::EventManager &m_eventManager;

            Utils::CircularQue<Math::Vector3D<F32>, 100> m_storedTranslations;
            Utils::CircularQue<Math::Vector3D<F32>, 100> m_storedScales;
            Utils::CircularQue<Math::Quaternion<F32>, 100> m_storedRotations;
            I8 m_lastProcessedTranslation;
            I8 m_lastProcessedRotation;
        };

        typedef std::shared_ptr<NetworkObject> NetworkObjectSPtr;
        typedef std::weak_ptr<NetworkObject> NetworkObjectWPtr;
    }
}

#endif
