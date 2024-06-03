#pragma once
#include "MegiComponent.h"

namespace MegiEngine
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		Math::Vector2 GetOffset() { return mOffset; }
		void SetOffset(Math::Vector2 offset) { mOffset = offset; }
		UINT32 GetID() { return mID; }
		Math::Vector2 GetSize() { return mSize; }
		void SetSize(Math::Vector2 size) { mSize = size; }

	private:
		static UINT CollisionID;

		UINT32 mID;
		Math::Vector2 mOffset;
		Math::Vector2 mSize;
	};


}
