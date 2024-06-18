// Editor_Window.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Editor_Window.h"
#include "../MegiEngine_SOURCE/MegiApplication.h"
#include "../MegiEngine_SOURCE/MegiResources.h"
#include "../MegiEngine_SOURCE/MegiTexture.h"
#include "../MegiEngine_Window/MegiLoadScene.h"
#include "../MegiEngine_Window/MegiToolScene.h"

#pragma comment(lib, "../x64/Debug/MegiEngine_Window.lib")

using namespace MegiEngine;

#define MAX_LOADSTRING 100

// 전역 변수:
Application application;
UINT toolTextureSize = 2;

ULONG_PTR gpToken;
Gdiplus::GdiplusStartupInput gpsi;

HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc);
BOOL                InitInstance(HINSTANCE, int);
BOOL				InitToolScene(HINSTANCE);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	// Memory Leak Check
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EDITORWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance, szWindowClass, WndProc);
    MyRegisterClass(hInstance, L"TILEWINDOW", WndTileProc);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDITORWINDOW));

    MSG msg;

    while (true)
    {
        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
        else
        {
            application.Run();
        }
    }

	Gdiplus::GdiplusShutdown(gpToken);
	application.Release();

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = proc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITORWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL; // MAKEINTRESOURCEW(IDC_EDITORWINDOW);
    wcex.lpszClassName  = name;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   const UINT width = 1600;
   const UINT height = 900;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInstance, nullptr);

   application.Initialize(hWnd , width , height);

   if ( !hWnd )
   {
	   return FALSE;
   }

   // Window Settings
   ShowWindow(hWnd , nCmdShow);
   UpdateWindow(hWnd);

   //   ShowWindow(toolHwnd , nCmdShow);
   //   UpdateWindow(toolHwnd);

	  // GdiPlus
   Gdiplus::GdiplusStartup(&gpToken , &gpsi , NULL);

   //load scenes
   // MegiEngine::LoadResource(); -> LoadingScene에서 하는걸로 수정
   MegiEngine::LoadScene();

   InitToolScene(hInstance);

   return TRUE;
}

BOOL InitToolScene(HINSTANCE hInstance)
{
	Scene* activeScene = SceneManager::GetActiveScene();
	std::wstring name = activeScene->GetName();
	if ( name == L"ToolScene" )
	{
		HWND toolHwnd = CreateWindowW(L"TILEWINDOW" , L"TileWindow" , WS_OVERLAPPEDWINDOW
		, 0 , 0 , CW_USEDEFAULT , 0 , nullptr , nullptr , hInstance , nullptr);

		// Tile 윈도우 크기 조정
		graphics::Texture* texture = Resources::Find<graphics::Texture>(L"SpringFloor");
		RECT rect = { 0, 0, texture->GetWidth() * toolTextureSize, texture->GetHeight() * toolTextureSize };
		AdjustWindowRect(&rect , WS_OVERLAPPEDWINDOW , false);

		UINT toolWidth = rect.right - rect.left;
		UINT toolHeight = rect.bottom - rect.top;

		SetWindowPos(toolHwnd , nullptr , 672 , 100 , toolWidth , toolHeight , 0);
		ShowWindow(toolHwnd , true);
		UpdateWindow(toolHwnd);
	}

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd , UINT message , WPARAM wParam , LPARAM lParam)
{
	switch ( message )
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch ( wmId )
		{
		case IDM_ABOUT:
			DialogBox(hInst , MAKEINTRESOURCE(IDD_ABOUTBOX) , hWnd , About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd , message , wParam , lParam);
		}
	}
	break;
	case WM_KEYDOWN:
	{

	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd , &ps);
		EndPaint(hWnd , &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd , message , wParam , lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg , UINT message , WPARAM wParam , LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch ( message )
	{
	case WM_INITDIALOG:
		return ( INT_PTR ) TRUE;

	case WM_COMMAND:
		if ( LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL )
		{
			EndDialog(hDlg , LOWORD(wParam));
			return ( INT_PTR ) TRUE;
		}
		break;
	}
	return ( INT_PTR ) FALSE;
}
