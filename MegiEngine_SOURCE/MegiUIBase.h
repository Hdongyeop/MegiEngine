#pragma once
#include "MegiEntity.h"

namespace MegiEngine
{
	using namespace Type;
	class UIBase : public Entity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}

			void operator()()
			{
				if ( mEvent ) mEvent();
			}

			std::function<void()> mEvent;
		};

		UIBase(UIType type);
		virtual ~UIBase();

		// ui가 로드 되었을 때 초기화 해주는 함수
		void Initialize();
		// ui가 활성화 되면 호출되는 함수
		void Active();
		// ui가 비활성화 되면 호출되는 함수
		void InActive();
		void Update();
		void LateUpdate();
		void Render();
		// ui가 사라질 때 호출되는 함수
		void UIClear();

		virtual void OnInit();
		virtual void OnActive();
		virtual void OnInActive();
		virtual void OnUpdate();
		virtual void OnLateUpdate();
		virtual void OnRender();
		virtual void OnClear();

		UIType GetType() const { return mType; }
		void SetType(UIType type) { mType = type; }
		void SetFullScreen(bool enable) { mFullScreen = enable; }
		bool IsFullScreen() { return mFullScreen; }
		Math::Vector2 GetPos() { return mPosition; }
		void SetPos(Math::Vector2 position) { mPosition = position; }
		Math::Vector2 GetSize() { return mSize; }
		void SetSize(Math::Vector2 size) { mSize = size; }

	protected:
		Math::Vector2 mPosition;
		Math::Vector2 mSize;
		bool mMouseOn;

	private:
		UIType mType;
		bool mFullScreen;
		bool mEnabled;

		UIBase* mParent;
	};
}
