#pragma once
#include "CommonInclude.h"
#include "MegiGraphicDevice_DX11.h"
#include "MegiTexture.h"

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
		void Release();
		void Destroy();

		HDC GetHdc() const { return mHdc; }
		HWND GetHwnd() const { return mHwnd; }
		UINT GetWidth() const { return mWidth; }
		UINT GetHeight() const { return mHeight; }

	private:
		void clearRenderTarget();
		void copyRenderTarget(HDC src , HDC dest);
		void adjustWindowRect(HWND hwnd , UINT width , UINT height);
		void createBuffer(UINT width , UINT height);
		void initializeEtc();

	private:
		std::unique_ptr<graphics::GraphicDevice_DX11> mGraphicDevice;
	
		HWND mHwnd;
		HDC mHdc;

		HDC mBackHdc;
		HBITMAP mBackBitmap;

		UINT mWidth;
		UINT mHeight;
	};

}

