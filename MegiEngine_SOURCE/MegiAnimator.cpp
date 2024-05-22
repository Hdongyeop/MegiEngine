#include "MegiAnimator.h"

namespace MegiEngine
{
	Animator::Animator()
	: Component(ComponentType::Animator)
	, mAnimations{}
	, mActiveAnimation(nullptr)
	, mLoop(false)
	{
	}

	Animator::~Animator()
	{
	}

	void Animator::Initialize()
	{
		Component::Initialize();
	}

	void Animator::Update()
	{
		if(mActiveAnimation)
		{
			mActiveAnimation->Update();

			if(mActiveAnimation->IsComplete() == true && mLoop == true)
				mActiveAnimation->Reset();
		}
	}

	void Animator::LateUpdate()
	{
		Component::LateUpdate();
	}

	void Animator::Render(HDC hdc)
	{
		if ( mActiveAnimation )
			mActiveAnimation->Render(hdc);
	}

	void Animator::CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet, Math::Vector2 leftTop,
		Math::Vector2 size, Math::Vector2 offset, UINT spriteLength, float duration)
	{
		Animation* animation = nullptr;
		animation = FindAnimation(name);

		if ( animation != nullptr ) return;

		animation = new Animation();
		animation->CreateAnimation(name , spriteSheet , leftTop , size , offset , spriteLength , duration);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name , animation));
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = mAnimations.find(name);
		if ( iter == mAnimations.end() )
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if ( animation == nullptr ) return;

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mLoop = loop;
	}

	Math::Vector2 Animator::GetSizeOfSprite()
	{
		if(mActiveAnimation != nullptr)
		{
			return mActiveAnimation->GetSizeOfSprite();
		}

		return Math::Vector2::One;
	}
}
