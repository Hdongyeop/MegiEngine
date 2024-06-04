#pragma once
#include "MegiGameObject.h"

namespace MegiEngine
{
	class Tile : public GameObject
	{
	public:
		Tile();
		~Tile();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetIndexPosition(int x , int y);

	private:

	};
}
