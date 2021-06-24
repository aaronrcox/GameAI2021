#include "Game.h"

#include "AssetManager.h"
#include "GameStateManager.h"
#include "Menu/MenuState.h"

#include "raylib.h"
#include "Math/Vec2.h"

#include "raylib.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Load()
{
	AssetManager::CreateSingleton();
	AssetManager::GetInstance()->LoadAssets();

	m_gsm = new GameStateManager();
	m_gsm->SetState("Menu", new Menu::MenuState(this));

	m_gsm->PushState("Menu");
}

void Game::UnLoad()
{
	delete m_gsm;
	m_gsm = nullptr;

	AssetManager::GetInstance()->UnloadAssets();
	AssetManager::DestroySingleton();
}

void Game::Update()
{
	m_gsm->UpdateGameStates(GetFrameTime());
}

void Game::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	m_gsm->DrawGameStates();

	EndDrawing();
}

GameStateManager* Game::GSM()
{
	return m_gsm;
}

int Game::GetWindowWidth()
{
	return windowWidth;
}
int Game::GetWindowHeight()
{
	return windowHeight;
}