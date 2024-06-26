#include "MegiConstantBuffer.h"

#include "MegiGraphicDevice_DX11.h"

namespace MegiEngine::graphics
{
	ConstantBuffer::ConstantBuffer()
	: mSize(0)
	, mType(CBType::None)
	{
	}

	ConstantBuffer::~ConstantBuffer()
	{
	}

	bool ConstantBuffer::Create(CBType type, UINT size, void* data)
	{
		mType = type;
		mSize = size;

		desc.ByteWidth = size;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sub = {};
		sub.pSysMem = data;

		bool success = false;
		if ( data == NULL ) success = GetDevice()->CreateBuffer(&desc , nullptr , buffer.GetAddressOf());
		else success = GetDevice()->CreateBuffer(&desc , &sub , buffer.GetAddressOf());

		if ( !success )
			assert(NULL /*, "Create constant buffer failed!"*/);

		return true;
	}

	void ConstantBuffer::SetData(void* data) const
	{
		GetDevice()->SetDataGpuBuffer(buffer.Get() , data , mSize);
	}

	void ConstantBuffer::Bind(ShaderStage stage) const
	{
		GetDevice()->BindConstantBuffer(stage , mType , buffer.Get());
	}
}
