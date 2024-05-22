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
			SitDown,
			Walk,
			Sleep,
			Attack,
		};

		PlayerController();
		~PlayerController();

		void Initialize() override;
		void Update() override;

	private:
		void SitDown();
		void Move();
		bool CheckPositionIsValid(Math::Vector2 pos);

	private:
		eState mState;
		class Animator* mAnimator;
		Transform* tr;
		float speed;
	};


}
