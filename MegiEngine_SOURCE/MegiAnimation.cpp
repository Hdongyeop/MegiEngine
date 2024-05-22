#include "MegiAnimation.h"

#include "MegiAnimator.h"
#include "MegiGameObject.h"
#include "MegiRenderer.h"
#include "MegiTime.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	Animation::Animation()
		: Resource(ResourceType::Animation)
	, mAnimator(nullptr)
	, mTexture(nullptr)
	, mAnimationSheet{}
	, mIndex(-1)
	, mTime(0.0f)
	, mbComplete(false)
	{
	}

	Animation::~Animation()
	{
	}

	HRESULT Animation::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Animation::Update()
	{
		if ( mbComplete ) return;

		mTime += Time::DeltaTime();

		if(mAnimationSheet[mIndex].duration < mTime)
		{
			mTime = 0.0f;
			if ( mIndex < mAnimationSheet.size() - 1 )
				mIndex++;
			else
				mbComplete = true;
		}
	}

	void Animation::Render(HDC hdc)
	{
		// 알파블렌드를 쓰려면 해당 이미지에 알파 채널이 있어야 한다
		if ( mTexture == nullptr ) return;

		GameObject* gameObj = mAnimator->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();

		// SRT
		Vector2 scale = tr->GetScale();
		float rotation = tr->GetRotation();
		Vector2 pos = tr->GetPosition();

		// 카메라 기반 위치 조정
		if(MainCamera)
			pos = MainCamera->CalculatePosition(pos);

		// 현재 스프라이트 얻기
		Sprite sprite = mAnimationSheet[ mIndex ];

		// 이미지 타입별 처리
		auto type = mTexture->GetTextureType();
		if(type == graphics::Texture::TextureType::Bmp)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

			HDC imgHdc = mTexture->GetHdc();

			AlphaBlend(hdc
			, pos.x
			, pos.y
			, sprite.size.x * scale.x
			, sprite.size.y * scale.y
			, imgHdc
			, sprite.leftTop.x
			, sprite.leftTop.y
			, sprite.size.x
			, sprite.size.y
			, func);
		}
		else if ( type == graphics::Texture::TextureType::Png )
		{
			// 투명화 시킬 픽셀의 색 범위
			Gdiplus::ImageAttributes imgAtt = {};
			imgAtt.SetColorKey
			( Gdiplus::Color(0, 0, 0)
			, Gdiplus::Color(100, 100, 100));

			Gdiplus::Graphics graphics(hdc);

			graphics.TranslateTransform(pos.x , pos.y);
			graphics.RotateTransform(rotation);
			graphics.TranslateTransform(-pos.x , -pos.y);

			graphics.DrawImage(mTexture->GetImage()
			, Gdiplus::Rect
			(
				pos.x // - ( sprite.size.x / 2.0f )
				, pos.y // - ( sprite.size.y / 2.0f )
				, sprite.size.x * scale.x
				, sprite.size.y * scale.y
			)
			, sprite.leftTop.x
			, sprite.leftTop.y
			, sprite.size.x
			, sprite.size.y
			, Gdiplus::UnitPixel
			, &imgAtt);
		}

	}

	void Animation::CreateAnimation(const std::wstring& name , graphics::Texture* spriteSheet , Math::Vector2 leftTop , Math::Vector2 size , Math::Vector2 offset , UINT spriteLength , float duration)
	{
		mTexture = spriteSheet;
		for ( UINT i = 0; i < spriteLength; ++i )
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + ( size.x * i );
			sprite.leftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mAnimationSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}

	Math::Vector2 Animation::GetSizeOfSprite()
	{
		GameObject* gameObj = mAnimator->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();

		Vector2 originSize = mAnimationSheet[mIndex].size;
		Vector2 transformScale = tr->GetScale();

		return Vector2(
			originSize.x * transformScale.x ,
			originSize.y * transformScale.y);
;
	}
}
