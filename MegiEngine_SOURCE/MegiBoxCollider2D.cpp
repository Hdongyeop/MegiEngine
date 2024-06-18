#include "MegiBoxCollider2D.h"

#include "MegiGameObject.h"
#include "MegiRenderer.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	BoxCollider2D::BoxCollider2D()
	: Collider(Type::ColliderType::Rect2D)
	{
		
	}

	BoxCollider2D::~BoxCollider2D()
	{
		
	}

	void BoxCollider2D::Initialize()
	{
		
	}

	void BoxCollider2D::Update()
	{
		
	}

	void BoxCollider2D::LateUpdate()
	{
		
	}

	void BoxCollider2D::Render()
	{
		Transform* tr = GetOwner()->GetComponent < Transform >();
		Vector2 pos = tr->GetPosition();
	}


}
