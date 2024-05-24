#pragma once
#include "CommonInclude.h"
#include "MegiComponent.h"

namespace MegiEngine
{
	class GameObject
	{
	public:
		enum class eState
		{
			Active,
			Paused,
			Dead,
			End
		};

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

		eState GetState() const { return mState; }
		void SetActive(bool flag)
		{
			if ( flag == true ) mState = eState::Active;
			if ( flag == false) mState = eState::Dead;
		}
		// FIXME Destroy로만 호출되야 하는데 흠..
		void Death() { mState = eState::Dead; }

	private:
		void InitializeTransform();

	private:
		eState mState;
		std::vector<Component*> mComponents;
	};
}

