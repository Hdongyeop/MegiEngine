#pragma once
#include "MegiScript.h"

namespace MegiEngine
{
	class Animator;
	class Transform;
	class CatController : public Script
	{
	public:
		enum class eState
		{
			SitDown,
			Walk,
			Sleep,
			LayDown,
			Attack,
		};

		enum class eDirection
		{
			Left,
			Right,
			Down,
			Up,
			End,
		};

		CatController();
		~CatController();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
		void SitDown();
		void Move();
		void LayDown();

		void PlayWalkAnimationByDirection(eDirection dir);
		void Translate(Transform* tr);
		bool CheckPositionIsValid(Math::Vector2 pos);

	private:
		eState mState;
		Animator* mAnimator;
		eDirection mDirection;
		float mTime;
		float speed;
	};


}
