#pragma once
#include "MegiGraphics.h"

namespace MegiEngine::graphics
{
	class ConstantBuffer : public GpuBuffer
	{
	public:
		ConstantBuffer();
		~ConstantBuffer();

		bool Create(CBType type , UINT size , void* data = NULL);

		void SetData(void* data);
		void Bind(ShaderStage stage);

	private:
		UINT mSize;
		CBType mType;
	};

}

