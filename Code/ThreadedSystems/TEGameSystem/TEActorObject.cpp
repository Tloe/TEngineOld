#include "TEActorObject.h"

TE::Game::ActorObject::ActorObject(I32 objectId)
    : m_objectId(objectId)
{

}

void TE::Game::ActorObject::SetValue(TE::Core::Value &value)
{

}

void TE::Game::ActorObject::Initialize()
{

}

void TE::Game::ActorObject::Cleanup()
{

}

Bitmask64 TE::Game::ActorObject::GetDesiredSystemChanges()
{
    return Engine::Change::NotSet;
}

Bitmask64 TE::Game::ActorObject::GetPotentialSystemChanges()
{
    return Engine::Change::NotSet;
}

void TE::Game::ActorObject::OnSubjectChange(Engine::Subject *subject, Bitmask64 changeBits)
{

}

I32 TE::Game::ActorObject::GetObjectId() const
{
    return m_objectId;
}
