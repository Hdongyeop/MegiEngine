#pragma once
#include "MegiGraphicDevice_DX11.h"

namespace MegiEngine::graphics
{
	class VertexBuffer : public GpuBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		bool Create(const std::vector<Vertex>& vertexes);
		void Bind();

	private:

	};

}

