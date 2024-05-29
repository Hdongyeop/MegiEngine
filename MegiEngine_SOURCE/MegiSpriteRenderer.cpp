#include "MegiSpriteRenderer.h"

#include "MegiGameObject.h"
#include "MegiTransform.h"
#include "MegiRenderer.h"

namespace MegiEngine
{
	SpriteRenderer::SpriteRenderer()
	: Component(ComponentType::SpriteRenderer)
	, mTexture(nullptr)
	, mSize(Vector2::One)
	{

	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{
		Component::Initialize();
	}

	void SpriteRenderer::Update()
	{
		Component::Update();
	}

	void SpriteRenderer::LateUpdate()
	{
		Component::LateUpdate();
	}

	void SpriteRenderer::Render(HDC hdc)
	{
		if ( mTexture == nullptr ) assert(false);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		// 메인 카메라에 맞게 위치 변환
		pos = MainCamera->CalculatePosition(pos);

		float rotation = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		if(mTexture->GetTextureType() == graphics::Texture::TextureType::Bmp)
		{
			if(mTexture->HaveAlphaChannel())
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)	

				AlphaBlend(hdc
					, pos.x
					, pos.y
					, mTexture->GetWidth() * mSize.x * scale.x
					, mTexture->GetHeight() * mSize.y * scale.y
					, mTexture->GetHdc()
					, 0 , 0
					, mTexture->GetWidth()
					, mTexture->GetHeight()
					, func);
			}
			else
			{
				//https://blog.naver.com/power2845/50147965306
				TransparentBlt(hdc
					, pos.x 
					, pos.y
					, mTexture->GetWidth() * mSize.x * scale.x
					, mTexture->GetHeight() * mSize.y * scale.y
					, mTexture->GetHdc()
					, 0 , 0
					, mTexture->GetWidth()
					, mTexture->GetHeight()
					, RGB(255 , 0 , 255));
			}
		}
		else if(mTexture->GetTextureType() == graphics::Texture::TextureType::Png)
		{
			// 투명화 시킬 픽셀의 색 범위
			Gdiplus::ImageAttributes imgAtt = {};
			imgAtt.SetColorKey
			( Gdiplus::Color(200, 200, 200)
			, Gdiplus::Color(255 , 255 , 255));

			Gdiplus::Graphics graphics(hdc);

			graphics.TranslateTransform(pos.x , pos.y);
			graphics.RotateTransform(rotation);
			graphics.TranslateTransform(-pos.x , -pos.y);

			graphics.DrawImage(mTexture->GetImage()
			, Gdiplus::Rect
			(
				pos.x , pos.y
				, mTexture->GetWidth() * mSize.x * scale.x
				, mTexture->GetHeight() * mSize.y * scale.y
			)
			, 0 , 0
			, mTexture->GetWidth() , mTexture->GetHeight()
			, Gdiplus::UnitPixel
			, &imgAtt);
		}
	}
}
