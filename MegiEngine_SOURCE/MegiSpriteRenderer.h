#pragma once

#include "MegiComponent.h"
#include "MegiTexture.h"

namespace MegiEngine
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void SetTexture(graphics::Texture* texture) { mTexture = texture; }

	private:
		graphics::Texture* mTexture;
		Math::Vector2 mSize;
	};


}
