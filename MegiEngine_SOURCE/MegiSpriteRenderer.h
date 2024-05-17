#pragma once

#include "MegiComponent.h"

namespace MegiEngine
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void ImageLoad(const std::wstring& path);
		
	private:
		Gdiplus::Image* mImage;
		UINT mWidth;
		UINT mHeight;

	};


}
