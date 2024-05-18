#pragma once

namespace MegiEngine
{
	struct Vector2
	{
		static Vector2 Zero;
		static Vector2 One;

		float x;
		float y;

		Vector2() : x(0.0f), y(0.0f)
		{
			
		}

		Vector2(float _x , float _y) : x(_x) , y(_y)
		{
			
		}
	};

}
