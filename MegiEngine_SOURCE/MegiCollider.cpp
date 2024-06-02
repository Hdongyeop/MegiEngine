#include "MegiCollider.h"

namespace MegiEngine
{
	Collider::Collider()
	: Component(Type::ComponentType::Collider)
	{
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
		Component::Initialize();
	}

	void Collider::Update()
	{
		Component::Update();
	}

	void Collider::LateUpdate()
	{
		Component::LateUpdate();
	}

	void Collider::Render(HDC hdc)
	{
		Component::Render(hdc);
	}
}
