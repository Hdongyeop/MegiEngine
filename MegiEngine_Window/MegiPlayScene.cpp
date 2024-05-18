#include "MegiPlayScene.h"

#include "MegiInput.h"
#include "MegiObject.h"
#include "MegiPlayer.h"
#include "MegiPlayerController.h"
#include "MegiResources.h"
#include "MegiSceneManager.h"
#include "MegiSpriteRenderer.h"

namespace MegiEngine
{
	PlayScene::PlayScene()
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		{
			GameObject* background = 
				Instantiate<GameObject>(LayerType::Background);

			SpriteRenderer* sr = background->AddComponent<SpriteRenderer>();
			auto bg = Resources::Find<graphics::Texture>(L"Background");
			sr->SetTexture(bg);

			AddGameObject(background, LayerType::Background);
		}

		{
			Player* player =
				Instantiate<Player>(LayerType::Player , Vector2(100 , 350));

			SpriteRenderer* sr =player ->AddComponent<SpriteRenderer>();
			auto playerTexture = Resources::Find<graphics::Texture>(L"Player");
			sr->SetTexture(playerTexture);

			PlayerController* pc =player ->AddComponent<PlayerController>();
			pc->SetName(L"PC");

			AddGameObject(player , LayerType::Player);
		}


		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
		if(Input::GetKeyDown(KeyCode::N))
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t str[ 50 ] = L"Play Scene";
		int len = wcsnlen_s(str, 50);
		TextOut(hdc , 0 , 0 , str , len);
	}

	void PlayScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void PlayScene::OnExit()
	{
		Scene::OnExit();
	}
}
