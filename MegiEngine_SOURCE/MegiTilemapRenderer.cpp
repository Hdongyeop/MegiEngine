#include "MegiTilemapRenderer.h"

#include "MegiTransform.h"
#include "MegiGameObject.h"
#include "MegiRenderer.h"

namespace MegiEngine
{
	Vector2 TilemapRenderer::TileSize = Vector2::One;
	Vector2 TilemapRenderer::OriginTileSize = Vector2::One;
	Vector2 TilemapRenderer::SelectedIndex = Vector2::One;

	TilemapRenderer::TilemapRenderer()
	: Component(ComponentType::SpriteRenderer)
	, mTexture(nullptr)
	, mSize(3.0f, 3.0f)
	, mIndex(0,0)
	, mTileSize(16.0f, 16.0f)
	{
		TileSize = mTileSize * mSize;
		OriginTileSize = mTileSize;
	}

	TilemapRenderer::~TilemapRenderer()
	{
	}

	void TilemapRenderer::Initialize()
	{
		Component::Initialize();
	}

	void TilemapRenderer::Update()
	{
		Component::Update();
	}

	void TilemapRenderer::LateUpdate()
	{
		Component::LateUpdate();
	}

	void TilemapRenderer::Render()
	{
	}
}
