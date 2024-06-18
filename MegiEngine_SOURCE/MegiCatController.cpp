#include "MegiCatController.h"
#include "MegiTransform.h"
#include "MegiAnimator.h"
#include "MegiApplication.h"
#include "MegiGameObject.h"
#include "MegiTime.h"

extern MegiEngine::Application application;

namespace MegiEngine
{
	CatController::CatController()
	: mState(eState::SitDown)
	, mAnimator(nullptr)
	, mTime(0.0f)
	, speed(50.0f)
	{
	}

	CatController::~CatController()
	{
	}

	void CatController::Initialize()
	{
		Script::Initialize();
	}

	void CatController::Update()
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
		case eState::LayDown:
			LayDown();
			break;
		case eState::Attack:
			break;
		default: 
			break;
		}
	}

	void CatController::LateUpdate()
	{
		Script::LateUpdate();
	}

	void CatController::Render()
	{
		Script::Render();
	}

	void CatController::SitDown()
	{
		mTime += Time::DeltaTime();

		if(mTime > 3.0f)
		{
			mState = eState::Walk;
			int dir = rand() % 4;
			mDirection = ( eDirection ) dir;
			PlayWalkAnimationByDirection(mDirection);
			mTime = 0.0f;
		}
	}

	void CatController::Move()
	{
		mTime += Time::DeltaTime();

		if(mTime > 2.0f)
		{
			int isLayDown = rand() % 2;
			if(isLayDown == 0)
			{
				mState = eState::LayDown;
				mAnimator->PlayAnimation(L"LayDown" , false);
			}
			else
			{
				mState = eState::SitDown;
				mAnimator->PlayAnimation(L"SitDown" , false);
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Translate(tr);
	}

	void CatController::LayDown()
	{
		mTime += Time::DeltaTime();

		if(mTime > 5.0f)
		{
			mState = eState::Walk;
			int dir = rand() % 4;
			mDirection = ( eDirection ) dir;
			PlayWalkAnimationByDirection(mDirection);
			mTime = 0.0f;
		}
	}

	void CatController::PlayWalkAnimationByDirection(eDirection dir)
	{
		switch (dir)
		{
		case eDirection::Left:
			mAnimator->PlayAnimation(L"LeftWalk" , true);
			break;
		case eDirection::Right:
			mAnimator->PlayAnimation(L"RightWalk" , true);
			break;
		case eDirection::Down:
			mAnimator->PlayAnimation(L"DownWalk" , true);
			break;
		case eDirection::Up:
			mAnimator->PlayAnimation(L"UpWalk" , true);
			break;
		default: 
			assert(false);
			break;
		}
	}

	void CatController::Translate(Transform* tr)
	{
		Vector2 dir = Vector2::Zero;

		switch (mDirection)
		{
		case eDirection::Left:
			dir.x -= 1;
			break;
		case eDirection::Right:
			dir.x += 1;
			break;
		case eDirection::Down:
			dir.y += 1;
			break;
		case eDirection::Up:
			dir.y -= 1;
			break;
		default:
			assert(false);
			break;
		}

		if(tr != NULL)
		{
			auto res = tr->GetPosition() + (dir * speed * Time::DeltaTime());
			if(CheckPositionIsValid(res))
				tr->SetPosition(res);
		}
	}

	bool CatController::CheckPositionIsValid(Vector2 pos)
	{
		int appWidth = application.GetWidth() - 50;
		int appHeight = application.GetHeight() - 50;

		if ( pos.x < 0 || pos.x > appWidth ) return false;
		if ( pos.y < 0 || pos.y > appHeight ) return false;

		return true;
	}
}
