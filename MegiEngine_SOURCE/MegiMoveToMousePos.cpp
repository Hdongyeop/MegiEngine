#include "MegiMoveToMousePos.h"

#include "MegiGameObject.h"
#include "MegiTime.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	MoveToMousePos::MoveToMousePos()
	: destPos(Math::Vector2::Zero)
	{
	}

	MoveToMousePos::~MoveToMousePos()
	{
	}

	void MoveToMousePos::Initialize()
	{
		Script::Initialize();
	}

	void MoveToMousePos::Update()
	{
		if ( destPos == Math::Vector2::Zero ) return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 destDir = destPos - tr->GetPosition();
		destDir.Normalize();

		Vector2 newPos = tr->GetPosition() + ( destDir * 100.0f * Time::DeltaTime() );
		tr->SetPosition(newPos);
	}

	void MoveToMousePos::LateUpdate()
	{
		Script::LateUpdate();
	}

	void MoveToMousePos::Render(HDC hdc)
	{
		Script::Render(hdc);
	}

	void MoveToMousePos::SetRotation(Math::Vector2 pos)
	{
		pos.Normalize();
		float cosTheta = Math::Vector2::Dot(pos , Math::Vector2::Up);
		float theTa = acosf(cosTheta);

		float degree = ConvertDegree(theTa);
		Vector2 res = Vector2::Rotate(Vector2::Up , ConvertDegree(theTa));

		GetOwner()->GetComponent<Transform>()->SetRotation(ConvertDegree(theTa));

	}
}
