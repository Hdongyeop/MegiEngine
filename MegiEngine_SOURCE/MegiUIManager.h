#pragma once
#include "CommonInclude.h"

#include "MegiEnums.h"
#include "MegiUIBase.h"

namespace MegiEngine
{
	using namespace Type;
	class UIManager
	{
	public:
		static void Initialize();
		static void OnLoad(UIType type);
		static void Update();
		static void LateUpdate();
		static void Render();
		static void OnComplete(UIBase* addUI);
		static void OnFail();
		static void Release();

		static void Push(UIType type);
		static void Pop(UIType type);

	private:
		static std::unordered_map<UIType , UIBase*> mUIs;
		static std::stack<UIBase*> mUIBases;
		static std::queue<UIType> mRequestUiQueue;
		static UIBase* mActiveUI;
	};

}

