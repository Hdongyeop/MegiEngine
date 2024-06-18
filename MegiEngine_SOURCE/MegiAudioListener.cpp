#include "MegiAudioListener.h"

#include "MegiFmod.h"
#include "MegiGameObject.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	AudioListener::AudioListener()
	: Component(Type::ComponentType::AudioListener)
	{
	}

	AudioListener::~AudioListener()
	{
	}

	void AudioListener::Initialize()
	{
		Component::Initialize();
	}

	void AudioListener::Update()
	{
		Component::Update();
	}

	void AudioListener::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos;
		Fmod::Set3DListenerAttributes(pos);
	}

	void AudioListener::Render()
	{
	}
}
