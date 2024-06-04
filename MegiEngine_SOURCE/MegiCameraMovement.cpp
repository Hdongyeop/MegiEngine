#include "MegiCameraMovement.h"

#include "MegiGameObject.h"
#include "MegiInput.h"
#include "MegiTime.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	CameraMovement::CameraMovement()
	{
	}

	CameraMovement::~CameraMovement()
	{
	}

	void CameraMovement::Initialize()
	{
		Script::Initialize();
	}

	void CameraMovement::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if ( Input::GetKey(KeyCode::Right) )
		{
			pos.x += 100.0f * Time::DeltaTime();
		}
		if ( Input::GetKey(KeyCode::Left) )
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}
		if ( Input::GetKey(KeyCode::Up) )
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}
		if ( Input::GetKey(KeyCode::Down) )
		{
			pos.y += 100.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);


		Script::Update();
	}

	void CameraMovement::LateUpdate()
	{
		Script::LateUpdate();
	}

	void CameraMovement::Render(HDC hdc)
	{
		Script::Render(hdc);
	}
}
