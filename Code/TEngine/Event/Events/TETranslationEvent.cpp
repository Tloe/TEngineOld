#include "TETranslationEvent.h"
#include "TEEventHandler.h"

TE::Event::TranslationEvent::TranslationEvent(TE::Math::Vector3D<F32> &translation)
    : m_translation(translation)
{

}

void TE::Event::TranslationEvent::VisitEventHandler( EventHandler & eventHandler )
{
	eventHandler.HandleEvent(*this);
}

const TE::Math::Vector3D<F32> &TE::Event::TranslationEvent::GetTranslation()
{
    return m_translation;
}
