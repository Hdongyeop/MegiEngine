#pragma once
#include "CommonInclude.h"
#include "MegiComponent.h"

namespace MegiEngine
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent()
		{
			T* component = new T();
			component->SetOwner(this);
			mComponents.push_back(component);

			return component;
		}

		template <typename T>
		T* GetComponent()
		{
			T* component = nullptr;
			for (auto _mComponent : mComponents)
			{
				component = dynamic_cast<T*>(_mComponent);
				if (component) break;
			}

			return component;
		}

	private:
		void InitializeTransform();
	private:
		std::vector<Component*> mComponents;
	};
}

