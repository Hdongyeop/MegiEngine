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
		virtual void Render(HDC hdc);

		void SetOwner(GameObject* owner)
		{
			mOwner = owner;
		}
		GameObject* GetOwner() { return mOwner; }
		Type::ComponentType GetComponentType() { return mType; }

	private:
		GameObject* mOwner;
		Type::ComponentType mType;
	};


}
