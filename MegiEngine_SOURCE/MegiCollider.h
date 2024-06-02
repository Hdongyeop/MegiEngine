#pragma once
#include "MegiComponent.h"

namespace MegiEngine
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		Math::Vector2 GetOffset() { return mOffset; }
		void SetOffset(Math::Vector2 offset) { mOffset = offset; }

	private:
		Math::Vector2 mOffset;
	};


}
