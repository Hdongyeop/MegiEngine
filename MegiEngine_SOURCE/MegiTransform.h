#pragma once
#include "MegiComponent.h"

namespace MegiEngine
{
	struct Pos
	{
		int mX;
		int mY;
	};

	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetPosition(Vector2 pos)
		{
			mPosition.x = pos.x;
			mPosition.y = pos.y;
		}

		void SetPosition(float x, float y)
		{
			mPosition.x = x;
			mPosition.y = y;
		}

		Vector2 GetPosition() { return mPosition; }

	private:
		Vector2 mPosition;
	};


}
