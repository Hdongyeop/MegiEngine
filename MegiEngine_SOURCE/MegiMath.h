#pragma once
#include <cmath>

namespace MegiEngine::Math
{
#define PI 3.141592f

	static float ConvertDegree(float radian)
	{
		return ( radian * ( 180 / PI ) );
	}

	struct Vector2
	{
		static Vector2 Rotate(Vector2 vector, float degree)
		{
			float radian = ( degree / 180.0f ) * PI;
			vector.Normalize();

			float x = cosf(radian) * vector.x - sinf(radian) * vector.y;
			float y = sinf(radian) * vector.x + cosf(radian) * vector.y;

			return Vector2(x , y);
		}

		static float Dot(Vector2& v1, Vector2& v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		static float Cross(Vector2 v1, Vector2 v2)
		{
			return v1.x * v2.y - v1.y * v2.x;
		}

		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Left;
		static Vector2 Up;
		static Vector2 Down;

		float x;
		float y;

		Vector2() : x(0.0f), y(0.0f)
		{
			
		}

		Vector2(float _x , float _y) : x(_x) , y(_y)
		{
			
		}

		void Clear()
		{
			x = 0.0f;
			y = 0.0f;
		}

		float Length()
		{
			return sqrtf(x * x + y * y);
		}

		Vector2 Normalize()
		{
			float len = Length();
			x /= len;
			y /= len;

			return *this;
		}

		Vector2 operator+(const Vector2& other) const
		{
			return Vector2(x + other.x , y + other.y);
		}

		void operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;
		}

		Vector2 operator-(const Vector2& other) const
		{
			return Vector2(x - other.x , y - other.y);
		}

		Vector2 operator/(float value) const
		{
			return Vector2(x / value , y / value);
		}

		Vector2 operator*(float value) const
		{
			return Vector2(x * value , y * value);
		}

		Vector2 operator*(Vector2 v) const
		{
			return Vector2(x * v.x , y * v.y);
		}

		bool operator==(Vector2 other) const
		{
			return areFloatsEqual(x, other.x) && areFloatsEqual(y, other.y);
		}

	private:
		bool areFloatsEqual(float a, float b, float epsilon = 1e-10f) const
		{
			return std::abs(a - b) < epsilon;
		}
	};

}
