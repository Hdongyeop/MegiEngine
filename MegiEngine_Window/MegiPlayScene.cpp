#include "MegiPlayScene.h"

#include "MegCircleCollider2D.h"
#include "MegiAnimator.h"
#include "MegiApplication.h"
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
#include "MegiTile.h"
#include "MegiTilemapRenderer.h"

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
		const wchar_t* tilemapName = L"..\\Resources\\kuku";
		LoadTileMap(tilemapName);

		// Main Camera GameObject
		{
			GameObject* mainCamera = 
				Object::Instantiate<GameObject>(LayerType::None
					, Vector2(358.0f , 469.5f));
			Camera* cameraComponent = mainCamera->AddComponent<Camera>();
			MainCamera = cameraComponent;
		}

		// Background GameObject

//		{
//			GameObject* background =
//				Instantiate<GameObject>(LayerType::Background);
//
//			SpriteRenderer* sr = background->AddComponent<SpriteRenderer>();
//			auto bg = Resources::Find<graphics::Texture>(L"Background");
//			sr->SetTexture(bg);
//
//			AddGameObject(background , LayerType::Background);
//		}

		// Player GameObject

		{
			Player* player = Object::Instantiate<Player>(LayerType::Player , Vector2(0, 0));
			Transform* tr = player->GetComponent<Transform>();
			tr->SetName(L"Transform");
			Animator* animator = player->AddComponent<Animator>();
			animator->SetName(L"Animator");
			PlayerController* pc = player->AddComponent < PlayerController >();
			pc->SetName(L"PlayerController");
			CircleCollider2D* collider = player->AddComponent<CircleCollider2D>();
			collider->SetOffset(Vector2(-50.0f , -50.0f));
			collider->SetSize(Vector2(100.0f , 100.0f));

			auto playerTexture = Resources::Find<graphics::Texture>(L"Player");
			animator->CreateAnimation(
			L"DownWalk" 
			, playerTexture
			, Vector2(0 * 250.0f , 3 * 250.0f)
			, Vector2(250.0f , 250.0f)
			, Vector2::Zero
			, 7
			, 0.2f);

			animator->CreateAnimation(
			L"RightWalk"
			, playerTexture
			, Vector2(0 * 250.0f , 0 * 250.0f)
			, Vector2(250.0f , 250.0f)
			, Vector2::Zero
			, 6
			, 0.2f);

			animator->CreateAnimation(
			L"UpWalk"
			, playerTexture
			, Vector2(0 * 250.0f, 2 * 250.0f)
			, Vector2(250.0f, 250.0f)
			, Vector2::Zero
			, 8
			, 0.2f);

			animator->CreateAnimation(
			L"LeftWalk"
			, playerTexture
			, Vector2(0 * 250.0f, 1 * 250.0f)
			, Vector2(250.0f, 250.0f)
			, Vector2::Zero
			, 6
			, 0.2f);

			animator->CreateAnimation(
			L"Idle"
			, playerTexture
			, Vector2(0 * 250.0f, 3 * 250.0f)
			, Vector2(250.0f, 250.0f)
			, Vector2::Zero
			, 1
			, 1.0f);

			animator->CreateAnimation(
			L"FrontGiveWater"
			, playerTexture
			, Vector2(0 * 250.0f , 4 * 250.0f)
			, Vector2(250.0f , 250.0f)
			, Vector2::Zero
			, 12
			, 0.1f);
			animator->GetCompleteEvent(L"FrontGiveWater")
				= [pc]() {pc->AttackEffect(); };

			animator->PlayAnimation(L"Idle" , false);

			// Object::DontDestroyOnLoad(player);
		}

		// Cat(AI)

