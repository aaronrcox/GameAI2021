#pragma once

class GameStateManager;

class Game
{
public:
	const int windowWidth = 800;
	const int windowHeight = 450;
	const char* windowTitle = "Hello Raylib";
	bool shouldQuit = false;

	GameStateManager* m_gsm = nullptr;

public:

	Game();
	~Game();

	void Load();
	void UnLoad();

	void Update();
	void Draw();

	GameStateManager* GSM();

	int GetWindowWidth();
	int GetWindowHeight();

protected:
private:
};