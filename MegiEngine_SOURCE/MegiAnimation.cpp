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

	HRESULT Animation::Save(const std::wstring& path)
	{
		return E_NOTIMPL;
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

	void Animation::Render()
	{
		if ( mTexture == nullptr ) return;
	}

	void Animation::CreateAnimation(const std::wstring& name , graphics::Texture* spriteSheet , Math::Vector2 leftTop , Math::Vector2 size , Math::Vector2 offset , UINT spriteLength , float duration)
	{
		SetName(name);
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

		Vector2 originSize = mAnimationSheet[ mIndex ].size;
		Vector2 transformScale = tr->GetScale();

		return Vector2(
			originSize.x * transformScale.x ,
			originSize.y * transformScale.y);
		;
	}
}
