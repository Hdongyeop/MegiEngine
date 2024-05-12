#pragma once
#include "CommonInclude.h"

namespace MegiEngine
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void virtual Update();
		void LateUpdate();
		void virtual Render(HDC hdc);

		void SetPlayerPosition(float x, float y)
		{
			mX = x;
			mY = y;
		}

		void SetTargetPosition(float x, float y)
		{
			mX2 = x;
			mY2 = y;
		}

		int GetPositionX()
		{
			return mX;
		}

		int GetPositionY()
		{
			return mY;
		}

	private:
		float mX;
		float mY;
		float mX2;
		float mY2;
	};
}

