#include "MegiAnimator.h"

#include "MegiResources.h"

namespace MegiEngine
{
	Animator::Animator()
	: Component(ComponentType::Animator)
	, mAnimations{}
	, mEvents{}
	, mActiveAnimation(nullptr)
	, mLoop(false)
	{
	}

	Animator::~Animator()
	{
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		for(auto& iter : mEvents)
		{
			delete iter.second;
			iter.second = nullptr;
		}
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

			Events* events = FindEvents(mActiveAnimation->GetName());

			if(mActiveAnimation->IsComplete() == true)
			{
				if ( events ) events->completeEvent();
				if ( mLoop == true ) mActiveAnimation->Reset();
			}
		}
	}

	void Animator::LateUpdate()
	{
		Component::LateUpdate();
	}

	void Animator::Render()
	{
//		if ( mActiveAnimation )
//			mActiveAnimation->Render(hdc);
	}

	void Animator::CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet, Math::Vector2 leftTop,
		Math::Vector2 size, Math::Vector2 offset, UINT spriteLength, float duration)
	{
		Animation* animation = nullptr;
		animation = FindAnimation(name);

		if ( animation != nullptr ) return;

		animation = new Animation();
		animation->SetName(name);
		animation->CreateAnimation(name , spriteSheet , leftTop , size , offset , spriteLength , duration);
		animation->SetAnimator(this);
		mAnimations.insert(std::make_pair(name , animation));

		Events* events = new Events();
		mEvents.insert(std::make_pair(name , events));
	}

	void Animator::CreateAnimationByFolder(/*const std::wstring& name, const std::wstring& path, Math::Vector2 offset,
		float duration*/)
	{
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = mAnimations.find(name);
		if ( iter == mAnimations.end() )
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name , bool loop)
	{
		Animation* animation = FindAnimation(name);
		if ( animation == nullptr ) return;

		// 현재 애니메이션의 EndEvent 호출
		if ( mActiveAnimation )
		{
			Events* currentEvents = FindEvents(mActiveAnimation->GetName());

			if ( currentEvents ) currentEvents->endEvent();
		}

		// Play 하려는 애니메이션의 StartEvent 호출
		Events* nextEvents = FindEvents(animation->GetName());
		if ( nextEvents ) nextEvents->startEvent();

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mLoop = loop;
	}

	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		auto iter = mEvents.find(name);
		if ( iter == mEvents.end() ) return nullptr;

		return iter->second;
	}

	Math::Vector2 Animator::GetSizeOfSprite()
	{
		if ( mActiveAnimation != nullptr )
		{
			return mActiveAnimation->GetSizeOfSprite();
		}

		return Math::Vector2::One;
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);
		return events->startEvent.mEvent;
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);
		return events->completeEvent.mEvent;
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);
		return events->endEvent.mEvent;
	}
}
