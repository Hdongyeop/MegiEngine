#include "MegiToolScene.h"

#include "MegiInput.h"
#include "MegiObject.h"
#include "MegiResources.h"
#include "MegiTile.h"
#include "MegiTilemapRenderer.h"

extern UINT toolTextureSize;

namespace MegiEngine
{
	ToolScene::ToolScene()
	{
	}

	ToolScene::~ToolScene()
	{
	}

	void ToolScene::Initialize()
	{
		GameObject* camera = Object::Instantiate<GameObject>(Type::LayerType::None 
			, Vector2(358.0f , 469.5f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		MainCamera = cameraComp;

		Tile* tile = Object::Instantiate<Tile>(Type::LayerType::Tile);
		TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
		tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));

		Scene::Initialize();
	}

	void ToolScene::Update()
	{
		Scene::Update();
	}

	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();

		if(Input::GetKeyDown(KeyCode::LMB))
		{
			Vector2 pos = Input::GetMousePosition();

			int idxX = pos.x / TilemapRenderer::TileSize.x;
			int idxY = pos.y / TilemapRenderer::TileSize.y;

			Tile* tile = Object::Instantiate<Tile>(LayerType::Tile);
			TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
			tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));
			tmr->SetIndex(TilemapRenderer::SelectedIndex);
			tile->SetPosition(idxX , idxY);
		}
	}

	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		for (size_t i = 0; i < 50; i++)
		{
			MoveToEx(hdc , TilemapRenderer::TileSize.x * i , 0 , NULL);
			LineTo(hdc , TilemapRenderer::TileSize.x * i , 1000);
		}

		for (size_t i = 0; i < 50; i++)
		{
			MoveToEx(hdc , 0 , TilemapRenderer::TileSize.y * i , NULL);
			LineTo(hdc , 1000 , TilemapRenderer::TileSize.y * i);
		}

//		wchar_t str[ 50 ] = L"Tool Scene";
//		int len = wcsnlen_s(str, 50);
//		TextOut(hdc , 0 , 0 , str , len);
	}

	void ToolScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void ToolScene::OnExit()
	{
		Scene::OnExit();
	}
}

LRESULT CALLBACK WndTileProc(HWND hWnd , UINT message , WPARAM wParam , LPARAM lParam)
{
	switch ( message )
	{
	case WM_LBUTTONDOWN:
	{
		POINT mousePos = {};
		GetCursorPos(&mousePos);
		ScreenToClient(hWnd , &mousePos);

		MegiEngine::Vector2 mousePosition;
		mousePosition.x = mousePos.x;
		mousePosition.y = mousePos.y;

		int tileWidth = MegiEngine::TilemapRenderer::OriginTileSize.x * toolTextureSize;
		int tileHeight = MegiEngine::TilemapRenderer::OriginTileSize.y * toolTextureSize;
		int idxX = mousePosition.x / tileWidth;
		int idxY = mousePosition.y / tileHeight;

		MegiEngine::TilemapRenderer::SelectedIndex = MegiEngine::Vector2(idxX , idxY);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd , &ps);

		//Rectangle(hdc, 100, 100, 200, 200);
		MegiEngine::graphics::Texture* texture
			= MegiEngine::Resources::Find<MegiEngine::graphics::Texture>(L"SpringFloor");

		TransparentBlt(hdc
			, 0 , 0
			, texture->GetWidth() * toolTextureSize
			, texture->GetHeight() * toolTextureSize
			, texture->GetHdc()
			, 0 , 0
			, texture->GetWidth()
			, texture->GetHeight()
			, RGB(255 , 0 , 255));

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
