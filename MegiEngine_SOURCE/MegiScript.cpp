#include "MegiScript.h"
#include "MegiCollider.h"

namespace MegiEngine
{
	Script::Script()
	: Component(Type::ComponentType::Script)
	{
	}

	Script::~Script()
	{
	}

	void Script::Initialize()
	{
		Component::Initialize();
	}

	void Script::Update()
	{
		Component::Update();
	}

	void Script::LateUpdate()
	{
		Component::LateUpdate();
	}

	void Script::Render(HDC hdc)
	{
		Component::Render(hdc);
	}

	void Script::OnCollisionEnter(Collider* other)
	{
	}

	void Script::OnCollisionStay(Collider* other)
	{
	}

	void Script::OnCollisionExit(Collider* other)
	{
	}
}

