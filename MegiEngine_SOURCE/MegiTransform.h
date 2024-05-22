#pragma once
#include "MegiComponent.h"

namespace MegiEngine
{
	using namespace Math;
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
		float GetRotation() { return mRotation; }
		void SetRotation(float rotation) { mRotation = rotation; }
		Vector2 GetScale() { return mScale; }
		void SetScale(Vector2 scale) { mScale = scale; }

	private:
		Vector2 mPosition;
		Vector2 mScale;
		float mRotation;
	};


}
