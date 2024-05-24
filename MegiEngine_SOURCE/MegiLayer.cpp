#include "MegiLayer.h"

namespace MegiEngine
{
	Layer::Layer() : mGameObjects{}
	{
	}

	Layer::~Layer()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			if ( gameObject == nullptr ) continue;

			delete gameObject;
			gameObject = nullptr;
		}
	}

	void Layer::Initialize()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if(gameObj == nullptr) continue;

			gameObj->Initialize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if(gameObj == nullptr) continue;

			GameObject::eState state = gameObj->GetState();
			if(state == GameObject::eState::Paused || state == GameObject::eState::Dead)
				continue;

			gameObj->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if(gameObj == nullptr) continue;

			GameObject::eState state = gameObj->GetState();
			if(state == GameObject::eState::Paused || state == GameObject::eState::Dead)
				continue;

			gameObj->LateUpdate();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if(gameObj == nullptr) continue;

			GameObject::eState state = gameObj->GetState();
			if(state == GameObject::eState::Paused || state == GameObject::eState::Dead)
				continue;

			gameObj->Render(hdc);
		}
	}

	void Layer::Destroy()
	{
		for(auto iter = mGameObjects.begin(); iter != mGameObjects.end(); )
		{
			GameObject::eState state = ( *iter )->GetState();
			if(state == GameObject::eState::Dead)
			{
				GameObject* deadObj = ( *iter );
				iter = mGameObjects.erase(iter);

				delete deadObj;
				deadObj = nullptr;

				continue;
			}

			++iter;
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if ( gameObject == nullptr ) return;
		mGameObjects.push_back(gameObject);
	}
}
