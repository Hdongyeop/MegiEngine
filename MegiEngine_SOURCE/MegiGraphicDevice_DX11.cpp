#include "MegiGraphicDevice_DX11.h"
#include "MegiApplication.h"
#include "MegiRenderer.h"

extern MegiEngine::Application application;

namespace MegiEngine::graphics
{
	GraphicDevice_DX11::GraphicDevice_DX11()
	{
		GetDevice() = this;
	}

	GraphicDevice_DX11::~GraphicDevice_DX11()
	{
	}

	bool GraphicDevice_DX11::CreateDevice()
	{
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

		return true;
	}

	bool GraphicDevice_DX11::CreateSwapChain(DXGI_SWAP_CHAIN_DESC desc)
	{
		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory = nullptr;

		if ( FAILED(mDevice->QueryInterface(__uuidof( IDXGIDevice ) , ( void** ) pDXGIDevice.GetAddressOf())) )
			return false;

		if ( FAILED(pDXGIDevice->GetParent(__uuidof( IDXGIAdapter ) , ( void** ) pAdapter.GetAddressOf())) )
			return false;

		if ( FAILED(pAdapter->GetParent(__uuidof( IDXGIFactory ) , ( void** ) pFactory.GetAddressOf())) )
			return false;

		if ( FAILED(pFactory->CreateSwapChain(mDevice.Get() , &desc, mSwapChain.GetAddressOf())) )
			return false;

		return true;
	}

	bool GraphicDevice_DX11::GetBuffer(UINT Buffer , const IID& riid , void** ppSurface)
	{
		if ( FAILED(mSwapChain->GetBuffer(Buffer , riid , ppSurface)) )
			return false;
		return true;
	}

	bool GraphicDevice_DX11::CreateRenderTargetView(ID3D11Resource* pResource ,
		const D3D11_RENDER_TARGET_VIEW_DESC* pDesc , ID3D11RenderTargetView** ppRTView)
	{
		if ( FAILED(mDevice->CreateRenderTargetView(pResource , pDesc , ppRTView)) )
			return false;
		return true;
	}

	bool GraphicDevice_DX11::CreateDepthStencilView(ID3D11Resource* pResource ,
		const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc , ID3D11DepthStencilView** ppDSView)
	{
		if ( FAILED(mDevice->CreateDepthStencilView(pResource, pDesc , ppDSView)))
			return false;
		return true;
	}

