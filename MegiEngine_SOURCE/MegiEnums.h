#pragma once
namespace MegiEngine::Type
{
	// 순서대로 Update됨
	enum class ComponentType
	{
		Transform,
		Collider,
		Script,
		SpriteRenderer,
		Animator,
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
		Tile,
		Animal,
		Player,
		Particle,
		MAX = 16,
	};

	enum class ColliderType
	{
		Circle2D,
		Rect2D,
		End,
	};
}
