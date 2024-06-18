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
		void Render() override;

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

		void SetRotation(float rotation) { mRotation = rotation; }
		void SetScale(Vector2 scale) { mScale = scale; }
		Vector2 GetPosition() const { return mPosition; }
		float GetRotation() const { return mRotation; }
		Vector2 GetScale() const { return mScale; }

	private:
		Vector2 mPosition;
		Vector2 mScale;
		float mRotation;
	};


}
