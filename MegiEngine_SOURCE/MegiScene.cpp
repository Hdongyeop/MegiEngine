#include "MegiScene.h"

#include "MegiCollisionManager.h"

namespace MegiEngine
{
	Scene::Scene()
	: mLayers{}
	{
		CreateLayers();
	}

	Scene::~Scene()
	{
		for (Layer* layer : mLayers)
		{
			delete layer;
			layer = nullptr;
		}
	}

	void Scene::Initialize()
	{
		for (auto& layer : mLayers)
		{
			if ( layer == nullptr ) continue;
			layer->Initialize();
		}
	}

	void Scene::Update()
	{
		for (auto& layer : mLayers)
		{
			if ( layer == nullptr ) continue;
			layer->Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (auto& layer : mLayers)
		{
			if ( layer == nullptr ) continue;
			layer->LateUpdate();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (auto& layer : mLayers)
		{
			if ( layer == nullptr ) continue;
			layer->Render(hdc);
		}
	}

	void Scene::Destroy()
	{
		for (auto& layer : mLayers)
		{
			if ( layer == nullptr ) continue;
			layer->Destroy();
		}
	}

	void Scene::OnEnter()
	{
	}

	void Scene::OnExit()
	{
		CollisionManager::Clear();
	}

	void Scene::AddGameObject(GameObject* gameObject, const Type::LayerType type)
	{
		 mLayers[(UINT)type]->AddGameObject(gameObject);
	}

	void Scene::CreateLayers()
	{
		mLayers.resize(( UINT ) Type::LayerType::MAX);
		for (Layer*& _mLayer : mLayers)
		{
			_mLayer = new Layer();
		}
	}

	Layer* Scene::GetLayer(Type::LayerType type)
	{
		return mLayers[ ( UINT ) type ];
	}

	void Scene::EraseGameObject(GameObject* gameObject)
	{
		Type::LayerType layerType = gameObject->GetLayerType();
		mLayers[ ( UINT ) layerType ]->EraseGameObject(gameObject);
	}
}
