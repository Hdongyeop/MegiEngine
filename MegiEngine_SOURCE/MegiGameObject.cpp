#include "MegiGameObject.h"

#include "MegiTransform.h"

namespace MegiEngine
{
	GameObject::GameObject()
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
