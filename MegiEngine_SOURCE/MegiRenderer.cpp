#include "MegiRenderer.h"

#include "MegiResources.h"
#include "MegiShader.h"

namespace MegiEngine::Renderer
{
	Camera* MainCamera = nullptr;

	std::vector<graphics::Vertex> vertexes = {};
	std::vector<UINT> indices;

	Mesh* mesh = nullptr;

	graphics::ConstantBuffer constantBuffers[ ( UINT ) graphics::CBType::End ] = {};

	ID3D11InputLayout* inputLayouts = nullptr;

	void LoadTriangleMesh()
	{
		mesh = new Mesh();

		vertexes.resize(3);

		vertexes[ 0 ].pos = Vector3(-.5f , -.5f , 0.0f);
		vertexes[ 0 ].color = Vector4(0.0f , 1.0f , 0.0f , 1.0f);

		vertexes[ 1 ].pos = Vector3(-.5f , .5f , 0.0f);
		vertexes[ 1 ].color = Vector4(1.0f , 0.0f , 0.0f , 1.0f);

		vertexes[ 2 ].pos = Vector3(.5f , .5f , 0.0f);
		vertexes[ 2 ].color = Vector4(0.0f , 0.0f , 1.0f , 1.0f);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);
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
		constantBuffers[ CAST_UINT(graphics::CBType::Transform) ].Create(graphics::CBType::Transform , sizeof(Vector4));
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
		delete mesh;
	}
}
