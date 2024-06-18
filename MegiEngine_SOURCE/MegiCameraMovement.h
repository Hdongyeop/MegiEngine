#pragma once
#include "MegiScript.h"

namespace MegiEngine
{
	class CameraMovement : public Script
	{
	public:
		CameraMovement();
		~CameraMovement();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:

	};


}
