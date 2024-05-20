#pragma once
namespace MegiEngine::Type
{
	enum class ComponentType
	{
		Transform,
		SpriteRenderer,
		Script,
		Camera,
		End,
	};

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
