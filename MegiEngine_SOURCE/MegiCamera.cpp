#include "MegiCamera.h"

#include "MegiApplication.h"
#include "MegiGameObject.h"
#include "MegiTransform.h"

extern MegiEngine::Application application;

namespace MegiEngine
{
	Camera::Camera()
	: Component(Type::ComponentType::Camera)
	, mDistance(Vector2::Zero)
	, mResolution(Vector2::Zero)
	, mLookPosition(Vector2::Zero)
	, mTarget(nullptr)
	{

	}

	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
	}

	void Camera::Update()
	{
		if(mTarget)
		{
			Transform* tr = mTarget->GetComponent<Transform>();
			mLookPosition = tr->GetPosition();
		}
		else
		{
			Transform* cameraTr = GetOwner()->GetComponent<Transform>();
			mLookPosition = cameraTr->GetPosition();
		}

		mDistance = mLookPosition - ( mResolution / 2.0f );
	}

	void Camera::LateUpdate()
	{
		Component::LateUpdate();
	}

	void Camera::Render(HDC hdc)
	{
		Component::Render(hdc);
	}
}
