#include "MegCircleCollider2D.h"
#include "MegiGameObject.h"
#include "MegiRenderer.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	CircleCollider2D::CircleCollider2D()
	:Collider(Type::ColliderType::Circle2D)
	,mRadius(0.0f)
	{
		
	}

	CircleCollider2D::~CircleCollider2D()
	{
		
	}

	void CircleCollider2D::Initialize()
	{
		
	}

	void CircleCollider2D::Update()
	{
		
	}

	void CircleCollider2D::LateUpdate()
	{
		
	}

	void CircleCollider2D::Render()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
	}
}
