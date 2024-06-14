#include "MegiRenderer.h"

#include "MegiResources.h"
#include "MegiShader.h"

namespace MegiEngine::Renderer
{
	Camera* MainCamera = nullptr;


	Vertex vertexes[ 4 ] = {};
	ID3D11Buffer* vertexBuffer = nullptr;

	std::vector<UINT> indices;
	ID3D11Buffer* indexBuffer = nullptr;

	ID3D11Buffer* constantBuffer = nullptr;

	ID3D11InputLayout* inputLayouts = nullptr;

	void LoadTriangleMesh()
	{
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

	void Initialize()
	{
		LoadMeshes();
		LoadShaders();
	}

	void Release()
	{
		vertexBuffer->Release();

		inputLayouts->Release();

		indexBuffer->Release();
		constantBuffer->Release();
	}
}
