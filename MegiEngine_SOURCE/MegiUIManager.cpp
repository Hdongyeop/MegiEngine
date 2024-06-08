#include "MegiUIManager.h"

#include "MegiUIButton.h"
#include "MegiUIHUD.h"

namespace MegiEngine
{
	std::unordered_map<UIType , UIBase*> UIManager::mUIs = {};
	std::stack<UIBase*> UIManager::mUIBases = {};
	std::queue<UIType> UIManager::mRequestUiQueue = {};
	UIBase* UIManager::mActiveUI = nullptr;

	void UIManager::Initialize()
	{
		// UI 객체 생성
		UIHUD* hud = new UIHUD();
		mUIs.insert(std::make_pair(UIType::HpBar , hud));

		UIButton* button = new UIButton();
		mUIs.insert(std::make_pair(UIType::Button , button));
	}

	void UIManager::OnLoad(UIType type)
	{
		std::unordered_map<UIType , UIBase*>::iterator iter = mUIs.find(type);
		if(iter == mUIs.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
	}

	void UIManager::Update()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if(uiBase)
			{
				uiBase->Update();
				uiBases.pop();
			}
		}

		if(mRequestUiQueue.size() > 0)
		{
			UIType requestUI = mRequestUiQueue.front();
			mRequestUiQueue.pop();
			OnLoad(requestUI);
		}
	}

	void UIManager::LateUpdate()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if(uiBase)
			{
				uiBase->LateUpdate();
				uiBases.pop();
			}
		}
	}

	void UIManager::Render(HDC hdc)
	{
		if ( mUIBases.size() <= 0 ) return;

		std::vector<UIBase*> buff;

		UIBase* uiBase = nullptr;

		while (mUIBases.size() > 0)
		{
			uiBase = mUIBases.top();
			mUIBases.pop();

			buff.push_back(uiBase);
		}

		std::reverse(buff.begin() , buff.end());

		for (UIBase* ui : buff)
		{
			ui->Render(hdc);
			mUIBases.push(ui);
		}
	}

	void UIManager::OnComplete(UIBase* addUI)
	{
		if ( addUI == nullptr ) return;

		addUI->Initialize();
		addUI->Active();
		addUI->Update();

		// 만약에 현재 추가된 UI가 전체 화면이라면
		// 전체화면인 UI 말고 나머지를 전부 비활성화
		if(addUI->IsFullScreen())
		{
			std::stack<UIBase*> uiBases = mUIBases;
			while (!uiBases.empty())
			{
				UIBase* uiBase = uiBases.top();
				uiBases.pop();
				if(uiBase)
				{
					uiBase->InActive();
				}
			}
		}

		mUIBases.push(addUI);
		mActiveUI = nullptr;
	}

	void UIManager::OnFail()
	{
		mActiveUI = nullptr;
	}

	void UIManager::Release()
	{
		for(auto iter : mUIs)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	void UIManager::Push(UIType type)
	{
		mRequestUiQueue.push(type);
	}

	void UIManager::Pop(UIType type)
	{
		if ( mUIBases.size() <= 0 ) return;

		std::stack<UIBase*> tempStack;

		UIBase* uiBase = nullptr;
		while (mUIBases.size() > 0)
		{
			uiBase = mUIBases.top();
			mUIBases.pop();

			if(uiBase->GetType() != type)
			{
				tempStack.push(uiBase);
				continue;
			}

			if(uiBase->IsFullScreen())
			{
				std::stack<UIBase*> uiBases = mUIBases;
				while (!uiBases.empty())
				{
					UIBase* uiBase = uiBases.top();
					uiBases.pop();
					if(uiBase)
					{
						uiBase->Active();
						break;
					}
				}
			}

			uiBase->UIClear();
		}

		while (tempStack.empty() == false)
		{
			uiBase = tempStack.top();
			tempStack.pop();
			mUIBases.push(uiBase);
		}
	}
}
