#pragma once
#include "MegiGameObject.h"

namespace MegiEngine
{
	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
	};


}
