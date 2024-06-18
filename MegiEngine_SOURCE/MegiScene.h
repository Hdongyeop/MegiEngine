#pragma once
#include "CommonInclude.h"
#include "MegiEntity.h"
#include "MegiEnums.h"
#include "MegiGameObject.h"
#include "MegiLayer.h"

namespace MegiEngine
{
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* const gameObject, const Type::LayerType type);
		void CreateLayers();
		Layer* GetLayer(Type::LayerType type);
		void EraseGameObject(GameObject* gameObject);

	private:
		std::vector<Layer*> mLayers;
	};

}

