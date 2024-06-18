#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "CommonInclude.h"

namespace MegiEngine::graphics
{
	struct Vertex
	{
		Math::Vector3 pos;
		Math::Vector4 color;
	};

	enum class ShaderStage
	{
		VS,			// Vertex Shader
		HS,			// Hull Shader
		DS,			// Domain Shader
		GS,			// Geometry Shader
		PS,			// Pixel Shader
		CS,			// Compute Shader
		All,
		End,
	};

	enum class CBType
	{
		Transform,
		None,
		End,
	};

	struct GpuBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer = nullptr;
		D3D11_BUFFER_DESC desc = {};

		GpuBuffer() = default;
		virtual ~GpuBuffer() = default;
	};
}
