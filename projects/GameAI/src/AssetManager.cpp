
#include "AssetManager.h"

// Singleton Methods
// ---------------------------------------------------------
AssetManager* AssetManager::ms_singleton = nullptr;

AssetManager* AssetManager::GetInstance()
{
	return ms_singleton;
}
void AssetManager::CreateSingleton()
{
	ms_singleton = new AssetManager();
}
void AssetManager::DestroySingleton()
{
	delete ms_singleton;
	ms_singleton = nullptr;
}
// ---------------------------------------------------------


AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{

}

void AssetManager::LoadAssets()
{
	fntDeltaGothicOne = LoadFontEx("./assets/fonts/DelaGothicOne-Regular.ttf", 48, 0, 250);
}

void AssetManager::UnloadAssets()
{
	UnloadFont(fntDeltaGothicOne);
}

