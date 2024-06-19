#include "MegiLoadingScene.h"

#include "MegiApplication.h"
#include "MegiResources.h"
#include "MegiTexture.h"
#include "MegiSceneManager.h"

extern MegiEngine::Application application;

namespace MegiEngine
{
	LoadingScene::LoadingScene()
	: loadComplete(false)
	, mMutex()
	, mResourcesLoadThread()
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
	}

	void LoadingScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void LoadingScene::Render()
	{
		Scene::Render();

		int a = 0;

		if(loadComplete /* && application.IsLoaded() */ )
		{
			mResourcesLoadThread->join();

			SceneManager::LoadScene(L"PlayScene");
		}
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
		while (true)
		{
			if ( application.IsLoaded() == true )
				break;
		}

		m.lock();
		{
			Resources::Load<graphics::Texture>(L"Player" , L"..\\Resources\\CloudOcean.png");
		}
		m.unlock();

		loadComplete = true;
	}
}
