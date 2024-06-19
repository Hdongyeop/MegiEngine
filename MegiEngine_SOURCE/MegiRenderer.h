#pragma once
#include "MegiCamera.h"
#include "MegiConstantBuffer.h"
#include "MegiGraphicDevice_DX11.h"
#include "MegiMesh.h"

namespace MegiEngine::Renderer
{
	extern Camera* MainCamera;

	extern Mesh* mesh;

	extern graphics::ConstantBuffer constantBuffers[ ( UINT ) graphics::CBType::End ];

	extern ID3D11InputLayout* inputLayouts;

	void Initialize();
	void Release();

}
