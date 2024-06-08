#pragma once
#include "MegiTexture.h"
#include "MegiUIBase.h"

namespace MegiEngine
{
	class UIHUD : public UIBase
	{
	public:
		UIHUD();
		~UIHUD();

		void OnInit() override;
		void OnActive() override;
		void OnInActive() override;
		void OnUpdate() override;
		void OnLateUpdate() override;
		void OnRender(HDC hdc) override;
		void OnClear() override;

	private:
		graphics::Texture* mTexture;

	};


}
