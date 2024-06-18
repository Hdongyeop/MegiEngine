#include "MegiSceneManager.h"

#include "../MegiEngine_Window/MegiDontDestroyOnLoad.h"

namespace MegiEngine
{
	std::map<std::wstring , Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Scene* SceneManager::mDontDestroyOnLoad = nullptr;

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		if ( mActiveScene != nullptr )
			mActiveScene->OnExit();

		auto iter = mScenes.find(name);
		if ( iter == mScenes.end() )
		{
			return nullptr;
		}

		mActiveScene = iter->second;
		mActiveScene->OnEnter();

		return iter->second;
	}

	std::vector<GameObject*> SceneManager::GetGameObjects(Type::LayerType layer)
	{
		std::vector<GameObject*> gameObjects = mActiveScene->GetLayer(layer)->GetGameObjects();
		std::vector<GameObject*> dontDestroyOnLoad = mDontDestroyOnLoad->GetLayer(layer)->GetGameObjects();

		gameObjects.insert(gameObjects.end() , dontDestroyOnLoad.begin() , dontDestroyOnLoad.end());

		return gameObjects;
	}

	void SceneManager::Initialize()
	{
		mDontDestroyOnLoad = CreateScene<DontDestroyOnLoad>(L"DontDestroyOnLoad");
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
		mDontDestroyOnLoad->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
		mDontDestroyOnLoad->LateUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
		mDontDestroyOnLoad->Render();
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
		mDontDestroyOnLoad->Destroy();
	}

	void SceneManager::Release()
	{
		for(auto& iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
}
