#pragma once
namespace MegiEngine::Type
{
	// 순서대로 Update됨
	enum class ComponentType
	{
		Transform,
		SpriteRenderer,
		Animator,
		Script,
		Camera,
		End,
	};

	enum class ResourceType
	{
		Texture,
		AudioClip,
		Animation,
		Prefab,
		End,
	};

	enum class LayerType
	{
		None,
		Background,
		Animal,
		Player,
		Particle,
		MAX = 16,
	};
}
