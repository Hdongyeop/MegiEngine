#include "MegiGraphicDevice_DX11.h"
#include "MegiApplication.h"
#include "MegiRenderer.h"

extern MegiEngine::Application application;

namespace MegiEngine::graphics
{
	GraphicDevice_DX11::GraphicDevice_DX11()
	{
	}

	GraphicDevice_DX11::~GraphicDevice_DX11()
	{
	}

	void GraphicDevice_DX11::Initialize()
	{
#pragma region Device

		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
		//#if defined(DEBUG) || defined(_DEBUG)
		//		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
		//#endif

		HRESULT hr = D3D11CreateDevice(0 , D3D_DRIVER_TYPE_HARDWARE ,
			0 , creationFlags ,
			featureLevels , ARRAYSIZE(featureLevels) ,
			D3D11_SDK_VERSION , mDevice.GetAddressOf() ,
			0 , mContext.GetAddressOf());

#pragma endregion

#pragma region SwapChain

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.OutputWindow = application.GetHwnd();
		swapChainDesc.Windowed = true;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // 이전 프레임 장면을 유지하지 않는다
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 144;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		// 4X MSAA supported check
		UINT quality = 0;
		mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM , 4 , &quality);
		//		if ( quality > 0 )
		//		{
		//			swapChainDesc.SampleDesc.Count = 4;
		//			swapChainDesc.SampleDesc.Quality = quality - 1;
		//		}
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory = nullptr;

		if ( FAILED(mDevice->QueryInterface(__uuidof( IDXGIDevice ) , ( void** ) pDXGIDevice.GetAddressOf())) )
			return;

		if ( FAILED(pDXGIDevice->GetParent(__uuidof( IDXGIAdapter ) , ( void** ) pAdapter.GetAddressOf())) )
			return;

		if ( FAILED(pAdapter->GetParent(__uuidof( IDXGIFactory ) , ( void** ) pFactory.GetAddressOf())) )
			return;

		if ( FAILED(pFactory->CreateSwapChain(mDevice.Get() , &swapChainDesc , mSwapChain.GetAddressOf())) )
			return;

		mSwapChain->GetBuffer(0 , __uuidof( ID3D11Texture2D ) , ( void** ) mRenderTarget.GetAddressOf());
		mDevice->CreateRenderTargetView(mRenderTarget.Get() , nullptr , mRenderTargetView.GetAddressOf());

#pragma endregion

#pragma region DepthSencil

		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // Depth 24bit, Stencil 8bit
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.Width = application.GetWidth();
		depthStencilDesc.Height = application.GetHeight();
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;

		if ( FAILED(mDevice->CreateTexture2D(&depthStencilDesc , nullptr , mDepthStencil.GetAddressOf())) )
			return;

		if ( FAILED(mDevice->CreateDepthStencilView(mDepthStencil.Get() , nullptr , mDepthStencilView.GetAddressOf())) )
			return;

#pragma endregion

		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
		shaderFlags |= D3DCOMPILE_DEBUG;
		shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

#pragma region Vertex Shader
		{
			ID3DBlob* errorBlob = nullptr;
			D3DCompileFromFile(L"..\\Shaders_SOURCE\\TriangleVS.hlsl" , nullptr
			, D3D_COMPILE_STANDARD_FILE_INCLUDE , "main"
			, "vs_5_0" , shaderFlags , 0
			, &Renderer::vsBlob , &errorBlob);

			mDevice->CreateVertexShader(
			Renderer::vsBlob->GetBufferPointer()
			, Renderer::vsBlob->GetBufferSize()
			, nullptr , &Renderer::vsShader);
		}
#pragma endregion

#pragma region Pixel Shader
		{
			ID3DBlob* errorBlob = nullptr;
			D3DCompileFromFile(L"..\\Shaders_SOURCE\\TrianglePS.hlsl" , nullptr
			, D3D_COMPILE_STANDARD_FILE_INCLUDE , "main"
			, "ps_5_0" , shaderFlags , 0
			, &Renderer::psBlob , &errorBlob);

			mDevice->CreatePixelShader(
			Renderer::psBlob->GetBufferPointer()
			, Renderer::psBlob->GetBufferSize()
			, nullptr , &Renderer::psShader);
		}
#pragma endregion

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesces[ 2 ] = {};
		inputLayoutDesces[ 0 ].AlignedByteOffset = 0;
		inputLayoutDesces[ 0 ].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputLayoutDesces[ 0 ].InputSlot = 0;
		inputLayoutDesces[ 0 ].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[ 0 ].SemanticName = "POSITION";
		inputLayoutDesces[ 0 ].SemanticIndex = 0;

		inputLayoutDesces[ 1 ].AlignedByteOffset = 12;
		inputLayoutDesces[ 1 ].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputLayoutDesces[ 1 ].InputSlot = 0;
		inputLayoutDesces[ 1 ].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[ 1 ].SemanticName = "COLOR";
		inputLayoutDesces[ 1 ].SemanticIndex = 0;

		mDevice->CreateInputLayout(inputLayoutDesces , 2
		, Renderer::vsBlob->GetBufferPointer()
		, Renderer::vsBlob->GetBufferSize()
		, &Renderer::inputLayouts);

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = sizeof(Renderer::Vertex) * 3;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		//xyz
		//rgba
		Renderer::vertexes[ 0 ].pos = Vector3(0.f , 0.5f , 0.0f);
		Renderer::vertexes[ 0 ].color = Vector4(0.0f , 1.0f , 0.0f , 1.0f);

		Renderer::vertexes[ 1 ].pos = Vector3(0.5f , -0.5f , 0.0f);
		Renderer::vertexes[ 1 ].color = Vector4(1.0f , 0.0f , 0.0f , 1.0f);

		Renderer::vertexes[ 2 ].pos = Vector3(-0.5f , -0.5f , 0.0f);
		Renderer::vertexes[ 2 ].color = Vector4(0.0f , 0.0f , 1.0f , 1.0f);

		D3D11_SUBRESOURCE_DATA sub = { Renderer::vertexes };

		mDevice->CreateBuffer(&bufferDesc , &sub , &Renderer::vertexBuffer);
	}

	void GraphicDevice_DX11::Draw()
	{
		// 화면 지우기
		FLOAT backgroundColor[ 4 ] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get() , backgroundColor);
		mContext->ClearDepthStencilView(mDepthStencilView.Get() , D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , 1.f , 0);

		// 뷰포트 설정
		D3D11_VIEWPORT viewPort =
		{
			0, 0, (FLOAT)application.GetWidth(), (FLOAT)application.GetHeight(),
			0.0f, 1.0f
		};
		mContext->RSSetViewports(1 , &viewPort);

		// 렌더 타겟 설정(추후 여러개의 렌더타겟도 설정 가능, Deffered Rendering 등)
		mContext->OMSetRenderTargets(1 , mRenderTargetView.GetAddressOf() , mDepthStencilView.Get());

		// 인풋레이아웃 설정
		mContext->IASetInputLayout(Renderer::inputLayouts);
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 쉐이더 설정
		UINT vertexSize = sizeof(Renderer::Vertex);
		UINT offset = 0;
		mContext->IASetVertexBuffers(0 , 1 , &Renderer::vertexBuffer , &vertexSize , &offset);

		mContext->VSSetShader(Renderer::vsShader , 0 , 0);
		mContext->PSSetShader(Renderer::psShader , 0 , 0);

		// 렌더 타겟에 물체를 그려준다
		mContext->Draw(3 , 0);

		// 렌더 타겟에 있는 이미지를 윈도우에 그려준다
		mSwapChain->Present(1 , 0);
	}
}
