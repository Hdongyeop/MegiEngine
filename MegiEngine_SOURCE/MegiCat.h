#pragma once
#include "MegiGameObject.h"

namespace MegiEngine
{
	class Cat : public GameObject
	{
	public:
		Cat();
		~Cat();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
	};


}
