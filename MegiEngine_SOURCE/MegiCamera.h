#pragma once
#include "MegiComponent.h"

namespace MegiEngine
{
	using namespace Math;
	class Camera : public Component
	{
	public:
		Vector2 CalculatePosition(Vector2 pos) const { return pos - mDistance; }
		Vector2 CalculateTilePosition(Vector2 pos) const { return pos + mDistance; }

		Camera();
		~Camera();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void SetTarget(GameObject* target) { mTarget = target; }

	private:
		GameObject* mTarget;
		Vector2 mDistance;
		Vector2 mResolution;
		Vector2 mLookPosition;
	};

}

