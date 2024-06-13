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

	extern Vertex vertexes[ 3 ];
	extern ID3D11Buffer* vertexBuffer;

	extern ID3DBlob* vsBlob;
	extern ID3D11VertexShader* vsShader;

	extern ID3DBlob* psBlob;
	extern ID3D11PixelShader* psShader;

	extern ID3D11InputLayout* inputLayouts;

}
