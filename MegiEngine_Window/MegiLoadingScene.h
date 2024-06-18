#pragma once
#include "..\\MegiEngine_SOURCE\\MegiScene.h"

namespace MegiEngine
{
	class LoadingScene : public Scene
	{
	public:
		LoadingScene();
		~LoadingScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnEnter() override;
		void OnExit() override;

	private:
		void ResourcesLoad(std::mutex& m);

	private:
		bool loadComplete;
		std::thread* mResourcesLoadThread;
		std::mutex mMutex;
	};
}

