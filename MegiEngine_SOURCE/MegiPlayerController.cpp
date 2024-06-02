#include "MegiPlayerController.h"

#include "MegiGameObject.h"
#include "MegiInput.h"
#include "MegiTime.h"
#include "MegiTransform.h"
#include "MegiAnimator.h"
#include "MegiApplication.h"
#include "MegiMoveToMousePos.h"
#include "MegiObject.h"
#include "MegiResources.h"

extern MegiEngine::Application application;

namespace MegiEngine
{
	PlayerController::PlayerController()
	: tr(nullptr)
	, speed(0)
	, mState(eState::Idle)
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
		case eState::Idle:
			Idle();
			break;
		case eState::Walk:
			Move();
			break;
		case eState::GiveWater:
			GiveWater();
			break;
		case eState::Sleep:
			break;
		case eState::Attack:
			break;
		}
	}

	void PlayerController::AttackEffect()
	{
		GameObject* attackEffect = Object::Instantiate<GameObject>(LayerType::Particle);

		auto animator = attackEffect->AddComponent<Animator>();
		auto moveToPos = attackEffect->AddComponent<MoveToMousePos>();

		Vector2 clickDir = clickPos - GetOwner()->GetComponent<Transform>()->GetPosition();

		moveToPos->SetDestPos(clickDir);
		// moveToPos->SetRotation(clickDir);

		graphics::Texture* hitEffect = Resources::Find <graphics::Texture>(L"HitEffect");
		animator->CreateAnimation(
		L"Hit"
		, hitEffect
		, Vector2(0.0f , 0.0f)
		, Vector2(512.0f, 512.0f)
		, Vector2::Zero
		, 15
		, 0.1f);
		animator->GetCompleteEvent(L"Hit") =
			[attackEffect]()
			{
				Object::Destroy(attackEffect);
			};

		animator->PlayAnimation(L"Hit" , false);

		Transform* tr = attackEffect->GetComponent<Transform>();
		tr->SetScale(Vector2(0.2f , 0.2f));
		tr->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
	}

	void PlayerController::Idle()
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
		else if(Input::GetKeyDown(KeyCode::LMB))
		{
			mState = eState::GiveWater;
			mAnimator->PlayAnimation(L"FrontGiveWater", false);

			clickPos = Input::GetMousePosition();
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
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"Idle" , false);
			return;
		}

		if(tr != NULL)
		{
			auto res = tr->GetPosition() + (dir * speed * Time::DeltaTime());
			//if ( CheckPositionIsValid(res) )
				tr->SetPosition(res);
		}
	}

	void PlayerController::GiveWater()
	{
		if(mAnimator->IsCompleted())
		{
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"Idle", false);
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
