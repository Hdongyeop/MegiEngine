#pragma once
#include <type_traits>

#include "MegiEnums.h"
#include "MegiGameObject.h"
#include "MegiScene.h"
#include "MegiSceneManager.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	template <typename T, std::enable_if_t<std::is_base_of_v<GameObject, T>, bool> = true>
	static T* Instantiate(LayerType type)
	{
		T* gameObject = new T();
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObject);

		return gameObject;
	}

	template <typename T, std::enable_if_t<std::is_base_of_v<GameObject, T>, bool> = true>
	static T* Instantiate(LayerType type, Vector2 position)
	{
		T* gameObject = new T();
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObject);

		Transform* tr = gameObject->GetComponent<Transform>();
		tr->SetPosition(position);

		return gameObject;
	}
}