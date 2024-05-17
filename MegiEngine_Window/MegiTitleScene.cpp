#include "MegiTitleScene.h"

#include "MegiInput.h"
#include "MegiSceneManager.h"

namespace MegiEngine
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();
	}

	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();

		if(Input::GetKeyDown(KeyCode::N))
		{
			SceneManager::LoadScene(L"PlayScene");
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t str[ 50 ] = L"Title Scene";
		int len = wcsnlen_s(str, 50);
		TextOut(hdc , 0 , 0 , str , len);
	}
}