	bool GraphicDevice_DX11::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc ,
		const D3D11_SUBRESOURCE_DATA* pInitialData , ID3D11Texture2D** ppTexture2D)
	{
		if ( FAILED(mDevice->CreateTexture2D(pDesc , pInitialData , ppTexture2D)) )
			return false;
		return true;
	}

	bool GraphicDevice_DX11::CreateVertexShader(const std::wstring& fileName , ID3DBlob** ppCode ,
		ID3D11VertexShader** ppVertexShader)
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
		shaderFlags |= D3DCOMPILE_DEBUG;
		shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

		ID3DBlob* errorBlob = nullptr;
		const std::wstring shaderFilePath = L"..\\Shaders_SOURCE\\";
		D3DCompileFromFile((shaderFilePath + fileName).c_str(), nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE , "main"
		, "vs_5_0" , shaderFlags , 0
		, ppCode, &errorBlob);

		if(errorBlob)
		{
			OutputDebugStringA(( char* ) errorBlob->GetBufferPointer());
			errorBlob->Release();
			assert(NULL && "hlsl file have problem check message!");
			return false;
		}

		if(FAILED(mDevice->CreateVertexShader(
		(*ppCode)->GetBufferPointer()
		, (*ppCode)->GetBufferSize()
		, nullptr , ppVertexShader)))
		{
			return false;
		}

		return true;
	}

	bool GraphicDevice_DX11::CreatePixelShader(const std::wstring& fileName , ID3DBlob** ppCode ,
		ID3D11PixelShader** ppPixelShader)
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
		shaderFlags |= D3DCOMPILE_DEBUG;
		shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

		ID3DBlob* errorBlob = nullptr;
		const std::wstring shaderFilePath = L"..\\Shaders_SOURCE\\";
		D3DCompileFromFile((shaderFilePath + fileName).c_str(), nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE , "main"
		, "ps_5_0" , shaderFlags , 0
		, ppCode, &errorBlob);

		if(errorBlob)
		{
			OutputDebugStringA(( char* ) errorBlob->GetBufferPointer());
			errorBlob->Release();
			assert(NULL && "hlsl file have problem check message!");
			return false;
		}

		if(FAILED(mDevice->CreatePixelShader(
		(*ppCode)->GetBufferPointer()
		, (*ppCode)->GetBufferSize()
		, nullptr , ppPixelShader)))
		{
			return false;
		}

		return true;
	}

	bool GraphicDevice_DX11::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs , UINT NumElements ,
		const void* pShaderBytecodeWithInputSignature , SIZE_T BytecodeLength , ID3D11InputLayout** ppInputLayout)
	{
		if ( FAILED(mDevice->CreateInputLayout(
			pInputElementDescs ,
			NumElements ,
			pShaderBytecodeWithInputSignature ,
			BytecodeLength ,
			ppInputLayout)) )
		{
			return false;
		}
		return true;
	}

	bool GraphicDevice_DX11::CreateBuffer(const D3D11_BUFFER_DESC * pDesc , const D3D11_SUBRESOURCE_DATA * pInitialData ,
		ID3D11Buffer * *ppBuffer)
	{
		if ( FAILED(mDevice->CreateBuffer(pDesc , pInitialData , ppBuffer)) )
			return false;
		return true;
	}

	void GraphicDevice_DX11::BindConstantBuffer(ShaderStage stage, CBType type, ID3D11Buffer* buffer)
	{
		UINT slot = ( UINT ) type;
		switch (stage)
		{
		case ShaderStage::VS:
			mContext->VSSetConstantBuffers(slot , 1 , &buffer);
			break;
		case ShaderStage::HS:
			mContext->HSSetConstantBuffers(slot , 1 , &buffer);
			break;
		case ShaderStage::DS:
			mContext->DSSetConstantBuffers(slot , 1 , &buffer);
			break;
		case ShaderStage::GS:
			mContext->GSSetConstantBuffers(slot , 1 , &buffer);
			break;
		case ShaderStage::PS:
			mContext->PSSetConstantBuffers(slot , 1 , &buffer);
			break;
		case ShaderStage::CS:
			mContext->CSSetConstantBuffers(slot , 1 , &buffer);
			break;
		case ShaderStage::All:
			mContext->VSSetConstantBuffers(slot , 1 , &buffer);
			mContext->HSSetConstantBuffers(slot , 1 , &buffer);
			mContext->DSSetConstantBuffers(slot , 1 , &buffer);
			mContext->GSSetConstantBuffers(slot , 1 , &buffer);
			mContext->PSSetConstantBuffers(slot , 1 , &buffer);
			mContext->CSSetConstantBuffers(slot , 1 , &buffer);
			break;
		default:
			break;
		}
	}

	void GraphicDevice_DX11::Initialize()
	{
		if (!(CreateDevice()) )
			assert(NULL && "Create Device failed!!");

#pragma region SwapChain DESC

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

#pragma endregion

#pragma region 4X MSAA supported check

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

#pragma endregion

		if (!(CreateSwapChain(swapChainDesc)) )
			assert(NULL && "Create Swapchain failed!!");

		if (!(GetBuffer(0 , __uuidof( ID3D11Texture2D ) , (void**) mRenderTarget.GetAddressOf())))
			assert(NULL && "Couldn't bring rendertarget!!");

		if (!(CreateRenderTargetView(mRenderTarget.Get() , nullptr , mRenderTargetView.GetAddressOf())) )
			assert(NULL && "Create RenderTargetView failed!!");

#pragma region DepthSencil DESC

		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // Depth 24bit, Stencil 8bit
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.Width = application.GetWidth();
		depthStencilDesc.Height = application.GetHeight();
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;

#pragma endregion

		if (!(CreateTexture2D(&depthStencilDesc , nullptr , mDepthStencil.GetAddressOf())) )
			assert(NULL && "Create depthstencil texture failed!!");

		if (!(CreateDepthStencilView(mDepthStencil.Get() , nullptr , mDepthStencilView.GetAddressOf())) )
			assert(NULL && "Create depthstencil View failed!!");

		if (!(CreateVertexShader(L"TriangleVS.hlsl" , &Renderer::vsBlob , &Renderer::vsShader)) )
			assert(NULL && "Create vertex shader failed!!");

		if (!(CreatePixelShader(L"TrianglePS.hlsl" , &Renderer::psBlob , &Renderer::psShader)) )
			assert(NULL && "Create pixel shader failed!!");

#pragma region InputLayout DESC

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

#pragma endregion

		if (!(CreateInputLayout(inputLayoutDesces , 2
			, Renderer::vsBlob->GetBufferPointer()
			, Renderer::vsBlob->GetBufferSize()
			, &Renderer::inputLayouts)) )
			assert(NULL && "Create input layout failed!");

#pragma region Vertex Buffer DESC

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = sizeof(Renderer::Vertex) * 4;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sub = { Renderer::vertexes };

#pragma endregion

		if (!(CreateBuffer(&bufferDesc , &sub , &Renderer::vertexBuffer)) )
			assert(NULL && "Create vertex buffer failed!");

#pragma region Index Buffer DESC

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth = sizeof(UINT) * Renderer::indices.size();
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.CPUAccessFlags = 0;
		// indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA indicesData = {Renderer::indices.data()};

#pragma endregion

		if (!(CreateBuffer(&indexBufferDesc , &indicesData , &Renderer::indexBuffer)) )
			assert(NULL && "Create index buffer failed!");

#pragma region Constant Buffer DESC

		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = sizeof(Vector4);
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		Vector4 pos(.5f , .0f , .0f , 1.f);
		D3D11_SUBRESOURCE_DATA constantBufferData = {};
		constantBufferData.pSysMem = &pos;

#pragma endregion

		if ( !( CreateBuffer(&constantBufferDesc , &constantBufferData , &Renderer::constantBuffer) ) )
			assert(NULL && "Create constant buffer failed!");
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
			0, 0, ( FLOAT ) application.GetWidth(), ( FLOAT ) application.GetHeight(),
			0.0f, 1.0f
		};
		mContext->RSSetViewports(1 , &viewPort);

		// 렌더 타겟 설정(추후 여러개의 렌더타겟도 설정 가능, Deffered Rendering 등)
		mContext->OMSetRenderTargets(1 , mRenderTargetView.GetAddressOf() , mDepthStencilView.Get());

		// 인풋레이아웃 설정
		mContext->IASetInputLayout(Renderer::inputLayouts);
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		D3D11_MAPPED_SUBRESOURCE mappedSubresource;
		Vector4 newPos(-.5f , .0f , .0f , 1.f);
		if(!FAILED(mContext->Map(Renderer::constantBuffer , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &mappedSubresource)))
		{
			memcpy(mappedSubresource.pData , &newPos , sizeof(Vector4));
			mContext->Unmap(Renderer::constantBuffer , 0);
		}

		// 쉐이더 설정
		UINT vertexSize = sizeof(Renderer::Vertex);
		UINT offset = 0;
		mContext->IASetVertexBuffers(0 , 1 , &Renderer::vertexBuffer , &vertexSize , &offset);
		mContext->IASetIndexBuffer(Renderer::indexBuffer , DXGI_FORMAT_R32_UINT , 0);
		BindConstantBuffer(ShaderStage::VS , CBType::Transform , Renderer::constantBuffer);

		mContext->VSSetShader(Renderer::vsShader , 0 , 0);
		mContext->PSSetShader(Renderer::psShader , 0 , 0);

		// 렌더 타겟에 물체를 그려준다
		mContext->Draw(3 , 0);

		// 렌더 타겟에 있는 이미지를 윈도우에 그려준다
		mSwapChain->Present(1 , 0);
	}
}