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
		virtual void Render(HDC hdc);

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* const gameObject, const LayerType type);
		void CreateLayers();
		Layer* GetLayer(LayerType type);

	private:
		std::vector<Layer*> mLayers;
	};

}

