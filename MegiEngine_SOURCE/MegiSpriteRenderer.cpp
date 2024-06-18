#include "MegiSpriteRenderer.h"

#include "MegiGameObject.h"
#include "MegiTransform.h"
#include "MegiRenderer.h"

namespace MegiEngine
{
	SpriteRenderer::SpriteRenderer()
	: Component(ComponentType::SpriteRenderer)
	, mTexture(nullptr)
	, mSize(Vector2::One)
	{

	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{
		Component::Initialize();
	}

	void SpriteRenderer::Update()
	{
		Component::Update();
	}

	void SpriteRenderer::LateUpdate()
	{
		Component::LateUpdate();
	}

	void SpriteRenderer::Render()
	{
		if ( mTexture == nullptr ) assert(false);
	}
}
