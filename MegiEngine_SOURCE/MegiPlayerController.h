#pragma once
#include "MegiScript.h"

namespace MegiEngine
{
	class Transform;
	class PlayerController : public Script
	{
	public:
		enum class eState
		{
			Idle,
			Walk,
			Sleep,
			Attack,
			GiveWater,
		};

		PlayerController();
		~PlayerController();

		void Initialize() override;
		void Update() override;

		void AttackEffect();

	private:
		void Idle();
		void Move();
		void GiveWater();
		bool CheckPositionIsValid(Math::Vector2 pos);

	private:
		eState mState;
		class Animator* mAnimator;
		Transform* tr;
		float speed;
	};


}
