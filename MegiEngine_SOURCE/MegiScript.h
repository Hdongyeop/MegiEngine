#pragma once
#include "MegiComponent.h"

namespace MegiEngine
{
	class Script : public Component
	{
	public:
		Script();
		~Script();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
	};


}
