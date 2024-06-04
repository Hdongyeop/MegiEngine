#include "MegiTile.h"

#include "..\\MegiEngine_SOURCE\\MegiTransform.h"
#include "..\\MegiEngine_SOURCE\\MegiTilemapRenderer.h"

namespace MegiEngine
{
	Tile::Tile()
	{
	}

	Tile::~Tile()
	{
	}

	void Tile::Initialize()
	{
		GameObject::Initialize();
	}

	void Tile::Update()
	{
		GameObject::Update();
	}

	void Tile::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Tile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Tile::SetIndexPosition(int x, int y)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos;
		pos.x = x * TilemapRenderer::TileSize.x;
		pos.y = y * TilemapRenderer::TileSize.y;

		tr->SetPosition(pos);
	}
}
