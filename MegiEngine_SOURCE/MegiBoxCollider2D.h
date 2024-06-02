#pragma once
#include "MegiCollider.h"

namespace MegiEngine
{
	class BoxCollider2D : public Collider
	{
	public:
		BoxCollider2D();
		~BoxCollider2D();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

	private:
		Math::Vector2 mSize;
	};
}
