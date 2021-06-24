#include "Demo1/Demo1State.h"
#include "Demo1/Player.h"
#include "Game.h"
#include "AssetManager.h"
#include "GameStateManager.h"
#include "raylib.h"

using namespace Demo1;

Demo1State::Demo1State(Game* app) : IGameState(app)
{
	m_player = new Player();
	m_player->SetPosition({ m_app->GetWindowWidth() * 0.25f,  m_app->GetWindowHeight() / 2.0f });
}

Demo1State::~Demo1State()
{
	delete m_player;
	m_player = nullptr;
}

void Demo1State::Update(float deltaTime)
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		m_app->GSM()->PopState();
		m_app->GSM()->PushState("Menu");
	}

	m_player->Update(deltaTime);
}

void Demo1State::Draw()
{
	DrawTextEx(AssetManager::GetInstance()->fntDeltaGothicOne, "Demo 1", { 10, 10 }, 48, 0, GRAY);
	m_player->Draw();
}

