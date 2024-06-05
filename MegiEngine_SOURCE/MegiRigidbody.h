#pragma once
#include "MegiComponent.h"

namespace MegiEngine
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Math::Vector2 force) { mForce = force; }
		void SetGround(bool ground) { mGround = ground; }
		void SetVelocity(Math::Vector2 velocity) { mVelocity = velocity; }
		Math::Vector2 GetVelocity() const { return mVelocity; }
		void SetApplyGravity(bool flag) { applyGravity = flag; }

	private:
		bool applyGravity;
		bool mGround;
		float mMass;
		float mFriction;

		Math::Vector2 mForce;
		Math::Vector2 mAccelation;
		Math::Vector2 mVelocity;
		Math::Vector2 mLimitedVelocity;
		Math::Vector2 mGravity;
	};


}
