#pragma once
#include "..\\MegiEngine_SOURCE\\MegiResources.h"
#include "..\\MegiEngine_SOURCE\\MegiTexture.h"

namespace MegiEngine
{
	void LoadResource()
	{
		// BMP
		Resources::Load<graphics::Texture>(L"Cat" , L"..\\Resources\\Cat.bmp");

		// PNG
		Resources::Load<graphics::Texture>(L"Background" , L"..\\Resources\\CloudOcean.png");
		Resources::Load<graphics::Texture>(L"Player" , L"..\\Resources\\Player_Outline.png");
		Resources::Load<graphics::Texture>(L"HitEffect" , L"..\\Resources\\HitEffect.png");
		Resources::Load<graphics::Texture>(L"Bubble" , L"..\\Resources\\Bubble.png");
		Resources::Load<graphics::Texture>(L"Black" , L"..\\Resources\\Black.png");
	}
}
