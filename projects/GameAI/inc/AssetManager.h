#pragma once

#include "raylib.h"

#define ASSETS AssetManager::GetInstance()


class AssetManager
{
public:

	static AssetManager* GetInstance();
	static void CreateSingleton();
	static void DestroySingleton();

	void LoadAssets();
	void UnloadAssets();

	// FONTS
	// ---------------------------------

	Font fntDeltaGothicOne;

	// IMAGES
	// ---------------------------------


	// SOUNDS
	// ---------------------------------

protected:
private:

	static AssetManager* ms_singleton;

	AssetManager();
	~AssetManager();
};