#include "MegiApplication.h"

#include "MegiInput.h"
#include "MegiTime.h"

namespace MegiEngine
{
	Application::Application() :
	mHwnd(nullptr),
	mHdc(nullptr),
	mWidth(0),
	mHeight(0),
	mBackHdc(nullptr),
	mBackBitmap(nullptr)
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hWnd, UINT width, UINT height)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		int windowStartX = 100;
		int windowStartY = 100;

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(hWnd, nullptr,
			windowStartX,
			windowStartY,
			mWidth,
			mHeight, 0);
		ShowWindow(hWnd, true);

		// 윈도우 해상도에 맞는 백버퍼 생성 
		mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);

		// 백버퍼를 가리킬 DC 생성
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = static_cast<HBITMAP>(SelectObject(mBackHdc, mBackBitmap));
		DeleteObject(oldBitmap);

		Input::Initialize();
		Time::Initialize();
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();

		mPlayer.Update();
		mBullet.Update();
	}

	void Application::LateUpdate()
	{
	}

	void Application::Render()
	{
		Rectangle(mBackHdc, 0, 0, 1600, 900);

		Time::Render(mBackHdc);

		mBullet.Render(mBackHdc);
		mPlayer.Render(mBackHdc);

		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
	}
}

