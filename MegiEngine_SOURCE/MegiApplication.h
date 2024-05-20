#pragma once
#include "CommonInclude.h"

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

		HDC GetHdc() const { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		void clearRenderTarget();
		void copyRenderTarget(HDC src , HDC dest);
		void adjustWindowRect(HWND hwnd , UINT width , UINT height);
		void createBuffer(UINT width , UINT height);
		void initializeEtc();

	private:
		HWND mHwnd;
		HDC mHdc;

		HDC mBackHdc;
		HBITMAP mBackBitmap;

		UINT mWidth;
		UINT mHeight;
	};

}

