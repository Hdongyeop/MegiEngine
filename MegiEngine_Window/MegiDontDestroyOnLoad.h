#pragma once
#include "MegiScene.h"

namespace MegiEngine
{
	class DontDestroyOnLoad : public Scene
	{
	public:
		DontDestroyOnLoad();
		~DontDestroyOnLoad();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnEnter() override;
		void OnExit() override;

	private:

	};
}

