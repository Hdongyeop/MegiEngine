#pragma once

namespace MegiEngine::graphics
{
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
		End,
	};
}
