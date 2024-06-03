#include "MegiCollisionManager.h"

#include "MegiScene.h"
#include "MegiSceneManager.h"

namespace MegiEngine
{
	std::bitset<( UINT ) LayerType::MAX> CollisionManager::mCollisionLayerMatrix[(UINT)LayerType::MAX] = {};

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
		// 충돌 여부 체크
		int a = 0;
	}
}
