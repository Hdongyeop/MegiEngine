#pragma once
#include "MegiAnimation.h"
#include "MegiComponent.h"
#include "MegiTexture.h"

namespace MegiEngine
{
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name
		, graphics::Texture* spriteSheet
		, Math::Vector2 leftTop
		, Math::Vector2 size
		, Math::Vector2 offset
		, UINT spriteLength
		, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name , bool loop = true);
		Math::Vector2 GetSizeOfSprite();

	private:
		std::map<std::wstring , Animation*> mAnimations;
		Animation* mActiveAnimation;
		bool mLoop;
	};
}
