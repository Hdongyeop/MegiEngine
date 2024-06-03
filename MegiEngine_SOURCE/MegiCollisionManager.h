#pragma once
#include "CommonInclude.h"
#include "MegiCollider.h"

namespace MegiEngine
{
	using namespace Type;

	union CollisionID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};

		UINT64 id;
	};

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
		static void LayerCollision(Scene* scene1, Scene* scene2 , LayerType left , LayerType right);
		// 충돌 여부를 확인해 Enter, Stay, Exit 콜백 함수를 호출하는 함수
		static void ColliderCollision(Collider* left , Collider* right);
		// AABB 방식으로 두 Collider가 충돌 하는지 체크하는 함수
		static bool Intersect(Collider* left , Collider* right);

	private:
		static UINT GetRectZone(Math::Vector2 rectPos , Math::Vector2 rectSize , Math::Vector2 circlePos);

	private:
		// Layer들 끼리 충돌 가능한지 써있는 마스킹
		static std::bitset<(UINT)LayerType::MAX> mCollisionLayerMatrix[(UINT)LayerType::MAX ];
		// 충돌 정보가 기록되는 Dict
		static std::unordered_map<UINT64 , bool> mCollisionMap;
	};
}
