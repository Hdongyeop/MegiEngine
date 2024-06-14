#include "MegiLoadingScene.h"

#include "MegiResources.h"
#include "MegiTexture.h"
#include "MegiSceneManager.h"

namespace MegiEngine
{
	LoadingScene::LoadingScene()
	: loadComplete(false)
	{
	}

	LoadingScene::~LoadingScene()
	{
		delete mResourcesLoadThread;
		mResourcesLoadThread = nullptr;
	}

	void LoadingScene::Initialize()
	{
		mResourcesLoadThread = new std::thread(&LoadingScene::ResourcesLoad , this , std::ref(mMutex));
	}

	void LoadingScene::Update()
	{
		if(loadComplete)
		{
			// 만약 메인쓰레드가 종료되는데 자식 쓰레드가 남아 있다면
			// 자식 쓰레드를 메인쓰레드에 편입 시켜 메인쓰레드가 종료되기 전까지 block
			mResourcesLoadThread->join();

			// 메인 쓰레드와 완전 분리 시켜 독립적인 쓰레드 운영 가능
			// mResourcesLoadThread->detach();

			SceneManager::LoadScene(L"PlayScene");
		}
	}

	void LoadingScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void LoadingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void LoadingScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void LoadingScene::OnExit()
	{
		Scene::OnExit();
	}

	void LoadingScene::ResourcesLoad(std::mutex& m)
	{
		m.lock();
		{
			// BMP
			Resources::Load<graphics::Texture>(L"Cat" , L"..\\Resources\\Cat.bmp");
			Resources::Load<graphics::Texture>(L"SpringFloor" , L"..\\Resources\\SpringFloor.bmp");
			Resources::Load<graphics::Texture>(L"HPBAR" , L"..\\Resources\\HPBAR.bmp");
			Resources::Load<graphics::Texture>(L"PixelMap" , L"..\\Resources\\pixelMap.bmp");

			// PNG
			Resources::Load<graphics::Texture>(L"Background" , L"..\\Resources\\CloudOcean.png");
			Resources::Load<graphics::Texture>(L"Player" , L"..\\Resources\\Player.png");
			Resources::Load<graphics::Texture>(L"HitEffect" , L"..\\Resources\\HitEffect.png");
			Resources::Load<graphics::Texture>(L"Bubble" , L"..\\Resources\\Bubble.png");
			Resources::Load<graphics::Texture>(L"Black" , L"..\\Resources\\Black.png");
		}
		m.unlock();

		loadComplete = true;
	}
}
