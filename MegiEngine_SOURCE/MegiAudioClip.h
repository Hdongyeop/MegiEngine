#pragma once
#include "MegiResource.h"
#include "../External/Include/Fmod/fmod.hpp"

namespace MegiEngine
{
	class AudioClip : public Resource
	{
	public:
		AudioClip();
		virtual ~AudioClip();

		HRESULT Load(const std::wstring& path) override;

		void Play();
		void Stop();
		void Set3DAttributes(const Math::Vector3 pos);
		void SetLoop(bool loop) { mLoop = loop; }

	private:
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;
		float mMinDistance;
		float mMaxDistance;
		bool mLoop;
	};


}
