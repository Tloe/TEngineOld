#include <TEGameStateHandler.h>
#include <assert.h>
#include <TEGameState.h>

TE::Engine::GameStateHandler::GameStateHandler( )
{
	RegisterEventCallback(*this, &Engine::GameStateHandler::OnGameStateChangeEvent);
}

TE::Engine::GameStateHandler::~GameStateHandler()
{
	UnRegisterEventCallback(&Engine::GameStateHandler::OnGameStateChangeEvent);
}

void TE::Engine::GameStateHandler::OnGameStateChangeEvent( GameStateChangeEvent& changeEvent )
{
	assert(!m_savedGameStateChangeEvent);
	m_savedGameStateChangeEvent = new0 GameStateChangeEvent(changeEvent);
}

void TE::Engine::GameStateHandler::SetInitState( GameStatePtr& gameState )
{
	assert(m_gameStates.empty() && "This should only be called at startup");
	I32 initStateId = AddGameState(gameState);
	TE::Engine::GameStateChangeEvent initialStateChange(TE::Engine::tekChangeAction_Push, initStateId);
	initialStateChange.Invoke();
}

I32 TE::Engine::GameStateHandler::AddGameState( GameStatePtr& gameState )
{
	static I32 stateId = 1;
	m_gameStates[stateId] = gameState;
	return stateId++;
}

void TE::Engine::GameStateHandler::RemoveGameState( I32 stateId )
{
	m_gameStates.erase(stateId);
}

void TE::Engine::GameStateHandler::DoGameStateChangeAction( EngineRoot& engine, I32 changeAction, I32 stateId )
{
	switch(changeAction)
	{
	case tekChangeAction_Push:
		PushGameState(engine, stateId);
		break;
	case tekChangeAction_Pop:
		PopGameState(engine);
		break;
	case tekChangeAction_Replace:
		PopGameState(engine);
		PushGameState(engine, stateId);
		break;
	default:
		assert(false && "Change action unknown!");
		break;
	}
}

void TE::Engine::GameStateHandler::PushGameState( EngineRoot& engine, I32 stateId )
{
	if (m_gameStateStack.size() > 0)
		m_gameStates[m_gameStateStack.top()]->Cleanup(engine);

	m_gameStateStack.push(stateId);
	m_gameStates[m_gameStateStack.top()]->Init(engine);
}

void TE::Engine::GameStateHandler::PopGameState(EngineRoot& engine)
{
	if (m_gameStateStack.size() > 0)
	{
		m_gameStates[m_gameStateStack.top()]->Cleanup(engine);
		m_gameStateStack.pop();
	}
}

void TE::Engine::GameStateHandler::Update(EngineRoot& engine, Real dt)
{
	if (m_savedGameStateChangeEvent)
	{
		DoGameStateChangeAction(engine, m_savedGameStateChangeEvent->GetChangeAction(), m_savedGameStateChangeEvent->GetStateId());
		m_savedGameStateChangeEvent = NULL;
	}

	m_gameStates[m_gameStateStack.top()]->Update(engine, dt);
}

void TE::Engine::GameStateHandler::Draw(EngineRoot& engine, Real dt)
{
	m_gameStates[m_gameStateStack.top()]->Draw(engine, dt);
}
