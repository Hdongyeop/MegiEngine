#pragma once
#include "MegiLoadingScene.h"
#include "MegiPlayScene.h"
#include "MegiTitleScene.h"
#include "MegiToolScene.h"
#include "../MegiEngine_SOURCE/MegiSceneManager.h"

namespace MegiEngine
{
	void LoadScene()
	{
		SceneManager::CreateScene<LoadingScene>(L"LoadingScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<ToolScene>(L"ToolScene");

		SceneManager::LoadScene(L"LoadingScene");
	}
}
