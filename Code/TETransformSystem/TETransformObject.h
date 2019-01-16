#ifndef TETRANSFORMOBJECT_H
#define TETRANSFORMOBJECT_H

#include "TEVector3D.h"
#include "TEQuaternion.h"
#include "TESystemObject.h"
#include "TEEventHandler.h"

namespace TE
{
    namespace Event { class EventManager; }
	namespace Event { class TranslationEvent; }
    namespace Event { class ScaleEvent; }
    namespace Event { class OrientationEvent; }

	namespace Transform
	{
		class TransformObject
			: public Engine::SystemObject
			, public Event::EventHandler
		{
		public:
            struct Values
            {
                enum
                {
                    Position,
                    Scale,
                    Orientation,
					SubscribeTranslationEvent,
					SubscribeScaleEvent,
					SubscribeOrientationEvent
                };
            };

            TransformObject(I32 objectId, Event::EventManager & eventManager);
			virtual ~TransformObject();

            virtual void SetValue(Core::Value & value);
            virtual void Initialize();
            virtual void Cleanup();
            virtual I32 GetObjectId() const;
			
            virtual Bitmask64 GetDesiredSystemChanges();
			virtual Bitmask64 GetPotentialSystemChanges();
            virtual Engine::Change::ChangeDataPtrVar GetChangeData(Bitmask64 changeBits); 

            //virtual void JSONDeserialize(const Json::Value& jsonValue);
            //virtual void JSONSerialize(Json::Value& jsonValue);
            virtual void OnSubjectChange( Subject* subject, Bitmask64 changeBits );
            virtual void HandleEvent(Event::TranslationEvent &translationEvent);
            virtual void HandleEvent(Event::ScaleEvent &scaleEvent);
            virtual void HandleEvent(Event::OrientationEvent &orientationEvent);

            virtual std::string GetME(){ return "Transform";}

		private:
			Math::Vector3D<Real> m_position;
			Math::Vector3D<Real> m_scale;
			Math::Quaternion<Real> m_orientation;
            I32 m_objectId;
			Event::EventManager & m_eventManager;
		};
	}
}

#endif
