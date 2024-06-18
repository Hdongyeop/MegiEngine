#include "MegiRigidbody.h"

#include "MegiGameObject.h"
#include "MegiTime.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	Rigidbody::Rigidbody()
	: Component(Type::ComponentType::Rigidbody)
	, applyGravity(true)
	, mGround(false)
	, mMass(1.0f)
	, mFriction(10.0f)
	, mForce(Math::Vector2::Zero)
	, mVelocity(Math::Vector2::Zero)
	, mGravity(Vector2(0.0f, 800.0f))
	, mAccelation(Math::Vector2::Zero)
	, mLimitedVelocity(200.0f, 1000.0f)
	{
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initialize()
	{
		Component::Initialize();
	}

	void Rigidbody::Update()
	{
		// F = ma
		// a = F / m
		mAccelation = mForce / mMass;

		// 속도에 가속도를 더한다.
		mVelocity += mAccelation * Time::DeltaTime();

		if(applyGravity)
		{
			if ( mGround )
			{
				// 땅 위에 있을 때
				Vector2 gravity = mGravity;
				gravity.Normalize();

				float dot = mVelocity.Dot(gravity);
				mVelocity -= gravity * dot;
			}
			else
			{
				// 공중에 떠 있을 때
				mVelocity += mGravity * Time::DeltaTime();
			}

			// 최대 속도 제한
			Vector2 gravity = mGravity;
			gravity.Normalize();
			float dot = mVelocity.Dot(gravity);
			gravity *= dot;

			Vector2 sideVelocity = mVelocity - gravity;
			if ( mLimitedVelocity.y < gravity.Length() )
			{
				gravity.Normalize();
				gravity *= mLimitedVelocity.y;
			}

			if ( mLimitedVelocity.x < sideVelocity.Length() )
			{
				sideVelocity.Normalize();
				sideVelocity *= mLimitedVelocity.x;
			}

			mVelocity = gravity + sideVelocity;
		}

		if ( mVelocity != Math::Vector2::Zero )
		{
			// 속도에 반대 방향으로 마찰력 작용
			Math::Vector2 friction = -mVelocity;
			friction.Normalize();
			friction = friction * mFriction * mMass * Time::DeltaTime();

			// 마찰력으로 인한 속도 감소량이 현재 속도보다 큰 경우
			if ( mVelocity.Length() <= friction.Length() )
			{
				mVelocity = Math::Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();
		tr->SetPosition(pos);

		mForce = Vector2::Zero;
	}

	void Rigidbody::LateUpdate()
	{
		Component::LateUpdate();
	}

	void Rigidbody::Render()
	{
	}
}
