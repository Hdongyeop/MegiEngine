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
		virtual void Destroy();

		void AddGameObject(GameObject* gameObject);
		std::vector<GameObject*> GetGameObjects() const { return mGameObjects; }

	private:
		void FindDeadGameObjects(OUT std::vector<GameObject*>& gameObjs);
		void DeleteGameObjects(std::vector<GameObject*> gameObjs);
		void eraseGameObject();

	private:
		// Type::LayerType mType;
		std::vector<GameObject*> mGameObjects;
	};


}
