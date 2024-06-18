#pragma once
#include "MegiScene.h"

namespace MegiEngine
{
	class SceneManager
	{
	public:
		template <typename T>
		static Scene* CreateScene(const std::wstring& name);
		static Scene* LoadScene(const std::wstring& name);
		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* GetDontDestroyOnLoad() { return mDontDestroyOnLoad; }
		static std::vector<GameObject*> GetGameObjects(Type::LayerType layer);

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Destroy();
		static void Release();

	private:
		static std::map<std::wstring , Scene*> mScenes;
		static Scene* mActiveScene;
		static Scene* mDontDestroyOnLoad;
	};

	template <typename T>
	Scene* SceneManager::CreateScene(const std::wstring& name)
	{
		T* scene = new T();
		scene->SetName(name);
		mActiveScene = scene;
		scene->Initialize();

		mScenes.insert(std::make_pair(name , scene));

		return scene;
	}
}
