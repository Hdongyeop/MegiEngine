#include "MegiPlayerController.h"

#include "MegiGameObject.h"
#include "MegiInput.h"
#include "MegiTime.h"
#include "MegiTransform.h"
#include "MegiAnimator.h"
#include "MegiApplication.h"

extern MegiEngine::Application application;

namespace MegiEngine
{
	PlayerController::PlayerController()
	: tr(nullptr)
	, speed(0)
	, mState(eState::SitDown)
	, mAnimator(nullptr)
	{
	}

	PlayerController::~PlayerController()
	{
	}

	void PlayerController::Initialize()
	{
		tr = GetOwner()->GetComponent<Transform>();
		speed = 100;
	}

	void PlayerController::Update()
	{
		if(mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
		}

		switch (mState)
		{
		case eState::SitDown:
			SitDown();
			break;
		case eState::Walk:
			Move();
			break;
		case eState::Sleep:
			break;
		case eState::Attack:
			break;
		}
	}

	void PlayerController::SitDown()
	{
		if(Input::GetKeyDown(KeyCode::D))
		{
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"RightWalk");
		}
		else if(Input::GetKeyDown(KeyCode::A))
		{
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"LeftWalk");
		}
		else if(Input::GetKeyDown(KeyCode::W))
		{
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"UpWalk");
		}
		else if(Input::GetKeyDown(KeyCode::S))
		{
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"DownWalk");
		}
	}

	void PlayerController::Move()
	{
		Vector2 dir = Vector2::Zero;
		
		if(Input::GetKey(KeyCode::W))
		{
			dir.y -= 1;
		}
		else if(Input::GetKey(KeyCode::S))
		{
			dir.y += 1;
		}
		else if(Input::GetKey(KeyCode::A))
		{
			dir.x -= 1;
		}
		else if(Input::GetKey(KeyCode::D))
		{
			dir.x += 1;
		}

		if(Input::GetKeyUp(KeyCode::W) 
			|| Input::GetKeyUp(KeyCode::A) 
			||Input::GetKeyUp(KeyCode::S) 
			|| Input::GetKeyUp(KeyCode::D))
		{
			mState = eState::SitDown;
			mAnimator->PlayAnimation(L"SitDown" , false);
			return;
		}

		if(tr != NULL)
		{
			auto res = tr->GetPosition() + (dir * speed * Time::DeltaTime());
			if ( CheckPositionIsValid(res) )
				tr->SetPosition(res);
		}
	}

	bool PlayerController::CheckPositionIsValid(Vector2 pos)
	{
		int appWidth = 700; // application.GetWidth();
		int appHeight = 900; // application.GetHeight();

		Vector2 spriteSize = GetOwner()->GetComponent<Animator>()->GetSizeOfSprite();

		if ( pos.x < 0 || pos.x + spriteSize.x > appWidth ) return false;
		if ( pos.y < 0 || pos.y + spriteSize.y > appHeight ) return false;

		return true;
	}
}
