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
		const std::vector<GameObject*>& lefts = scene->GetLayer(left)->GetGameObjects();
		const std::vector<GameObject*>& rights = scene->GetLayer(right)->GetGameObjects();

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

		// AABB 충돌 체크
		if(fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
			&& fabs(leftPos.y - rightPos.y) < fabs((leftSize.y / 2.0f + rightSize.y / 2.0f)))
		{
			return true;
		}

		return false;
	}
}
