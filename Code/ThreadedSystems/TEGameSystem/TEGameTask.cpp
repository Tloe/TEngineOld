#include "TEGameTask.h"
#include "TEGameScene.h"

#include <iostream>

TE::Game::GameTask::GameTask(GameScene &gameScene) : m_gameScene(gameScene) {}

void TE::Game::GameTask::Run() { m_gameScene.Update(); }

Bitmask TE::Game::GameTask::GetTaskFlags() { return Engine::TaskFlags::NotSet; }

void TE::Game::GameTask::SetInterpolation(F32 interpolation) {}

void TE::Game::GameTask::SetDeltaValues(U64 t, U64 dt) {}
