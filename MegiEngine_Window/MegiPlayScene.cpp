#include "MegiPlayScene.h"

#include "MegiAnimator.h"
#include "MegiApplication.h"
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

extern MegiEngine::Application application;

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
		// Main Camera GameObject
		{
			GameObject* mainCamera = 
				Instantiate<GameObject>(LayerType::None
					, Vector2((float)application.GetWidth() / 2, (float)application.GetHeight() / 2));
			Camera* cameraComponent = mainCamera->AddComponent<Camera>();
			MainCamera = cameraComponent;

			AddGameObject(mainCamera, LayerType::None);
		}

		// Background GameObject
		{
			GameObject* background =
				Instantiate<GameObject>(LayerType::Background);

			SpriteRenderer* sr = background->AddComponent<SpriteRenderer>();
			auto bg = Resources::Find<graphics::Texture>(L"Background");
			sr->SetTexture(bg);

			AddGameObject(background , LayerType::Background);
		}

		// Cat(Player) GameObject
		{
			Player* cat = Instantiate<Player>(LayerType::Player , Vector2(100 , 100));
			Transform* tr = cat->GetComponent<Transform>();
			tr->SetName(L"Transform");
			tr->SetScale(Vector2(5.0f , 5.0f));
			Animator* animator = cat->AddComponent<Animator>();
			animator->SetName(L"Animator");
			PlayerController* pc = cat->AddComponent < PlayerController >();
			pc->SetName(L"PlayerController");

			auto catTexture = Resources::Find<graphics::Texture>(L"Cat");
			animator->CreateAnimation(
			L"DownWalk" 
			, catTexture
			, Vector2(0.0f , 0.0f)
			, Vector2(32.0f , 32.0f)
			, Vector2::Zero
			, 4
			, 0.2f);

			animator->CreateAnimation(
			L"RightWalk"
			, catTexture
			, Vector2(0.0f , 32.0f)
			, Vector2(32.0f , 32.0f)
			, Vector2::Zero
			, 4
			, 0.2f);

			animator->CreateAnimation(
			L"UpWalk"
			, catTexture
			, Vector2(0.0f , 64.0f)
			, Vector2(32.0f , 32.0f)
			, Vector2::Zero
			, 4
			, 0.2f);

			animator->CreateAnimation(
			L"LeftWalk"
			, catTexture
			, Vector2(0.0f , 96.0f)
			, Vector2(32.0f , 32.0f)
			, Vector2::Zero
			, 4
			, 0.2f);

			animator->CreateAnimation(
			L"SitDown"
			, catTexture
			, Vector2(0.0f , 128.0f)
			, Vector2(32.0f , 32.0f)
			, Vector2::Zero
			, 4
			, 0.2f);

			animator->PlayAnimation(L"SitDown" , false);

			AddGameObject(cat , LayerType::Player);
		}

		// Cat(AI)
		{
			Cat* cat = Instantiate<Cat>(LayerType::Animal, Vector2(200 , 200));
			Transform* tr = cat->GetComponent<Transform>();
			tr->SetName(L"Transform");
			tr->SetScale(Vector2(5.0f , 5.0f));
			Animator* animator = cat->AddComponent<Animator>();
			animator->SetName(L"Animator");
			CatController* catController = cat->AddComponent<CatController>();
			catController->SetName(L"CatController");
			
			auto catTexture = Resources::Find<graphics::Texture>(L"Cat");
			animator->CreateAnimation(
			L"DownWalk" 
			, catTexture
			, Vector2(0.0f , 0.0f)
			, Vector2(32.0f , 32.0f)
			, Vector2::Zero
			, 4
			, 0.2f);

			animator->CreateAnimation(
			L"RightWalk"
			, catTexture
			, Vector2(0.0f , 32.0f)
			, Vector2(32.0f , 32.0f)
			, Vector2::Zero
			, 4
			, 0.2f);

			animator->CreateAnimation(
			L"UpWalk"
			, catTexture
			, Vector2(0.0f , 64.0f)
			, Vector2(32.0f , 32.0f)
			, Vector2::Zero
			, 4
			, 0.2f);

			animator->CreateAnimation(
			L"LeftWalk"
			, catTexture
			, Vector2(0.0f , 96.0f)
			, Vector2(32.0f , 32.0f)
			, Vector2::Zero
			, 4
			, 0.2f);

			animator->CreateAnimation(
			L"SitDown"
			, catTexture
			, Vector2(0.0f , 128.0f)
			, Vector2(32.0f , 32.0f)
			, Vector2::Zero
			, 4
			, 0.2f);

			animator->CreateAnimation(
			L"LayDown"
			, catTexture
			, Vector2(0.0f , 192.0f)
			, Vector2(32.0f , 32.0f)
			, Vector2::Zero
			, 4
			, 0.2f);

			animator->PlayAnimation(L"SitDown" , false);

			AddGameObject(cat , LayerType::Animal);
		}

		// Bubble

//		{
//			GameObject* bubble = Instantiate<GameObject>(LayerType::Particle, Vector2(100, 100));
//
//			Transform* tr = bubble->GetComponent<Transform>();
//			tr->SetScale(Vector2(0.5f, 0.5f));
//
//			auto bubbleTexture = Resources::Find<graphics::Texture>(L"Bubble");
//			SpriteRenderer* sr = bubble->AddComponent<SpriteRenderer>();
//			sr->SetTexture(bubbleTexture);
//
//			AddGameObject(bubble , LayerType::Particle);
//		}

		// Black

//		{
//			GameObject* black = Instantiate<GameObject>(LayerType::Particle, Vector2(0,0));
//
//			Transform* tr =black ->GetComponent<Transform>();
//
//			auto blackTexture = Resources::Find<graphics::Texture>(L"Black");
//			SpriteRenderer* sr =black ->AddComponent<SpriteRenderer>();
//			sr->SetTexture(blackTexture);
//
//			AddGameObject(black , LayerType::Particle);
//		}

		// Hit Effect

//		{
//			GameObject* hitEffect = Instantiate<GameObject>(LayerType::Player , Vector2(0 , 0));
//			Animator* animator = hitEffect->AddComponent<Animator>();
//
//			auto hitTexture = Resources::Find<graphics::Texture>(L"HitEffect");
//			animator->CreateAnimation(
//			L"HitEffect" 
//			, hitTexture
//			, Vector2(0.0f , 0.0f)
//			, Vector2(512.0f , 512.0f)
//			, Vector2::Zero
//			, 15
//			, 0.05f
//			, Vector2(0.3f, 0.3f));
//
//			animator->PlayAnimation(L"HitEffect");
//
//			AddGameObject(hitEffect , LayerType::Player);
//		}

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

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t str[ 50 ] = L"Play Scene";
		int len = wcsnlen_s(str , 50);
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
