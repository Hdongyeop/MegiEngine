#include "MegiScene.h"

namespace MegiEngine
{
	Scene::Scene()
	: mLayers{}
	{
		CreateLayers();
	}

	Scene::~Scene()
	{
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

	void Scene::OnEnter()
	{
	}

	void Scene::OnExit()
	{
	}

	void Scene::AddGameObject(GameObject* gameObject, const LayerType type)
	{
		 mLayers[(UINT)type]->AddGameObject(gameObject);
	}

	void Scene::CreateLayers()
	{
		mLayers.resize(( UINT ) LayerType::MAX);
		for (Layer*& _mLayer : mLayers)
		{
			_mLayer = new Layer();
		}
	}

	Layer* Scene::GetLayer(LayerType type)
	{
		return mLayers[ ( UINT ) type ];
	}
}