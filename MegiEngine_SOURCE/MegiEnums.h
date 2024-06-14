#pragma once
namespace MegiEngine::Type
{
	// 순서대로 Update됨
	enum class ComponentType
	{
		Transform,
		Collider,
		Rigidbody,
		Script,
		SpriteRenderer,
		Animator,
		Camera,
		AudioListener,
		AudioSource,
		End,
	};

	enum class ResourceType
	{
		Texture,
		Animation,
		AudioClip,
		Shader,
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
		Floor,
		Particle,
		MAX = 16,
	};

	enum class ColliderType
	{
		Circle2D,
		Rect2D,
		End,
	};

	enum class UIType
	{
		HpBar,
		Button,
		End,
	};
}
