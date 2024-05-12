#include "MegiLoopingObject.h"

namespace MegiEngine
{
	LoopingObject::LoopingObject()
	{
		curX = startX;
		dir = 1;
	}

	LoopingObject::~LoopingObject()
	{
	}

	void LoopingObject::Update()
	{
		curX += dir * 0.01f;

		if (curX > startX + movingDistance) dir = -1;
		if (curX < startX - movingDistance) dir = 1;
	}

	void LoopingObject::Render(HDC hdc)
	{
		HPEN blackPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		SelectObject(hdc, blackPen);

		// Green
		{
			HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc,greenBrush);
			Rectangle(hdc, curX, 250, 100 + curX, 350);
			DeleteObject(greenBrush);
		}

		DeleteObject(blackPen);
	}
}
