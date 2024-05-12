#include "MegiGameObject.h"

namespace MegiEngine
{
	GameObject::GameObject()
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Update()
	{
		///
		/// Blue One
		///
		if(GetAsyncKeyState(VK_LEFT) & KF_UP)
		{
			mX -= 0.01f;
		}
		if(GetAsyncKeyState(VK_RIGHT) & KF_UP)
		{
			mX += 0.01f;
		}
		if(GetAsyncKeyState(VK_UP) & KF_UP)
		{
			mY -= 0.01f;
		}
		if(GetAsyncKeyState(VK_DOWN) & KF_UP)
		{
			mY += 0.01f;
		}

		///
		/// Red One
		///
		if(GetAsyncKeyState('A') & KF_UP)
		{
			mX2 -= 0.01f;
		}
		if(GetAsyncKeyState('D') & KF_UP)
		{
			mX2 += 0.01f;
		}
		if(GetAsyncKeyState('W') & KF_UP)
		{
			mY2 -= 0.01f;
		}
		if(GetAsyncKeyState('S') & KF_UP)
		{
			mY2 += 0.01f;
		}
	}

	void GameObject::LateUpdate()
	{
	}

	void GameObject::Render(HDC hdc)
	{
		HPEN blackPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		SelectObject(hdc, blackPen);

		// Blue
		{
			HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, blueBrush);
			Rectangle(hdc, mX, mY, 100 + mX, 100 + mY);
			DeleteObject(blueBrush);
		}

		// Red
		{
			HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, redBrush);
			Rectangle(hdc, 400 + mX2, 400 + mY2, 500 + mX2, 500 + mY2);
			DeleteObject(redBrush);
		}

		DeleteObject(blackPen);
	}
}
