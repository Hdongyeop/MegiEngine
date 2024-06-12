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

		HRESULT Load(const std::wstring& path) override;
		UINT GetWidth() const { return mWidth; }
		void SetWidth(UINT width) { mWidth = width; }
		UINT GetHeight() const { return mHeight; }
		void SetHeight(UINT height) { mHeight = height; }
		HDC GetHdc() const { return mHdc; }
		TextureType GetTextureType() const { return mType; }
		Gdiplus::Image* GetImage() const { return mImage; }
		bool HaveAlphaChannel() const { return mAlpha; }
		COLORREF GetPixel(int x , int y);

	private:
		bool mAlpha;
		TextureType mType;
		Gdiplus::Image* mImage;
		HBITMAP mBitmap;
		HDC mHdc;

		UINT mWidth;
		UINT mHeight;
	};


}
