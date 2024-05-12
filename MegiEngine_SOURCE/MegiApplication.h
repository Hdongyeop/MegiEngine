#pragma once
#include "CommonInclude.h"
#include "MegiGameObject.h"
#include "MegiLoopingObject.h"

namespace MegiEngine
{
	class Application
	{
	public:
		Application();
		~Application();
		void Initialize(HWND hWnd);
		void Run();
		void Update();
		void LateUpdate();
		void Render();
	private:
		HWND mHwnd;
		HDC mHdc;

		float mSpeed;
		GameObject mPlayer;
		LoopingObject mLoopingObj;
	};

}

