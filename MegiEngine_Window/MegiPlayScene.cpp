#include "MegiPlayScene.h"

#include "MegCircleCollider2D.h"
#include "MegiAnimator.h"
#include "MegiApplication.h"
#include "MegiAudioListener.h"
#include "MegiAudioSource.h"
#include "MegiBoxCollider2D.h"
#include "MegiInput.h"
#include "MegiObject.h"
#include "MegiPlayer.h"
#include "MegiPlayerController.h"
#include "MegiResources.h"
#include "MegiSceneManager.h"
#include "MegiSpriteRenderer.h"
#include "MegiRenderer.h"
#include "MegiCat.h"
#include "MegiCatController.h"
#include "MegiCollisionManager.h"
#include "MegiFloor.h"
#include "MegiFloorScript.h"
#include "MegiRigidbody.h"
#include "MegiTile.h"
#include "MegiTilemapRenderer.h"
#include "MegiUIManager.h"

extern MegiEngine::Application application;

namespace MegiEngine
{
	PlayScene::PlayScene()
	: mPlayer(nullptr)
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		mPlayer = Object::Instantiate<Player>(LayerType::Player);
		Object::DontDestroyOnLoad(mPlayer);

		Scene::Initialize();
	}

	void PlayScene::Update()
	{

		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
		if ( Input::GetKeyDown(KeyCode::N) )
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
		Scene::OnEnter();

//		CollisionManager::CollisionLayerCheck(LayerType::Player , LayerType::Animal, true);
//		CollisionManager::CollisionLayerCheck(LayerType::Player , LayerType::Floor, true);

		//UIManager::Push(UIType::Button);
	}

	void PlayScene::OnExit()
	{
		//UIManager::Pop(UIType::Button);

		Scene::OnExit();
	}
}
