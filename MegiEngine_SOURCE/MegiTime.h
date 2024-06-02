#pragma once
#include "CommonInclude.h"

namespace MegiEngine
{
	class Time
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		__forceinline static float DeltaTime() { return DeltaTimeValue; }
	private:
		// CPU가 1초에 몇 번 진동하는지 
		static LARGE_INTEGER CpuFrequency;
		static LARGE_INTEGER PrevFrequency;
		static LARGE_INTEGER CurrentFrequency;
		static float DeltaTimeValue; // 한 프레임에 걸리는 시간
	};
}
