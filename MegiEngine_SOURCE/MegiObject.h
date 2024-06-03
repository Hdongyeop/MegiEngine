#pragma once
#include <type_traits>

#include "MegiEnums.h"
#include "MegiGameObject.h"
#include "MegiRenderer.h"
#include "MegiScene.h"
#include "MegiSceneManager.h"
#include "MegiTransform.h"

namespace MegiEngine::Object
{
	template <typename T, std::enable_if_t<std::is_base_of_v<GameObject, T>, bool> = true>
	static T* Instantiate(Type::LayerType type)
	{
		T* gameObject = new T();
		gameObject->SetLayerType(type);
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObject);

		return gameObject;
	}

	template <typename T, std::enable_if_t<std::is_base_of_v<GameObject, T>, bool> = true>
	static T* Instantiate(Type::LayerType type, Vector2 position)
	{
		T* gameObject = new T();
		gameObject->SetLayerType(type);
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObject);

		Transform* tr = gameObject->GetComponent<Transform>();
		tr->SetPosition(position);

		return gameObject;
	}

	static void DontDestroyOnLoad(GameObject* gameObject)
	{
		// 해당 게임오브젝트를 Scene에서 지운다.
		Scene* activeScene = SceneManager::GetActiveScene();
		activeScene->EraseGameObject(gameObject);

		// 해당 게임오브젝트를 DontDestroy Scene으로 넣어준다
		Scene* dontDestroyOnLoad = SceneManager::GetDontDestroyOnLoad();
		dontDestroyOnLoad->AddGameObject(gameObject , gameObject->GetLayerType());

		gameObject->Initialize();
	}
}
