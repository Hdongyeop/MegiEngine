#include "MegiInput.h"

namespace MegiEngine
{
	std::vector<Input::Key> Input::mKeys = { };

	int ASCII[(UINT)KeyCode::END] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP, VK_SPACE,
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
		if (IsKeyDown(key.keyCode))
			UpdateKeyDown(key);
		else
			UpdateKeyUp(key);
	}

	bool Input::IsKeyDown(KeyCode keyCode)
	{
		return GetAsyncKeyState(ASCII[(UINT)keyCode]) & 0x8000;
	}

	void Input::UpdateKeyDown(Key& key)
	{
		if (key.pressed == true) key.state = KeyState::Press;
		else key.state = KeyState::Down;

		key.pressed = true;
	}

	void Input::UpdateKeyUp(Key& key)
	{
		if (key.pressed == true) key.state = KeyState::Up;
		else key.state = KeyState::None;

		key.pressed = false;
	}
}

