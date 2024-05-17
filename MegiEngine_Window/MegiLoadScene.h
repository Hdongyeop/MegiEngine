#pragma once
#include "MegiPlayScene.h"
#include "MegiTitleScene.h"
#include "../MegiEngine_SOURCE/MegiSceneManager.h"

namespace MegiEngine
{
	void LoadScene()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<TitleScene>(L"TitleScene");

		SceneManager::LoadScene(L"TitleScene");
	}
}
