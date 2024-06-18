#pragma once

#include "MegiIndexBuffer.h"
#include "MegiVertexBuffer.h"
#include "MegiResource.h"

namespace MegiEngine
{
	class Mesh : public Resource
	{
	public:
		struct Data
		{
			Data();
			~Data();

			D3D11_PRIMITIVE_TOPOLOGY mTopology;
			std::vector<graphics::Vertex> vertices;
			std::vector<UINT> indices;
		};

		Mesh();
		~Mesh();

		HRESULT Save(const std::wstring& path) override;
		HRESULT Load(const std::wstring& path) override;

		bool CreateVB(const std::vector<graphics::Vertex>& vertices);
		bool CreateIB(const std::vector<UINT>& indices);
		void Bind();

	private:
		graphics::VertexBuffer mVB;
		graphics::IndexBuffer mIB;

		Data mData;
	};
}
