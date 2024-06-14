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
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{

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

//		CollisionManager::CollisionLayerCheck(LayerType::Player , LayerType::Animal, true);
//		CollisionManager::CollisionLayerCheck(LayerType::Player , LayerType::Floor, true);

		//UIManager::Push(UIType::Button);
	}

	void PlayScene::OnExit()
	{
		//UIManager::Pop(UIType::Button);

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
