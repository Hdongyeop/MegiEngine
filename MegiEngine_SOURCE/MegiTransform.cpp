#include "MegiTransform.h"

namespace MegiEngine
{
	Transform::Transform()
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
