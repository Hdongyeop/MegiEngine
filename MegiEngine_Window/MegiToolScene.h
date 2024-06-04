#pragma once
#include "..\\MegiEngine_SOURCE\\MegiScene.h"

namespace MegiEngine
{
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		~ToolScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;

	private:

	};
}

LRESULT CALLBACK WndTileProc(HWND hWnd , UINT messge , WPARAM wParam , LPARAM lParam);
