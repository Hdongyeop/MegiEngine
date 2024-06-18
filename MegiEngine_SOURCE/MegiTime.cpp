#include "MegiTime.h"

#include "MegiApplication.h"

extern MegiEngine::Application application;

namespace MegiEngine
{
	LARGE_INTEGER Time::CpuFrequency = {};
	LARGE_INTEGER Time::PrevFrequency = {};
	LARGE_INTEGER Time::CurrentFrequency = {};
	float Time::DeltaTimeValue = 0.0f;

	void Time::Initialize()
	{
		// CPU 고유 진동수
		QueryPerformanceFrequency(&CpuFrequency);

		// 프로그램이 시작 했을 때 진동 수
		QueryPerformanceCounter(&PrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&CurrentFrequency);

		float differenceFrequency = 
			static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);

		DeltaTimeValue = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart);

		PrevFrequency = CurrentFrequency;
	}

	void Time::Render()
	{
//		static float time = 0.0f;
//
//		time += DeltaTimeValue;
//		float fps = 1.0f / DeltaTimeValue;
//
//		wchar_t str[50] = L"";
//		swprintf_s(str, 50, L"FPS: %d", (int)fps);
//		int len = wcsnlen_s(str, 50);
//
//		TextOut(hdc, application.GetWidth() - 100, 0, str, len);
	}
}
