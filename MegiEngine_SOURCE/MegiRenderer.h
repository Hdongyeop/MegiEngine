#pragma once
#include "MegiCamera.h"
#include "MegiGraphicDevice_DX11.h"
#include "MegiVertexBuffer.h"

namespace MegiEngine::Renderer
{
	extern Camera* MainCamera;

	extern std::vector<graphics::Vertex> vertexes;
	extern graphics::VertexBuffer vertexBuffer;

	extern std::vector<UINT> indices;
	extern ID3D11Buffer* indexBuffer;

	extern ID3D11Buffer* constantBuffer;

	extern ID3D11InputLayout* inputLayouts;

	void Initialize();
	void Release();

}
