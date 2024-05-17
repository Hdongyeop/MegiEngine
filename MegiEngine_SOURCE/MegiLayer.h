#pragma once
#include "CommonInclude.h"
#include "MegiEntity.h"
#include "MegiGameObject.h"

namespace MegiEngine
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void AddGameObject(GameObject* gameObject);

	private:
		LayerType mType;
		std::vector<GameObject*> mGameObjects;
	};


}
