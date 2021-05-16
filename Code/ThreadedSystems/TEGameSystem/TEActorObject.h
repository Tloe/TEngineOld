#ifndef TEACTOROBJECT_H
#define TEACTOROBJECT_H

#include <TESystemObject.h>

namespace TE {
namespace Game {
    class ActorObject : public Engine::SystemObject {
      public:
        ActorObject(I32 objectId);

        virtual void SetValue(Core::Value &value);
        virtual void Initialize();
        virtual void Cleanup();
        virtual Bitmask64 GetDesiredSystemChanges();
        virtual Bitmask64 GetPotentialSystemChanges();
        virtual void OnSubjectChange(Engine::Subject *subject, Bitmask64 changeBits);
        virtual I32 GetObjectId() const;

      private:
        I32 m_objectId;
    };
}
}

#endif
