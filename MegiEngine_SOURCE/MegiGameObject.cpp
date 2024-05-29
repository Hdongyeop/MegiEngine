#include "MegiGameObject.h"

#include "MegiTransform.h"

namespace MegiEngine::Object
{
	void Destroy(GameObject* gameObject)
	{
		if ( gameObject == nullptr ) return;
		gameObject->Death();
	}

}

namespace MegiEngine
{
	GameObject::GameObject()
	: mState(eState::Active)
	{
		mComponents.resize(( UINT ) Type::ComponentType::End);
		InitializeTransform();
	}

	GameObject::~GameObject()
	{
		for (auto _mComponent : mComponents)
		{
			if ( _mComponent == nullptr ) continue;

			delete _mComponent;
			_mComponent = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (auto _mComponent : mComponents)
		{
			if ( _mComponent == nullptr ) continue;
			_mComponent->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (auto _mComponent : mComponents)
		{
			if ( _mComponent == nullptr ) continue;
			_mComponent->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (auto _mComponent : mComponents)
		{
			if ( _mComponent == nullptr ) continue;
			_mComponent->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (auto _mComponent : mComponents)
		{
			if ( _mComponent == nullptr ) continue;
			_mComponent->Render(hdc);
		}
	}

	void GameObject::InitializeTransform()
	{
		AddComponent<Transform>();
	}
}
