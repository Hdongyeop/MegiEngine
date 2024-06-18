#pragma once
#include "MegiTexture.h"
#include "MegiUIBase.h"

namespace MegiEngine
{
	class UIButton : public UIBase
	{
	public:
		UIButton();
		~UIButton();

		void OnInit() override;
		void OnActive() override;
		void OnInActive() override;
		void OnUpdate() override;
		void OnLateUpdate() override;
		void OnRender() override;
		void OnClear() override;

		virtual void ButtonClick();

	private:
		graphics::Texture* mTexture;
		Event mOnClick;
	};
}

