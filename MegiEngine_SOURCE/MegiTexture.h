#pragma once
#include "MegiResource.h"

namespace MegiEngine::graphics
{
	class Texture : public Resource
	{
	public:
		enum class TextureType
		{
			Bmp,
			Png,
			None,
		};

		static Texture* Create(const std::wstring& name , UINT width , UINT height);

		Texture();
		~Texture();

		HRESULT Save(const std::wstring& path) override;
		HRESULT Load(const std::wstring& path) override;
		UINT GetWidth() const { return mWidth; }
		UINT GetHeight() const { return mHeight; }
		TextureType GetTextureType() const { return mType; }
		bool HaveAlphaChannel() const { return mAlpha; }

		void SetWidth(UINT width) { mWidth = width; }
		void SetHeight(UINT height) { mHeight = height; }

	private:
		bool mAlpha;
		TextureType mType;

		UINT mWidth;
		UINT mHeight;
	};


}
