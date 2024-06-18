#include "MegiInput.h"

#include "MegiApplication.h"

extern MegiEngine::Application application;

namespace MegiEngine
{
	std::vector<Input::Key> Input::mKeys = { };
	Math::Vector2 Input::mMousePosition = Math::Vector2::One;

	int ASCII[(UINT)KeyCode::END] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP, VK_SPACE,
		VK_LBUTTON, VK_MBUTTON, VK_RBUTTON,
	};

	void Input::Initialize()
	{
		RegisterKeys();
	}

	void Input::Update()
	{
		UpdateKeys();
	}

	void Input::RegisterKeys()
	{
		mKeys.resize((UINT)KeyCode::END);

		for (size_t i = 0; i < (UINT)KeyCode::END; i++)
		{
			Key key = {(KeyCode)i, KeyState::None, false };
			mKeys[i] = key;
		}
	}

	void Input::UpdateKeys()
	{
		for (Key& key : mKeys)
		{
			UpdateKey(key);
		}
	}

	void Input::UpdateKey(Key& key)
	{
		if ( GetFocus() )
		{
			if ( IsKeyDown(key.keyCode) )
				UpdateKeyDown(key);
			else
				UpdateKeyUp(key);

			GetMousePositionByWindow();
		}
		else ClearKeys();
	}

	bool Input::IsKeyDown(KeyCode keyCode)
	{
		return GetAsyncKeyState(ASCII[ ( UINT ) keyCode ]) & 0x8000;
	}

	void Input::UpdateKeyDown(Key& key)
	{
		if ( key.pressed == true ) key.state = KeyState::Press;
		else key.state = KeyState::Down;

		key.pressed = true;
	}

	void Input::UpdateKeyUp(Key& key)
	{
		if ( key.pressed == true ) key.state = KeyState::Up;
		else key.state = KeyState::None;

		key.pressed = false;
	}

	void Input::GetMousePositionByWindow()
	{
		POINT mousePos = {};
		GetCursorPos(&mousePos);
		ScreenToClient(application.GetHwnd() , &mousePos);

		UINT width = application.GetWidth();
		UINT height = application.GetHeight();

		mMousePosition.x = -1.0f;
		mMousePosition.y = -1.0f;

		if ( CAST_UINT(mousePos.x) > 0 && CAST_UINT(mousePos.x) < width )
			mMousePosition.x = CAST_FLOAT(mousePos.x);
		if ( CAST_UINT(mousePos.y) > 0 && CAST_UINT(mousePos.y) < height )
			mMousePosition.y = CAST_FLOAT(mousePos.y);
	}

	void Input::ClearKeys()
	{
		for(Key& key : mKeys)
		{
			if ( key.state == KeyState::Down || key.state == KeyState::Press )
				key.state = KeyState::Up;
			else if ( key.state == KeyState::Up )
				key.state = KeyState::None;

			key.pressed = false;
		}
	}
}

