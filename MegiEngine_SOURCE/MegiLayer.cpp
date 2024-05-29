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
			if(gameObj->IsActive() == false) continue;

			gameObj->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if(gameObj == nullptr) continue;
			if(gameObj->IsActive() == false) continue;

			gameObj->LateUpdate();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if(gameObj == nullptr) continue;
			if(gameObj->IsActive() == false) continue;

			gameObj->Render(hdc);
		}
	}

	void Layer::Destroy()
	{
		std::vector<GameObject*> deleteObjects;
		// 메모리 해제할 녀석들 모으기
		FindDeadGameObjects(deleteObjects);
		// mGameObjects에서 지우기
		eraseGameObject();
		// 메모리 해제하기
		DeleteGameObjects(deleteObjects);
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if ( gameObject == nullptr ) return;
		mGameObjects.push_back(gameObject);
	}

	void Layer::FindDeadGameObjects(std::vector<GameObject*>& gameObjs)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			GameObject::eState active = gameObj->GetState();
			if ( active == GameObject::eState::Dead )
				gameObjs.push_back(gameObj);
		}
	}

	void Layer::DeleteGameObjects(std::vector<GameObject*> gameObjs)
	{
		for (GameObject* obj : gameObjs)
		{
			delete obj;
			obj = nullptr;
		}
	}

	void Layer::eraseGameObject()
	{
		// Predicate result가 true인 경우 삭제
		std::erase_if(mGameObjects ,
			[](GameObject* gameObj)
			{
				return ( gameObj )->IsDead();
			});
	}
}
