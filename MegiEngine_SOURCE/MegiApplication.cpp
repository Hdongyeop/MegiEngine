#include "MegiApplication.h"

#include "MegiCollisionManager.h"
#include "MegiFmod.h"
#include "MegiInput.h"
#include "MegiRenderer.h"
#include "MegiResources.h"
#include "MegiSceneManager.h"
#include "MegiTime.h"
#include "MegiUIManager.h"

namespace MegiEngine
{
	Application::Application()
	: mHwnd(nullptr)
	, mHdc(nullptr)
	, mWidth(0)
	, mHeight(0)
	, mBackHdc(nullptr)
	, mBackBitmap(nullptr)
	, mLoaded(false)
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hWnd, UINT width, UINT height)
	{
		AdjustWindowRect(hWnd , width , height);
		InitializeEtc();

		mGraphicDevice = std::make_unique<graphics::GraphicDevice_DX11>();
		Renderer::Initialize();
		mGraphicDevice->Initialize();

		Fmod::Initialize();
		CollisionManager::Initialize();
		UIManager::Initialize();
		SceneManager::Initialize();
	}

	void Application::AdjustWindowRect(HWND hwnd, UINT width, UINT height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		RECT rect = { 0, 0, ( LONG ) width, ( LONG ) height };
		::AdjustWindowRect(&rect , WS_OVERLAPPEDWINDOW , false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(hwnd , nullptr , 0 , 100 , mWidth , mHeight , 0);
		ShowWindow(hwnd , true);
	}

	void Application::InitializeEtc()
	{
		Input::Initialize();
		Time::Initialize();
	}

	void Application::Run()
	{
		if ( mLoaded == false )
			mLoaded = true;

		Update();
		LateUpdate();
		Render();
		Destroy();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();

		CollisionManager::Update();
		UIManager::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		CollisionManager::LateUpdate();
		UIManager::LateUpdate();
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		CollisionManager::Render();
		UIManager::Render();
		SceneManager::Render();
		Time::Render();
	}

	void Application::Release()
	{
		SceneManager::Release();
		UIManager::Release();
		Resources::Release();

		Renderer::Release();
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

}

