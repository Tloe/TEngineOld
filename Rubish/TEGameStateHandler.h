#ifndef TEGAMESTATEHANDLER_H
#define TEGAMESTATEHANDLER_H

#include <TEGameStateChangeEvent.h>
#include <TEEventHandler.h>
#include <TEDataTypes.h>
#include <stack>
#include <unordered_map>
#include "TESmartPointers.h"

namespace TE
{
	//Forward declarations
	namespace Engine{ class EngineRoot; }
	namespace Engine{ class GameState; typedef Memory::Pointer0<GameState> GameStatePtr; }
	//End forward declarations

	namespace Engine
	{
		class GameStateHandler : public Events::EventHandler
		{
		public:
			GameStateHandler();
			~GameStateHandler();

			void SetInitState(GameStatePtr& gameState);
			I32 AddGameState(GameStatePtr& gameState);
			void RemoveGameState(I32 stateId);
			void Update(EngineRoot& engine, Real dt);
			void Draw(EngineRoot& engine, Real dt);
		private:
			void OnGameStateChangeEvent(GameStateChangeEvent& changeEvent);
			void DoGameStateChangeAction( EngineRoot& engine, I32 changeAction, I32 stateId );
			void PushGameState( EngineRoot& engine, I32 stateId );
			void PopGameState(EngineRoot& engine);

			Memory::Pointer0<GameStateChangeEvent> m_savedGameStateChangeEvent;
			std::unordered_map<I32, GameStatePtr > m_gameStates;
			std::stack<I32> m_gameStateStack;
		};
	}
}

#endif
