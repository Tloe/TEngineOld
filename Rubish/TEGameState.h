#ifndef TEGAMESTATE_H
#define TEGAMESTATE_H

#include <TEDataTypes.h>
#include "TEEngine.h"

namespace TE
{
	//Forward declarations
	namespace Render { class Renderer; typedef Memory::Pointer0<Renderer> RendererPtr; }
	//End forward declarations

	namespace Engine
	{
		class GameState
		{
		public:
			GameState()
			{}
		
			virtual ~GameState(){};

			virtual void Init(EngineRoot& engine)
			{};

			virtual void Cleanup(EngineRoot& engine)
			{};

			virtual void Update(EngineRoot& engine, Real dt)
			{};

			virtual void Draw(EngineRoot& engine, Real dt)
			{};
		};

		typedef Memory::Pointer0<GameState> GameStatePtr;
	}
}

#endif