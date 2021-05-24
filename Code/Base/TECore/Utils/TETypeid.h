#ifndef TETYPEID_H
#define TETYPEID_H

#include "TEDataTypes.h"

namespace TE {
    namespace {
        class TypeIdGeneratorBase {
          public:
            enum { ALTTYPEID_INVALID = 0xFFffFFff };

          protected:
            static unsigned GenerateAltTypeId() {
                static unsigned s_NextClassID = 0;
                return s_NextClassID++;
            }

            TypeIdGeneratorBase() {}
        };
    }

    typedef U32 TETypeId;

    template <typename T> class TypeIdGenerator : public TypeIdGeneratorBase {
      public:
        static unsigned GetTypeId() {
            static unsigned s_ClassId = GenerateAltTypeId();
            return s_ClassId;
        }

      private:
        TypeIdGenerator() {}
    };
}

#endif
