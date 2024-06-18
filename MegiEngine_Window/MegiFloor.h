#pragma once
#include "MegiGameObject.h"

namespace MegiEngine
{
	class Floor : public GameObject
	{
	public:
		Floor();
		~Floor();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:

	};


}