//		{
//			Cat* cat = Instantiate<Cat>(LayerType::Animal, Vector2(200 , 200));
//			Transform* tr = cat->GetComponent<Transform>();
//			tr->SetName(L"Transform");
//			tr->SetScale(Vector2(5.0f , 5.0f));
//			Animator* animator = cat->AddComponent<Animator>();
//			animator->SetName(L"Animator");
//			CatController* catController = cat->AddComponent<CatController>();
//			catController->SetName(L"CatController");
//			
//			auto catTexture = Resources::Find<graphics::Texture>(L"Cat");
//			animator->CreateAnimation(
//			L"DownWalk" 
//			, catTexture
//			, Vector2(0.0f , 0.0f)
//			, Vector2(32.0f , 32.0f)
//			, Vector2::Zero
//			, 4
//			, 0.2f);
//
//			animator->CreateAnimation(
//			L"RightWalk"
//			, catTexture
//			, Vector2(0.0f , 32.0f)
//			, Vector2(32.0f , 32.0f)
//			, Vector2::Zero
//			, 4
//			, 0.2f);
//
//			animator->CreateAnimation(
//			L"UpWalk"
//			, catTexture
//			, Vector2(0.0f , 64.0f)
//			, Vector2(32.0f , 32.0f)
//			, Vector2::Zero
//			, 4
//			, 0.2f);
//
//			animator->CreateAnimation(
//			L"LeftWalk"
//			, catTexture
//			, Vector2(0.0f , 96.0f)
//			, Vector2(32.0f , 32.0f)
//			, Vector2::Zero
//			, 4
//			, 0.2f);
//
//			animator->CreateAnimation(
//			L"SitDown"
//			, catTexture
//			, Vector2(0.0f , 128.0f)
//			, Vector2(32.0f , 32.0f)
//			, Vector2::Zero
//			, 4
//			, 0.2f);
//
//			animator->CreateAnimation(
//			L"LayDown"
//			, catTexture
//			, Vector2(0.0f , 192.0f)
//			, Vector2(32.0f , 32.0f)
//			, Vector2::Zero
//			, 4
//			, 0.2f);
//
//			animator->PlayAnimation(L"SitDown" , false);
//
//			AddGameObject(cat , LayerType::Animal);
//		}

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
//			Transform* tr =black ->GetComponent<Transform>();
//			tr->SetName(L"Transform");
//
//			auto blackTexture = Resources::Find<graphics::Texture>(L"Black");
//
//			Animator* animator = black->AddComponent<Animator>();
//			animator->CreateAnimation(
//			L"Idle"
//			, blackTexture
//			, Vector2(0.0f , 0.0f)
//			, Vector2(100.0f , 100.0f)
//			, Vector2::Zero
//			, 1
//			, 1.0f);
//
//			animator->PlayAnimation(L"Idle" , false);
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

		// Mushroom

		{
			GameObject* mushroom = Object::Instantiate<GameObject>(LayerType::Animal, Vector2(300, 300));
			Animator* animator = mushroom->AddComponent<Animator>();
			BoxCollider2D* collider = mushroom->AddComponent<BoxCollider2D>();
			collider->SetOffset(Vector2(-50.0f , -50.0f));
			collider->SetSize(Vector2(100.0f , 100.0f));

			animator->CreateAnimationByFolder(
			L"MushroomIdle"
			, L"..\\Resources\\Mushroom"
			, Vector2::Zero
			, 0.2f);

			animator->PlayAnimation(L"MushroomIdle" , true);
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

		CollisionManager::CollisionLayerCheck(LayerType::Player , LayerType::Animal, true);
	}

	void PlayScene::OnExit()
	{
		Scene::OnExit();
	}

	void PlayScene::LoadTileMap(const wchar_t* fileName)
	{
		FILE* pFile = nullptr;
		_wfopen_s(&pFile , fileName , L"rb");

		while ( true )
		{
			int idxX = 0;
			int idxY = 0;

			int posX = 0;
			int posY = 0;


			if ( fread(&idxX , sizeof(int) , 1 , pFile) == NULL )
				break;
			if ( fread(&idxY , sizeof(int) , 1 , pFile) == NULL )
				break;
			if ( fread(&posX , sizeof(int) , 1 , pFile) == NULL )
				break;
			if ( fread(&posY , sizeof(int) , 1 , pFile) == NULL )
				break;

			Tile* tile = Object::Instantiate<Tile>(LayerType::Tile , Vector2(posX , posY));
			TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
			tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));
			tmr->SetIndex(Vector2(idxX , idxY));

			//mTiles.push_back(tile);
		}

		fclose(pFile);
	}
}
