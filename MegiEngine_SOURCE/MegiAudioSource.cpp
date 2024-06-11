#include "MegiAudioSource.h"

#include "MegiGameObject.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	AudioSource::AudioSource()
	: Component(ComponentType::AudioSource)
	, mAudioClip(nullptr)
	{
	}

	AudioSource::~AudioSource()
	{
	}

	void AudioSource::Initialize()
	{
		Component::Initialize();
	}

	void AudioSource::Update()
	{
		Component::Update();
	}

	void AudioSource::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent < Transform >();
		Vector2 pos = tr->GetPosition();

		mAudioClip->Set3DAttributes(pos);
	}

	void AudioSource::Render(HDC hdc)
	{
		Component::Render(hdc);
	}

	void AudioSource::Play()
	{
		if ( mAudioClip == nullptr ) return;
		mAudioClip->Play();
	}

	void AudioSource::Stop()
	{
		if ( mAudioClip == nullptr ) return;
		mAudioClip->Stop();
	}

	void AudioSource::SetLoop(bool loop)
	{
		if ( mAudioClip == nullptr ) return;
		mAudioClip->SetLoop(loop);
	}
}
