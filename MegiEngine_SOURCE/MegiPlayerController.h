#pragma once
#include "MegiScript.h"

namespace MegiEngine
{
	class Transform;
	class PlayerController : public Script
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
