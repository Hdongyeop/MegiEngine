#include "MegiTransform.h"

namespace MegiEngine
{
	Transform::Transform()
	: Component(Type::ComponentType::Transform)
	, mScale(Vector2::One)
	, mRotation(0.0f)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
		Component::Initialize();
	}

	void Transform::Update()
	{
		Component::Update();
	}

	void Transform::LateUpdate()
	{
		Component::LateUpdate();
	}

	void Transform::Render(HDC hdc)
	{
		Component::Render(hdc);
	}
}
