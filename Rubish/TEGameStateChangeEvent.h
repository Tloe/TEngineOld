#ifndef TEGAMESTATECHANGEEVENT_H
#define TEGAMESTATECHANGEEVENT_H


#include <TEEvent.h>


namespace TE
{
	namespace Engine
	{
		enum
		{
			tekGameStateChangeEvent = 'gsch'
		};
		
		enum
		{
			tekChangeAction_Push,
			tekChangeAction_Pop,
			tekChangeAction_Replace
		};

		class GameStateChangeEvent : public Events::Event
		{
		public:
			GameStateChangeEvent(I32 changeAction, I32 stateId = -1)
				:
				Events::Event(tekGameStateChangeEvent),
				m_changeAction(changeAction),
				m_stateId(stateId)
			{}

			I32 GetChangeAction()
			{
				return m_changeAction;
			}

			I32 GetStateId()
			{
				return m_stateId;
			}
		private:
			I32			m_changeAction;
			I32			m_stateId;
		};
	}
}

#endif