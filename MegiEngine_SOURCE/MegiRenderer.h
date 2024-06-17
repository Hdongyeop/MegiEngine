#pragma once
#include "MegiCamera.h"
#include "MegiConstantBuffer.h"
#include "MegiGraphicDevice_DX11.h"
#include "MegiIndexBuffer.h"
#include "MegiVertexBuffer.h"

namespace MegiEngine::Renderer
{
	extern Camera* MainCamera;

	extern std::vector<graphics::Vertex> vertexes;
	extern graphics::VertexBuffer vertexBuffer;

	extern std::vector<UINT> indices;
	extern graphics::IndexBuffer indexBuffer;

	extern graphics::ConstantBuffer constantBuffers[ ( UINT ) graphics::CBType::End ];

	extern ID3D11InputLayout* inputLayouts;

	void Initialize();
	void Release();

}
