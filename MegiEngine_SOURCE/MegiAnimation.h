#pragma once
#include "MegiResource.h"
#include "MegiTexture.h"

namespace MegiEngine
{
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Math::Vector2 leftTop;
			Math::Vector2 size;
			Math::Vector2 offset;
			float duration;

			Sprite()
			: leftTop(Math::Vector2::Zero)
			, size(Math::Vector2::Zero)
			, offset(Math::Vector2::Zero)
			, duration(0.0f)
			{
				
			}
		};

		Animation();
		~Animation();

		HRESULT Load(const std::wstring& path) override;

		void Update();
		void Render(HDC hdc);

		void CreateAnimation(const std::wstring& name
		, graphics::Texture* spriteSheet
		, Math::Vector2 leftTop
		, Math::Vector2 size
		, Math::Vector2 offset
		, UINT spriteLength
		, float duration);

		void Reset();

		bool IsComplete() { return mbComplete; }
		void SetAnimator(class Animator* animator) { mAnimator = animator; }

		Math::Vector2 GetSizeOfSprite();
		
	private:
		class Animator* mAnimator;
		graphics::Texture* mTexture;

		std::vector<Sprite> mAnimationSheet;
		int mIndex;
		float mTime;
		bool mbComplete;
	};
}
