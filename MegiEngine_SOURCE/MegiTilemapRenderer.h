#pragma once
#include "MegiComponent.h"
#include "MegiTexture.h"

namespace MegiEngine
{
	class TilemapRenderer : public Component
	{
	public:
		TilemapRenderer();
		~TilemapRenderer();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetTexture(graphics::Texture* texture) { mTexture = texture; }
		void SetSize(Math::Vector2 size) { mSize = size; }
		void SetIndex(Math::Vector2 index) { mIndex = index; }

	public:
		static Math::Vector2 TileSize;
		static Math::Vector2 OriginTileSize;
		static Math::Vector2 SelectedIndex;

	private:
		Math::Vector2 mTileSize;
		graphics::Texture* mTexture;
		Math::Vector2 mSize;
		Math::Vector2 mIndex;
	};
}
