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

		void SetData(void* data) const;
		void Bind(ShaderStage stage) const;

	private:
		UINT mSize;
		CBType mType;
	};

}

