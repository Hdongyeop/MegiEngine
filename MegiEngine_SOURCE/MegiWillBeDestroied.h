#pragma once
#include "MegiComponent.h"

namespace MegiEngine
{
	class WillBeDestroied : public Component
	{
	public:
		WillBeDestroied(float time);
		~WillBeDestroied();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
		float mTime = 0;
		float mLimitTime = 0;
	};


}
