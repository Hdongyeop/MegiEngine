#include "MegiUIBase.h"

namespace MegiEngine
{
	UIBase::UIBase(UIType type)
	: mType(type)
	, mMouseOn(false)
	{
	}

	UIBase::~UIBase()
	{
	}

	void UIBase::Initialize()
	{
		OnInit();
	}

	void UIBase::Active()
	{
		mEnabled = true;
		OnActive();
	}

	void UIBase::InActive()
	{
		mEnabled = false;
		OnInActive();
	}

	void UIBase::Update()
	{
		if ( mEnabled ) OnUpdate();
	}

	void UIBase::LateUpdate()
	{
		if ( mEnabled ) OnLateUpdate();
	}

	void UIBase::Render(HDC hdc)
	{
		if ( mEnabled ) OnRender(hdc);
	}

	void UIBase::UIClear()
	{
		OnClear();
	}

	void UIBase::OnInit()
	{
	}

	void UIBase::OnActive()
	{
	}

	void UIBase::OnInActive()
	{
	}

	void UIBase::OnUpdate()
	{
	}

	void UIBase::OnLateUpdate()
	{
	}

	void UIBase::OnRender(HDC hdc)
	{
	}

	void UIBase::OnClear()
	{
	}
}
