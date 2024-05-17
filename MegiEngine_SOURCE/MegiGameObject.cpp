#include "MegiGameObject.h"

#include "MegiTransform.h"

namespace MegiEngine
{
	GameObject::GameObject()
	{
		InitializeTransform();
	}

	GameObject::~GameObject()
	{
		for (auto _mComponent : mComponents)
		{
			delete _mComponent;
			_mComponent = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (auto _mComponent : mComponents)
		{
			_mComponent->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (auto _mComponent : mComponents)
		{
			_mComponent->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (auto _mComponent : mComponents)
		{
			_mComponent->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (auto _mComponent : mComponents)
		{
			_mComponent->Render(hdc);
		}
	}

	void GameObject::InitializeTransform()
	{
		AddComponent<Transform>();
	}
}
