#include "MegiUIButton.h"

#include "MegiInput.h"

namespace MegiEngine
{
	UIButton::UIButton()
	: UIBase(UIType::Button)
	{
	}

	UIButton::~UIButton()
	{
	}

	void UIButton::OnInit()
	{
		SetPos(Math::Vector2(200.0f , 200.0f));
		SetSize(Math::Vector2(200.0f , 200.0f));

		mOnClick = std::bind(&UIButton::ButtonClick , this);
	}

	void UIButton::OnActive()
	{
		UIBase::OnActive();
	}

	void UIButton::OnInActive()
	{
		UIBase::OnInActive();
	}

	void UIButton::OnUpdate()
	{
		Math::Vector2 mousePos = Input::GetMousePosition();

		if(mPosition.x <= mousePos.x && mousePos.x <= mPosition.x + mSize.x &&
			mPosition.y <= mousePos.y && mousePos.y <= mPosition.y + mSize.y)
		{
			mMouseOn = true;
		}
		else
		{
			mMouseOn = false;
		}

		if(Input::GetKeyDown(KeyCode::LMB))
		{
			if ( mMouseOn ) mOnClick();
		}
	}

	void UIButton::OnLateUpdate()
	{
		UIBase::OnLateUpdate();
	}

	void UIButton::OnRender(HDC hdc)
	{
		Rectangle(hdc
		, ( int ) mPosition.x , ( int ) mPosition.y
		, mPosition.x + mSize.x , mPosition.y + mSize.y);
	}

	void UIButton::OnClear()
	{
		UIBase::OnClear();
	}

	void UIButton::ButtonClick()
	{
		int a = 0;
	}
}
