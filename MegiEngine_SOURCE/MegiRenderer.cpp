#include "MegiRenderer.h"

#include "MegiResources.h"
#include "MegiShader.h"

namespace MegiEngine::Renderer
{
	Camera* MainCamera = nullptr;

	Mesh* mesh = nullptr;

	graphics::ConstantBuffer constantBuffers[ ( UINT ) graphics::CBType::End ] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[ ( UINT ) graphics::SamplerType::End ] = {};

	ID3D11InputLayout* inputLayouts = nullptr;

	void LoadStates()
	{
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		graphics::GetDevice()->CreateSamplerState(&samplerDesc , samplerStates[ ( UINT ) graphics::SamplerType::Anisotropic ].GetAddressOf());

		ZeroMemory(&samplerDesc , sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		graphics::GetDevice()->CreateSamplerState(&samplerDesc , samplerStates[ ( UINT ) graphics::SamplerType::Point ].GetAddressOf());

		ZeroMemory(&samplerDesc , sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		graphics::GetDevice()->CreateSamplerState(&samplerDesc , samplerStates[ ( UINT ) graphics::SamplerType::PostProcess].GetAddressOf());

		graphics::GetDevice()->BindSamplers(( UINT ) graphics::SamplerType::Anisotropic , 1 , samplerStates[ ( UINT ) graphics::SamplerType::Anisotropic ].GetAddressOf());
		graphics::GetDevice()->BindSamplers(( UINT ) graphics::SamplerType::Point, 1 , samplerStates[ ( UINT ) graphics::SamplerType::Point].GetAddressOf());
		graphics::GetDevice()->BindSamplers(( UINT ) graphics::SamplerType::PostProcess, 1 , samplerStates[ ( UINT ) graphics::SamplerType::PostProcess].GetAddressOf());

	}

	void LoadTriangleMesh()
	{
		mesh = new Mesh();

		std::vector<graphics::Vertex> vertexes = {};
		std::vector<UINT> indices = {};

		vertexes.resize(3);
		vertexes[ 0 ].pos = Vector3(0.0f , 0.5f , 0.0f);
		vertexes[ 0 ].color = Vector4(0.0f , 1.0f , 0.0f , 1.0f);

		vertexes[ 1 ].pos = Vector3(0.5f , -0.5f , 0.0f);
		vertexes[ 1 ].color = Vector4(1.0f , 0.0f , 0.0f , 1.0f);
		
		vertexes[ 2 ].pos = Vector3(-0.5f , -0.5f , 0.0f);
		vertexes[ 2 ].color = Vector4(0.0f , 0.0f , 1.0f , 1.0f);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);
	}

	void LoadRectMesh()
	{
		mesh = new Mesh();

		std::vector<graphics::Vertex> vertexes = {};
		std::vector<UINT> indices = {};

		vertexes.resize(4);
		vertexes[ 0 ].pos = Vector3(-0.5f , 0.5f , 0.0f);
		vertexes[ 0 ].color = Vector4(0.0f , 1.0f , 0.0f , 1.0f);
		vertexes[ 0 ].uv = Vector2(0.0f , 0.0f);

		vertexes[ 1 ].pos = Vector3(0.5f , 0.5f , 0.0f);
		vertexes[ 1 ].color = Vector4(1.0f , 0.0f , 0.0f , 1.0f);
		vertexes[ 1 ].uv = Vector2(1.0f , 0.0f);
		
		vertexes[ 2 ].pos = Vector3(0.5f , -0.5f , 0.0f);
		vertexes[ 2 ].color = Vector4(0.0f , 0.0f , 1.0f , 1.0f);
		vertexes[ 2 ].uv = Vector2(1.0f , 1.0f);

		vertexes[ 3 ].pos = Vector3(-0.5f , -0.5f , 0.0f);
		vertexes[ 3 ].color = Vector4(0.0f , 0.0f , 1.0f , 1.0f);
		vertexes[ 3 ].uv = Vector2(0.0f , 1.0f);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);
	}

	void LoadMeshes()
	{
		LoadTriangleMesh();
		LoadRectMesh();
	}

	void LoadShaders()
	{
		Resources::Load<graphics::Shader>(L"TriangleShader" , L"..\\Shaders_SOURCE\\Triangle");
		Resources::Load<graphics::Shader>(L"SpriteShader" , L"..\\Shaders_SOURCE\\Sprite");
	}

	void LoadConstantBuffers()
	{
		constantBuffers[ CAST_UINT(graphics::CBType::Transform) ].Create(graphics::CBType::Transform , sizeof(Vector4));
	}

	void Initialize()
	{
		LoadStates();
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
