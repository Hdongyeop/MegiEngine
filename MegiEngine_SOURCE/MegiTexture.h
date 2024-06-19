#pragma once
#include <DirectXTex.h>

#include "MegiGraphicDevice_DX11.h"
#include "MegiResource.h"

namespace MegiEngine::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		~Texture();

		HRESULT Save(const std::wstring& path) override;
		HRESULT Load(const std::wstring& path) override;

		void Bind(ShaderStage stage , UINT startSlot);

	private:
		ScratchImage mImage;

		D3D11_TEXTURE2D_DESC mDesc;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV; // For read
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRTV; // For write
	};


}
