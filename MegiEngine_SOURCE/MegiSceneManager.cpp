#include "MegiSceneManager.h"

namespace MegiEngine
{
	std::map<std::wstring , Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

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

	void SceneManager::Initialize()
	{
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}
}
