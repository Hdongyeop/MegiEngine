#pragma once
#include "MegiPlayScene.h"
#include "../MegiEngine_SOURCE/MegiSceneManager.h"

namespace MegiEngine
{
	void LoadScene()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::LoadScene(L"PlayScene");
	}
}
