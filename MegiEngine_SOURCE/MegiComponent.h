#pragma once
#include "MegiEntity.h"

namespace MegiEngine
{
	class GameObject;
	class Component : public Entity
	{
	public:
		Component(Type::ComponentType type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetOwner(GameObject* owner) { mOwner = owner; }
		GameObject* GetOwner() const { return mOwner; }
		Type::ComponentType GetComponentType() const { return mType; }

	private:
		GameObject* mOwner;
		Type::ComponentType mType;
	};


}
