#include "MegiToolScene.h"

#include "MegiCameraMovement.h"
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
		camera->AddComponent<CameraMovement>();
		Camera* cameraComp = camera->AddComponent<Camera>();
		MainCamera = cameraComp;

//		Tile* tile = Object::Instantiate<Tile>(Type::LayerType::Tile);
//		TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
//		tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));

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
			// 마우스 포지션은 카메라가 움직이면 움직이는 대로 같이 +- 된다.
			pos = MainCamera->CalculateTilePosition(pos);

			if(pos.x >= 0.0f && pos.y >= 0.0f)
			{
				int idxX = pos.x / TilemapRenderer::TileSize.x;
				int idxY = pos.y / TilemapRenderer::TileSize.y;

				Tile* tile = Object::Instantiate<Tile>(LayerType::Tile);
				TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
				tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));
				tmr->SetIndex(TilemapRenderer::SelectedIndex);
				tile->SetIndexPosition(idxX , idxY);
				mTiles.push_back(tile);
			}
			else
			{

			}

		}

		if ( Input::GetKeyDown(KeyCode::S) ) Save();
		if ( Input::GetKeyDown(KeyCode::L) ) Load();

	}

	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		for ( size_t i = 0; i < 50; i++ )
		{
			Vector2 pos = MainCamera->CalculatePosition(
			Vector2(TilemapRenderer::TileSize.x * i , 0.0f));

			MoveToEx(hdc , pos.x, 0 , NULL);
			LineTo(hdc , pos.x, 1000);
		}

		for ( size_t i = 0; i < 50; i++ )
		{
			Vector2 pos = MainCamera->CalculatePosition(
			Vector2(0.0f, TilemapRenderer::TileSize.y * i));

			MoveToEx(hdc , 0 , pos.y, NULL);
			LineTo(hdc , 1000 , pos.y);
		}

		wchar_t str[ 50 ] = L"Tool Scene";
		int len = wcsnlen_s(str , 50);
		TextOut(hdc , 0 , 0 , str , len);
	}

	void ToolScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void ToolScene::OnExit()
	{
		Scene::OnExit();
	}

	void ToolScene::Save()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[ 256 ] = {};

		ZeroMemory(&ofn , sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[ 0 ] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if ( false == GetSaveFileName(&ofn) ) return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile , szFilePath , L"wb");

		for ( auto tile : mTiles )
		{
			TilemapRenderer* tmr = tile->GetComponent<TilemapRenderer>();
			Transform* tr = tile->GetComponent<Transform>();

			Vector2 sourceIndex = tmr->GetIndex();
			Vector2 position = tr->GetPosition();

			int x = sourceIndex.x;
			fwrite(&x , sizeof(int) , 1 , pFile);
			int y = sourceIndex.y;
			fwrite(&y , sizeof(int) , 1 , pFile);

			x = position.x;
			fwrite(&x , sizeof(int) , 1 , pFile);
			y = position.y;
			fwrite(&y , sizeof(int) , 1 , pFile);
		}

		fclose(pFile);
	}

	void ToolScene::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[ 256 ] = {};

		ZeroMemory(&ofn , sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[ 0 ] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if ( false == GetOpenFileName(&ofn) )
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile , szFilePath , L"rb");

		while ( true )
		{
			int idxX = 0;
			int idxY = 0;

			int posX = 0;
			int posY = 0;


			if ( fread(&idxX , sizeof(int) , 1 , pFile) == NULL )
				break;
			if ( fread(&idxY , sizeof(int) , 1 , pFile) == NULL )
				break;
			if ( fread(&posX , sizeof(int) , 1 , pFile) == NULL )
				break;
			if ( fread(&posY , sizeof(int) , 1 , pFile) == NULL )
				break;

			Tile* tile = Object::Instantiate<Tile>(LayerType::Tile , Vector2(posX , posY));
			TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
			tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));
			tmr->SetIndex(Vector2(idxX , idxY));

			mTiles.push_back(tile);
		}

		fclose(pFile);
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
