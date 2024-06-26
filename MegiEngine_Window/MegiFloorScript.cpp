#include "MegiFloorScript.h"

#include "MegiAudioSource.h"
#include "MegiCollider.h"
#include "MegiGameObject.h"
#include "MegiRigidbody.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	FloorScript::FloorScript()
	{
	}

	FloorScript::~FloorScript()
	{
	}

	void FloorScript::Initialize()
	{
		Script::Initialize();
	}

	void FloorScript::Update()
	{
		Script::Update();
	}

	void FloorScript::LateUpdate()
	{
		Script::LateUpdate();
	}

	void FloorScript::Render()
	{
		Script::Render();
	}

	void FloorScript::OnCollisionEnter(Collider* other)
	{
		Rigidbody* playerRB = other->GetOwner()->GetComponent<Rigidbody>();
		Transform* playerTR = other->GetOwner()->GetComponent<Transform>();
		Collider* playerCol = other;

		Rigidbody* floorRB = GetOwner()->GetComponent<Rigidbody>();
		Transform* floorTR = GetOwner()->GetComponent<Transform>();
		Collider* floorCol = GetOwner()->GetComponent<Collider>();

		float len = fabs(playerTR->GetPosition().y - floorTR->GetPosition().y);
		float scale = fabs(playerCol->GetSize().y / 2.0f - floorCol->GetSize().y / 2.0f);

		if(len < scale)
		{
			Vector2 playerPos = playerTR->GetPosition();
			playerPos.y -= ( scale - len ) - 1.0f;

			playerTR->SetPosition(playerPos);
		}

		AudioSource* as = GetOwner()->GetComponent<AudioSource>();
		as->Stop();
		as->SetLoop(false);
		as->Play();

		playerRB->SetGround(true);
	}

	void FloorScript::OnCollisionStay(Collider* other)
	{
		Script::OnCollisionStay(other);
	}

	void FloorScript::OnCollisionExit(Collider* other)
	{
		Script::OnCollisionExit(other);
	}
}
