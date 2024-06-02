#pragma once
#include "MegiGameObject.h"
#include "MegiScript.h"

namespace MegiEngine
{
	class MoveToMousePos : public Script
	{
	public:
		MoveToMousePos();
		~MoveToMousePos();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetDestPos(Math::Vector2 pos)
		{
			destPos = pos;
		}

		void SetRotation(Math::Vector2 pos);

	private:
		Math::Vector2 destPos;
	};


}
