#pragma once
#include <map>

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
		void Initialize(HWND hWnd, UINT width, UINT height);
		void Run();
		void Update();
		void LateUpdate();
		void Render();
		void AddGameObject(GameObject& obj);
	private:
		HWND mHwnd;
		HDC mHdc;
		HDC mBackHdc;
		HBITMAP mBackBitmap;

		UINT mWidth;
		UINT mHeight;

		GameObject mPlayer;
		LoopingObject mBullet;
	};

}

