#pragma once
#include "CommonInclude.h"
#include "MegiCollider.h"

namespace MegiEngine
{
	using namespace Type;
	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

		// left layer와 right layer가 충돌하게 할 것 인지 설정해주는 함수
		static void CollisionLayerCheck(LayerType left , LayerType right, bool enable);
		// left Layer와 right Layer에 있는 게임오브젝트들 중 Collider를 가지고
		// 있는 것들 끼리 충돌 함수를 호출 해주는 함수
		static void LayerCollision(class Scene* scene , LayerType left , LayerType right);
		// 두 Collider가 충돌인지 아닌지 체크하는 함수
		static void ColliderCollision(Collider* left , Collider* right);

	private:
		static std::bitset<(UINT)LayerType::MAX> mCollisionLayerMatrix[(UINT)LayerType::MAX ];
	};
}
