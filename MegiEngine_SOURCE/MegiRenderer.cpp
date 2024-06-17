#include "MegiRenderer.h"

#include "MegiResources.h"
#include "MegiShader.h"

namespace MegiEngine::Renderer
{
	Camera* MainCamera = nullptr;

	std::vector<graphics::Vertex> vertexes = {};
	graphics::VertexBuffer vertexBuffer;

	std::vector<UINT> indices;
	graphics::IndexBuffer indexBuffer;

	graphics::ConstantBuffer constantBuffers[ ( UINT ) graphics::CBType::End ] = {};

	ID3D11InputLayout* inputLayouts = nullptr;

	void LoadTriangleMesh()
	{
		vertexes.resize(4);

		vertexes[ 0 ].pos = Vector3(-.5f , -.5f , 0.0f);
		vertexes[ 0 ].color = Vector4(0.0f , 1.0f , 0.0f , 1.0f);

		vertexes[ 1 ].pos = Vector3(-.5f , .5f , 0.0f);
		vertexes[ 1 ].color = Vector4(1.0f , 0.0f , 0.0f , 1.0f);

		vertexes[ 2 ].pos = Vector3(.5f , .5f , 0.0f);
		vertexes[ 2 ].color = Vector4(0.0f , 0.0f , 1.0f , 1.0f);

		vertexes[ 3 ].pos = Vector3(.5f , -.5f , 0.0f);
		vertexes[ 3 ].color = Vector4(0.0f , 0.0f , 1.0f , 1.0f);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);
	}

	void LoadMeshes()
	{
		LoadTriangleMesh();
	}

	void LoadShaders()
	{
		Resources::Load<graphics::Shader>(L"TriangleShader" , L"..\\Shaders_SOURCE\\Triangle");
	}

	void LoadConstantBuffers()
	{
		constantBuffers[ ( UINT ) graphics::CBType::Transform ].Create(graphics::CBType::Transform , sizeof(Vector4));
	}

	void Initialize()
	{
		LoadMeshes();
		LoadShaders();
		LoadConstantBuffers();
	}

	void Release()
	{
		inputLayouts->Release();
	}
}
