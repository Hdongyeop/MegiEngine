#include "MegiPlayScene.h"

#include "MegiPlayer.h"
#include "MegiSpriteRenderer.h"
#include "MegiTransform.h"

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
			Player* pl = new Player();

			Transform* tr = pl->AddComponent<Transform>();
			tr->SetPos(300 , 450);
			tr->SetName(L"TR");

			SpriteRenderer* sr = pl->AddComponent<SpriteRenderer>();
			sr->SetName(L"SR");

			AddGameObject(pl);
		}

		{
			Player* pl = new Player();

			Transform* tr = pl->AddComponent<Transform>();
			tr->SetPos(100 , 650);
			tr->SetName(L"TR");

			SpriteRenderer* sr = pl->AddComponent<SpriteRenderer>();
			sr->SetName(L"SR");

			AddGameObject(pl);
		}
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}
