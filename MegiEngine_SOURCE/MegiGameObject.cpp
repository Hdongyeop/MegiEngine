#include "MegiGameObject.h"

#include "MegiInput.h"
#include "MegiTime.h"

namespace MegiEngine
{
	GameObject::GameObject()
	{
		redSpeed = 100;
		blueSpeed = 100;
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Update()
	{
		///
		/// Blue One
		///
		if(Input::GetKey(KeyCode::Left))
		{
			mX -= blueSpeed * Time::DeltaTime();
		}
		if(Input::GetKey(KeyCode::Right))
		{
			mX += blueSpeed * Time::DeltaTime();
		}
		if(Input::GetKey(KeyCode::Up))
		{
			mY -= blueSpeed * Time::DeltaTime();
		}
		if(Input::GetKey(KeyCode::Down))
		{
			mY += blueSpeed * Time::DeltaTime();
		}

		///
		/// Red One
		///
		if(Input::GetKey(KeyCode::A))
		{
			mX2 -= redSpeed * Time::DeltaTime();
		}
		if(Input::GetKey(KeyCode::D))
		{
			mX2 += redSpeed * Time::DeltaTime();
		}
		if(Input::GetKey(KeyCode::W))
		{
			mY2 -= redSpeed * Time::DeltaTime();
		}
		if(Input::GetKey(KeyCode::S))
		{
			mY2 += redSpeed * Time::DeltaTime();
		}

		if(Input::GetKey(KeyCode::SPACE))
		{
			
		}
	}

	void GameObject::LateUpdate()
	{
	}

	void GameObject::Render(HDC hdc)
	{
		HPEN blackPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, blackPen);

		// Blue
//		{
//			HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
//			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);
//			Rectangle(hdc, mX, mY, 100 + mX, 100 + mY);
//			SelectObject(hdc, oldBrush);
//			DeleteObject(blueBrush);
//		}

		// Red
		{
			HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, redBrush);
			Rectangle(hdc, 400 + mX2, 400 + mY2, 500 + mX2, 500 + mY2);
			SelectObject(hdc, oldBrush);
			DeleteObject(redBrush);
		}

		SelectObject(hdc, oldPen);
		DeleteObject(blackPen);
	}
}
