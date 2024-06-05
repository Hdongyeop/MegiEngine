#include "MegiCollisionManager.h"

#include "MegiScene.h"
#include "MegiSceneManager.h"
#include "MegiTransform.h"

namespace MegiEngine
{
	std::bitset<( UINT ) LayerType::MAX> CollisionManager::mCollisionLayerMatrix[(UINT)LayerType::MAX] = {};
	std::unordered_map<UINT64 , bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Scene* dontDestroyOnLoad = SceneManager::GetDontDestroyOnLoad();

		for (UINT row = 0; row < (UINT)LayerType::MAX; row++)
		{
			for (UINT col = 0; col < ( UINT ) LayerType::MAX; col++ )
			{
				if(mCollisionLayerMatrix[row][col] == true)
				{
					LayerCollision(scene , ( LayerType ) row , ( LayerType ) col);
				}
			}
		}
	}

	void CollisionManager::LateUpdate()
	{
	}

	void CollisionManager::Render(HDC hdc)
	{
	}

	void CollisionManager::Clear()
	{
		mCollisionMap.clear();
		mCollisionLayerMatrix->reset();
	}

	void CollisionManager::CollisionLayerCheck(LayerType left , LayerType right , bool enable)
	{
		int row = 0;
		int col = 0;

		if(left <= right)
		{
			row = ( UINT ) left;
			col = ( UINT ) right;
		}
		else
		{
			row = ( UINT ) right;
			col = ( UINT ) left;
		}

		mCollisionLayerMatrix[ row ][ col ] = enable;
	}

	void CollisionManager::LayerCollision(Scene* scene , LayerType left , LayerType right)
	{
		const std::vector<GameObject*>& lefts = SceneManager::GetGameObjects(left);
		const std::vector<GameObject*>& rights = SceneManager::GetGameObjects(right);

		for (GameObject* left : lefts)
		{
			if ( left->IsActive() == false ) continue;

			Collider* leftCol = left->GetComponent < Collider >();
			if ( leftCol == nullptr ) continue;

			for (GameObject* right : rights)
			{
				if ( right->IsActive() == false ) continue;

				Collider* rightCol = right->GetComponent<Collider>();
				if ( rightCol == nullptr ) continue;
				if ( left == right ) continue;

				ColliderCollision(leftCol , rightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* left , Collider* right)
	{
		// 두 충돌체 번호로 가져온 ID 확인하여 CollisionID 세팅
		CollisionID id = {};
		id.left = left->GetID();
		id.right = right->GetID();

		// 이전 충돌 정보를 검색한다.
		// 만약 충돌정보가 없는 상태라면 충돌 정보를 생성해준다.

		auto iter = mCollisionMap.find(id.id);
		if(iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id , false));
			iter = mCollisionMap.find(id.id);
		}

		// 충돌 체크를 해준다
		if ( Intersect(left, right))
		{
			// 처음 충돌 함
			if ( iter->second == false )
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else // 이미 충돌 중 이였음
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else // 충돌 안함
		{
			// 전에 충돌 중 이였음
			if(iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
		Vector2 rightPos = rightTr->GetPosition() + right->GetOffset();

		Vector2 leftSize = left->GetSize();
		Vector2 rightSize = right->GetSize();

		ColliderType leftType = left->GetColliderType();
		ColliderType rightType = right->GetColliderType();

		// AABB 충돌 체크
		if(leftType == ColliderType::Rect2D && rightType == ColliderType::Rect2D)
		{
			// rect - rect
			if ( fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
				&& fabs(leftPos.y - rightPos.y) < fabs(( leftSize.y / 2.0f + rightSize.y / 2.0f )) )
			{
				return true;
			}
		}

		if(leftType == ColliderType::Circle2D && rightType == ColliderType::Circle2D)
		{
			// circle - circle
			Vector2 leftCirclePos = leftPos + ( leftSize / 2.0f );
			Vector2 rightCirclePos = rightPos + ( rightSize / 2.0f );

			float distance = ( leftCirclePos - rightCirclePos ).Length();
			if(distance <= (leftSize.x / 2.0f + rightSize.x / 2.0f))
			{
				return true;
			}
		}

		if((leftType == ColliderType::Circle2D && rightType == ColliderType::Rect2D)
			|| (leftType == ColliderType::Rect2D && rightType == ColliderType::Circle2D))
		{
			// circle - rect
			Vector2 rectCenter = leftType == ColliderType::Circle2D ? rightPos : leftPos;
			Vector2 rectSize = leftType == ColliderType::Circle2D ? rightSize : leftSize;
			Vector2 circleCenter = leftType == ColliderType::Circle2D ? leftPos : rightPos;
			Vector2 circleSize = leftType == ColliderType::Circle2D	? leftSize : rightSize;

			UINT zone = GetRectZone(rectCenter , rectSize , circleCenter);
			switch (zone)
			{
			case 1:
			case 7:
			case 3:
			case 5:
				if ( fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
					&& fabs(leftPos.y - rightPos.y) < fabs(( leftSize.y / 2.0f + rightSize.y / 2.0f )) )
				{
					return true;
				}
				break;
			case 4:
				return true;
			default: // 모서리 영역
				Vector2 checkEdge;
				if ( zone == 0 ) checkEdge = Vector2(rectCenter.x - rectSize.x / 2.0f , rectCenter.y + rectSize.y / 2.0f);
				else if ( zone == 2 ) checkEdge = Vector2(rectCenter.x + rectSize.x / 2.0f , rectCenter.y + rectSize.y / 2.0f);
				else if ( zone == 8 ) checkEdge = Vector2(rectCenter.x - rectSize.x / 2.0f , rectCenter.y - rectSize.y / 2.0f);
				else if ( zone == 6 ) checkEdge = Vector2(rectCenter.x - rectSize.x / 2.0f , rectCenter.y - rectSize.y / 2.0f);

				// 모서리가 원의 내부에 있는지?
				float distance = ( checkEdge - circleCenter ).Length();
				if ( distance < circleSize.x / 2.0f )
					return true;
				break;
			}
		}

		return false;
	}

	// https://dolphin.ivyro.net/file/mathematics/tutorial07.html
	UINT CollisionManager::GetRectZone(Math::Vector2 rectPos , Math::Vector2 rectSize , Math::Vector2 circlePos)
	{
		UINT xZone = circlePos.x < ( rectPos.x - rectSize.x / 2.0f ) ? 0
			: circlePos.x >(rectPos.x + rectSize.x / 2.0f) ? 2 : 1;
		UINT yZone = circlePos.y < ( rectPos.y - rectSize.y / 2.0f ) ? 2
			: circlePos.y >(rectPos.y + rectSize.y / 2.0f) ? 0 : 1;

		UINT ret = xZone + 3 * yZone;
		return ret;
	}
}
