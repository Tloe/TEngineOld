#ifndef TESPAWNEROBJECT_H
#define TESPAWNEROBJECT_H

#include <TESystemObject.h>

namespace TE {
namespace Game {
    class SpawnerObject : public Engine::SystemObject {
      public:
        SpawnerObject(I32 objectId);

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
