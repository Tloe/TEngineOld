#include "TEValue.h"
#include "TEVector3D.h"
#include <TEQuaternion.h>

TE::Core::Value::Value(Enum valueType) : m_valueType(valueType), m_readIndex(0) {}

void TE::Core::Value::AddString(const std::string &str) {
    m_variants.emplace_back(Core::Variant(str));
}

void TE::Core::Value::AddString(const char *str) { m_variants.emplace_back(Core::Variant(str)); }

void TE::Core::Value::AddI32(I32 i32) { m_variants.emplace_back(Core::Variant(i32)); }

void TE::Core::Value::AddU32(U32 u32) { m_variants.emplace_back(Core::Variant(u32)); }

void TE::Core::Value::AddBool(bool boolean) { m_variants.emplace_back(Core::Variant(boolean)); }

void TE::Core::Value::AddF32(F32 f32) { m_variants.emplace_back(Core::Variant(f32)); }

Enum TE::Core::Value::GetValueType() { return m_valueType; }

const char *TE::Core::Value::GetCString() {
    assert(m_readIndex < m_variants.size());

    return m_variants[m_readIndex++].GetCString();
}

std::string TE::Core::Value::GetString() {
    assert(m_readIndex < m_variants.size());

    return m_variants[m_readIndex++].GetString();
}

I32 TE::Core::Value::GetI32() {
    assert(m_readIndex < m_variants.size());

    return m_variants[m_readIndex++].GetI32();
}

U32 TE::Core::Value::GetU32() {
    assert(m_readIndex < m_variants.size());

    return m_variants[m_readIndex++].GetU32();
}

bool TE::Core::Value::GetBool() {
    assert(m_readIndex < m_variants.size());

    return m_variants[m_readIndex++].GetBool();
}

F32 TE::Core::Value::GetF32() {
    assert(m_readIndex < m_variants.size());

    return m_variants[m_readIndex++].GetF32();
}

void TE::Core::Value::Reset(Enum valueType) {
    m_valueType = valueType;
    m_variants.clear();
    m_readIndex = 0;
}

TE::Math::Vector3D<F32> TE::Core::GetVector(Value &value) {
    TE::Math::Vector3D<F32> vec;

    vec.x = value.GetF32();
    vec.y = value.GetF32();
    vec.z = value.GetF32();

    return vec;
}

void TE::Core::AddVector(const TE::Math::Vector3D<F32> &vec, Value &value) {
    value.AddF32(vec.x);
    value.AddF32(vec.y);
    value.AddF32(vec.z);
}

TE::Math::Quaternion<F32> TE::Core::GetQuaternion(Value &value) {
    TE::Math::Quaternion<F32> quat;

    quat.x = value.GetF32();
    quat.y = value.GetF32();
    quat.z = value.GetF32();
    quat.w = value.GetF32();

    return quat;
}

void TE::Core::AddQuaternion(const TE::Math::Quaternion<F32> &quat, Value &value) {
    value.AddF32(quat.x);
    value.AddF32(quat.y);
    value.AddF32(quat.z);
    value.AddF32(quat.w);
}
