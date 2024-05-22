#pragma once
#include "..\\MegiEngine_SOURCE\\MegiResources.h"
#include "..\\MegiEngine_SOURCE\\MegiTexture.h"

namespace MegiEngine
{
	void LoadResource()
	{
		Resources::Load<graphics::Texture>(L"Background" , L"E:\\MegiEngine\\Resources\\CloudOcean.png");
		Resources::Load<graphics::Texture>(L"Player" , L"E:\\MegiEngine\\Resources\\Player.bmp");
		Resources::Load<graphics::Texture>(L"Cat" , L"E:\\MegiEngine\\Resources\\Cat.bmp");
		Resources::Load<graphics::Texture>(L"HitEffect" , L"E:\\MegiEngine\\Resources\\HitEffect.png");
		Resources::Load<graphics::Texture>(L"Bubble" , L"E:\\MegiEngine\\Resources\\Bubble.png");
		Resources::Load<graphics::Texture>(L"Black" , L"E:\\MegiEngine\\Resources\\Black.png");
	}
}
