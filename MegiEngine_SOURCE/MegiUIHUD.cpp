#include "MegiUIHUD.h"

#include "MegiResources.h"

namespace MegiEngine
{
	UIHUD::UIHUD()
	: UIBase(UIType::HpBar)
	{
	}

	UIHUD::~UIHUD()
	{
	}

	void UIHUD::OnInit()
	{
		mTexture = Resources::Find<graphics::Texture>(L"HPBAR");
	}

	void UIHUD::OnActive()
	{
		UIBase::OnActive();
	}

	void UIHUD::OnInActive()
	{
		UIBase::OnInActive();
	}

	void UIHUD::OnUpdate()
	{
		UIBase::OnUpdate();
	}

	void UIHUD::OnLateUpdate()
	{
		UIBase::OnLateUpdate();
	}

	void UIHUD::OnRender()
	{
	}

	void UIHUD::OnClear()
	{
		UIBase::OnClear();
	}
}
