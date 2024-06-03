#include "MegiCollider.h"

#include "MegiGameObject.h"
#include "MegiScript.h"

namespace MegiEngine
{
	UINT Collider::CollisionID = 1;

	Collider::Collider()
	: Component(Type::ComponentType::Collider)
	, mID(CollisionID++)
	, mSize(Math::Vector2::One)
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

	void Collider::OnCollisionEnter(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		if(script != nullptr) 
			script->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		if ( script != nullptr )
			script->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		if ( script != nullptr )
			script->OnCollisionExit(other);
	}
}
