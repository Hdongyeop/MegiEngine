#include "MegiVertexBuffer.h"

namespace MegiEngine::graphics
{
	VertexBuffer::VertexBuffer()
	{
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	bool VertexBuffer::Create(const std::vector<Vertex>& vertexes)
	{
		desc.ByteWidth = sizeof(Vertex) * vertexes.size();
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sub = {};
		sub.pSysMem = vertexes.data();

		if ( !GetDevice()->CreateBuffer(&desc , &sub , buffer.GetAddressOf()) )
			assert(NULL && "Create vertex buffer failed!");

		return true;
	}

	void VertexBuffer::Bind()
	{
		UINT offset = 0;
		UINT vertexSize = sizeof(Vertex);
		GetDevice()->BindVertexBuffer(0 , 1 , buffer.GetAddressOf() , &vertexSize , &offset);
	}
}
