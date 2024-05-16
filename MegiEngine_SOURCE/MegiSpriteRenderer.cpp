#include "MegiSpriteRenderer.h"

#include "MegiGameObject.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	SpriteRenderer::SpriteRenderer()
	{

	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{
		Component::Initialize();
	}

	void SpriteRenderer::Update()
	{
		Component::Update();
	}

	void SpriteRenderer::LateUpdate()
	{
		Component::LateUpdate();
	}

	void SpriteRenderer::Render(HDC hdc)
	{
		HPEN blackPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, blackPen);

		Transform* tr = GetOwner()->GetComponent < Transform >();

		// Green Rectangle
		{
			HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc,greenBrush);
			Rectangle(hdc, tr->GetX(), tr->GetY(), 100 + tr->GetX(), 100 + tr->GetY());
			SelectObject(hdc, oldBrush);
			DeleteObject(greenBrush);
		}

		SelectObject(hdc, oldPen);
		DeleteObject(blackPen);
	}
}
