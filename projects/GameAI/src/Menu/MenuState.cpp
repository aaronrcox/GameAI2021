#include "Menu/MenuState.h"
#include "Demo1/Demo1State.h"
#include "Demo2/Demo2State.h"
#include "Game.h"
#include "AssetManager.h"
#include "GameStateManager.h"
#include "raylib.h"

using namespace Menu;

MenuState::MenuState(Game* app) : IGameState(app)
{
}

MenuState::~MenuState()
{
}

void MenuState::Update(float deltaTime)
{
	if (IsKeyPressed('1'))
	{
		m_app->GSM()->SetState("Demo1", new Demo1::Demo1State(m_app));
		m_app->GSM()->PopState();
		m_app->GSM()->PushState("Demo1");
	}
	if (IsKeyPressed('2'))
	{
		m_app->GSM()->SetState("Demo2", new Demo2::Demo2State(m_app));
		m_app->GSM()->PopState();
		m_app->GSM()->PushState("Demo2");
	}
}

void MenuState::Draw()
{
	DrawTextEx(AssetManager::GetInstance()->fntDeltaGothicOne, "Menu", { 10, 10 }, 48, 0, GRAY);
			
	DrawTextEx(AssetManager::GetInstance()->fntDeltaGothicOne, "1. Demo 1", { 10, 68 }, 32, 0, GRAY);
	DrawTextEx(AssetManager::GetInstance()->fntDeltaGothicOne, "2. Demo 2", { 10, 100 }, 32, 0, GRAY);
}

