#pragma once
#include "..\\MegiEngine_SOURCE\\MegiResources.h"
#include "..\\MegiEngine_SOURCE\\MegiTexture.h"

namespace MegiEngine
{
	void LoadResource()
	{
		Resources::Load<graphics::Texture>(L"Background" , L"E:\\MegiEngine\\Resources\\CloudOcean.png");
		Resources::Load<graphics::Texture>(L"Player" , L"E:\\MegiEngine\\Resources\\Player.bmp");
	}
}
