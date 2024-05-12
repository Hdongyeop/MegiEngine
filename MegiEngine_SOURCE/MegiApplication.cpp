#include "MegiApplication.h"

namespace MegiEngine
{
	Application::Application() : mHwnd(nullptr), mHdc(nullptr), mSpeed(0)
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);

		mPlayer.SetPlayerPosition(0, 0);
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update()
	{
		mSpeed += 0.003f;

		mPlayer.Update();
		mLoopingObj.Update();
	}

	void Application::LateUpdate()
	{
	}

	void Application::Render()
	{
		mPlayer.Render(mHdc);
		mLoopingObj.Render(mHdc);
	}
}

