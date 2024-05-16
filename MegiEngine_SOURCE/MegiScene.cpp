#include "MegiScene.h"

namespace MegiEngine
{
	Scene::Scene()
	: mGameObjects{}
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
	}

	void Scene::Update()
	{
		for (auto gameObject : mGameObjects)
		{
			gameObject->Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (auto gameObject : mGameObjects)
		{
			gameObject->LateUpdate();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (auto gameObject : mGameObjects)
		{
			gameObject->Render(hdc);
		}
	}

	void Scene::AddGameObject(GameObject* gameObject)
	{
		mGameObjects.push_back(gameObject);
	}
}
