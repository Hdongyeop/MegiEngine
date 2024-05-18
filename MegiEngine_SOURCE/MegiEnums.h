#pragma once
namespace MegiEngine
{
	enum class ResourceType
	{
		Texture,
		AudioClip,
		Prefab,
		End,
	};

	enum class LayerType
	{
		None ,
		Background ,
		// Tree,
		// Character,
		Player ,
		MAX = 16,
	};
}
