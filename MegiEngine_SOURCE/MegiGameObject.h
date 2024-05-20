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

		template <typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		T* AddComponent()
		{
			T* component = new T();
			component->SetOwner(this);
			mComponents[static_cast<UINT>(component->GetComponentType())] = component;

			return component;
		}

		template <typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
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

