#ifndef TESUBJECT_H
#define TESUBJECT_H

#include "TEDataTypes.h"

#include <memory>
#include <mutex>
#include <vector>

namespace TE
{
	namespace Engine { class Observer; }
	namespace Engine { struct ChangeInterfacePtrs; }
	namespace Engine { class SubjectVisitor; }

	namespace Engine
	{
		class Subject
		{
		public:
            enum class Priority
            {
                Level0,
                Level1,
                Level2,
                Level3,
                Level4
            };

            struct ObserverSubscription
            {
                Observer* observer;
                Bitmask64 subscribeBits;
            };

            typedef std::vector<ObserverSubscription> ObserverSubscriptionVec;

			virtual void AcceptSubjectVisitor(SubjectVisitor & subjectVisitor);
			void PostSubjectChanges(Bitmask64 changeBits);
			virtual void AttachObserver(Observer& observer, Bitmask64 changeBits);
			virtual void DetachObserver(Observer& observer);
            virtual Priority GetPriority() const;
            virtual I32 GetObjectId() const;

            virtual std::string GetME(){ return "";}

		private:
            std::mutex m_mutex;
            ObserverSubscriptionVec m_observerSubscriptions;
            I32 m_objectId;
		};

		typedef std::unique_ptr<Subject> SubjectUPtr;
	}
}

#endif
