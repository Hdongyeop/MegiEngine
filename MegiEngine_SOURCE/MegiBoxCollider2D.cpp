#include "MegiBoxCollider2D.h"

#include "MegiGameObject.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	BoxCollider2D::BoxCollider2D()
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

	void BoxCollider2D::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent < Transform >();
		Vector2 pos = tr->GetPosition();

		Vector2 offset = GetOffset();

		HBRUSH transparentBrush = ( HBRUSH ) GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = ( HBRUSH ) SelectObject(hdc , transparentBrush);

		HPEN greenPen = CreatePen(PS_SOLID , 2 , RGB(0 , 255 , 0));
		HPEN oldPen = ( HPEN ) SelectObject(hdc , greenPen);

		Rectangle(hdc
		, pos.x + offset.x
		, pos.y + offset.y
		, pos.x + offset.x + GetSize().x
		, pos.y + offset.y + GetSize().y);

		SelectObject(hdc , oldBrush);
		SelectObject(hdc , oldPen);
		DeleteObject(greenPen);
	}


}