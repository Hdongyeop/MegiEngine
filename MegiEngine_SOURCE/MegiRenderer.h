#pragma once
#include "MegiCamera.h"
#include "MegiGraphicDevice_DX11.h"

namespace MegiEngine::Renderer
{
	extern Camera* MainCamera;

	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern Vertex vertexes[ 4 ];
	extern ID3D11Buffer* vertexBuffer;

	extern std::vector<UINT> indices;
	extern ID3D11Buffer* indexBuffer;

	extern ID3D11Buffer* constantBuffer;

	extern ID3D11InputLayout* inputLayouts;

	void Initialize();
	void Release();

}
