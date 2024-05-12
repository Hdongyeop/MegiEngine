#pragma once
#include "MegiGameObject.h"

namespace MegiEngine
{
	class LoopingObject : GameObject
	{
	public:
		LoopingObject();
		~LoopingObject();
		void Update() override;
		void Render(HDC hdc) override;
	private:
		const float movingDistance = 50;
		const float startX = 250;
		float curX;
		int dir;
	};
}

