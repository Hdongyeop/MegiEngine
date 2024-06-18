#include "MegiWillBeDestroied.h"

#include "MegiObject.h"
#include "MegiTime.h"

namespace MegiEngine
{
	WillBeDestroied::WillBeDestroied(float time)
	: Component(Type::ComponentType::Script)
	, mTime(0.0f)
	, mLimitTime(time)
	{
	}

	WillBeDestroied::~WillBeDestroied()
	{
	}

	void WillBeDestroied::Initialize()
	{
		Component::Initialize();
	}

	void WillBeDestroied::Update()
	{
		mTime += Time::DeltaTime();
		if(mTime > mLimitTime)
		{
			Object::Destroy(GetOwner());
		}
	}

	void WillBeDestroied::LateUpdate()
	{
		Component::LateUpdate();
	}

	void WillBeDestroied::Render()
	{
		Component::Render();
	}
}
