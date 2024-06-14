#pragma once

#include "MegiGraphics.h"

// Sample Example DX11
// https://github.com/kevinmoran/BeginnerDirect3D11

namespace MegiEngine::graphics
{
	class GraphicDevice_DX11
	{
	public:
		GraphicDevice_DX11();
		~GraphicDevice_DX11();

		bool CreateDevice();
		bool CreateSwapChain(DXGI_SWAP_CHAIN_DESC desc);
		bool GetBuffer(UINT Buffer , REFIID riid , void** ppSurface);
		bool CreateRenderTargetView(
			ID3D11Resource* pResource ,
			const D3D11_RENDER_TARGET_VIEW_DESC* pDesc ,
			ID3D11RenderTargetView** ppRTView);
		bool CreateDepthStencilView(
			ID3D11Resource* pResource ,
			const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc ,
			ID3D11DepthStencilView** ppDSView);
		bool CreateTexture2D(
			const D3D11_TEXTURE2D_DESC* pDesc ,
			const D3D11_SUBRESOURCE_DATA* pInitialData ,
			ID3D11Texture2D** ppTexture2D);
		bool CreateVertexShader(
			const std::wstring& fileName ,
			ID3DBlob** ppCode ,
			ID3D11VertexShader** ppVertexShader);
		bool CreatePixelShader(
			const std::wstring& fileName ,
			ID3DBlob** ppCode ,
			ID3D11PixelShader** ppPixelShader);
		bool CreateInputLayout(
			const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs ,
			UINT NumElements ,
			const void* pShaderBytecodeWithInputSignature ,
			SIZE_T BytecodeLength ,
			ID3D11InputLayout** ppInputLayout);
		bool CreateBuffer(
			const D3D11_BUFFER_DESC* pDesc ,
			const D3D11_SUBRESOURCE_DATA* pInitialData ,
			ID3D11Buffer** ppBuffer);
		void BindConstantBuffer(ShaderStage stage , CBType type , ID3D11Buffer* buffer);

		void Initialize();
		void Draw();

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencil;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> mSamplers;
	};

	// This is a helper to get access to a global device instance
	// - The engine uses this, but it is not necessary to use a single global device object
	// - This is not a lifetime managing object, just a way to globally expose a reference to
	// an object by pointer
	inline GraphicDevice_DX11*& GetDevice()
	{
		static GraphicDevice_DX11* device = nullptr;
		return device;
	}

}

