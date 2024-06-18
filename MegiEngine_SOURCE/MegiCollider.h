#pragma once
#include "MegiComponent.h"

namespace MegiEngine
{
	class Collider : public Component
	{
	public:
		Collider(Type::ColliderType type);
		~Collider();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		Math::Vector2 GetOffset() const { return mOffset; }
		void SetOffset(Math::Vector2 offset) { mOffset = offset; }
		UINT32 GetID() const { return mID; }
		Math::Vector2 GetSize() const { return mSize; }
		void SetSize(Math::Vector2 size) { mSize = size; }
		Type::ColliderType GetColliderType() const { return mType; }

	private:
		static UINT CollisionID;

		UINT32 mID;
		Math::Vector2 mOffset;
		Math::Vector2 mSize;
		Type::ColliderType mType;
	};


}
