#pragma once
#include "CommonInclude.h"
namespace MegiEngine
{
	enum class KeyState
	{
		None,
		Down,
		Press,
		Up,
	};

	enum class KeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		Left, Right, Down, Up, SPACE,
		LMB, MMB, RMB,
		END,
	};

	class Input
	{
	public:
		struct Key
		{
			KeyCode keyCode;
			KeyState state;
			bool pressed;
		};

		static void Initialize();
		static void Update();

		static bool GetKeyDown(KeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state == KeyState::Down;
		}
		static bool GetKeyUp(KeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state == KeyState::Up;
		}
		static bool GetKey(KeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state == KeyState::Press;
		}
		static Math::Vector2 GetMousePosition() { return mMousePosition; }

	private:
		static void RegisterKeys();
		static void UpdateKeys();
		static void UpdateKey(Key& key);
		static bool IsKeyDown(KeyCode keyCode);
		static void UpdateKeyDown(Key& key);
		static void UpdateKeyUp(Key& key);
		static void GetMousePositionByWindow();
		static void ClearKeys();

	private:
		static std::vector<Key> mKeys;
		static Math::Vector2 mMousePosition;
	};
}

