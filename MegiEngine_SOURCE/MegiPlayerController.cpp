#include "MegiPlayerController.h"

#include "MegiGameObject.h"
#include "MegiInput.h"
#include "MegiTime.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	PlayerController::PlayerController() : tr(nullptr), speed(0)
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
		float dx = 0 , dy = 0;
		
		if(Input::GetKey(KeyCode::W))
		{
			dy -= speed * Time::DeltaTime();
		}
		if(Input::GetKey(KeyCode::S))
		{
			dy += speed * Time::DeltaTime();
		}
		if(Input::GetKey(KeyCode::A))
		{
			dx -= speed * Time::DeltaTime();
		}
		if(Input::GetKey(KeyCode::D))
		{
			dx += speed * Time::DeltaTime();
		}

		if(tr != NULL)
		{
			float resX = tr->GetPosition().x + dx;
			float resY = tr->GetPosition().y + dy;
			tr->SetPosition(resX , resY);
		}
	}

}
