#pragma once
#include "MegiComponent.h"

namespace MegiEngine
{
	class Transform;
	class PlayerController : public Component
	{
	public:
		PlayerController();
		~PlayerController();

		void Initialize() override;
		void Update() override;
	private:
		Transform* tr;
		float speed;
	};


}
