#ifndef TEVALUE_H
#define TEVALUE_H

#include "TEVariant.h"

namespace TE::Math {
    template <typename T> class Vector3D;
    template <typename T> class Quaternion;
}

namespace TE::Core {
    class Value {
      public:
        Value(Enum valueType);

        void AddString(const std::string &str);
        void AddString(const char *str);
        void AddI32(I32 i32);
        void AddU32(U32 u32);
        void AddBool(bool boolean);
        void AddF32(F32 f32);

        Enum GetValueType();
        const char *GetCString();
        std::string GetString();
        I32 GetI32();
        U32 GetU32();
        bool GetBool();
        F32 GetF32();

        void Reset(Enum valueType);

      private:
        typedef std::vector<TE::Core::Variant> VariantVec;

        Enum m_valueType;
        VariantVec m_variants;
        U32 m_readIndex;
    };

    TE::Math::Vector3D<F32> GetVector(Value &value);
    void AddVector(const TE::Math::Vector3D<F32> &vec, Value &value);
    TE::Math::Quaternion<F32> GetQuaternion(Value &value);
    void AddQuaternion(const TE::Math::Quaternion<F32> &quat, Value &value);
}

#endif
