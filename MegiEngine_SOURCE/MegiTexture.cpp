#include "MegiTexture.h"

#include "MegiApplication.h"
#include "MegiResources.h"

extern MegiEngine::Application application;

namespace MegiEngine::graphics
{
	Texture* Texture::Create(const std::wstring& name, UINT width, UINT height)
	{
		Texture* image = Resources::Find<Texture>(name);
		if ( image ) return image;

		image = new Texture();
		image->SetName(name);
		image->SetWidth(width);
		image->SetHeight(height);

		HDC hdc = application.GetHdc();

		image->mBitmap = CreateCompatibleBitmap(hdc , width , height);
		image->mHdc = CreateCompatibleDC(hdc);

		HBITMAP oldBitmap = ( HBITMAP ) SelectObject(image->mHdc , image->mBitmap);
		DeleteObject(oldBitmap);

		Resources::Insert(name + L"Image" , image);

		return image;
	}

	Texture::Texture()
	:Resource(ResourceType::Texture)
	, mAlpha(false)
	{
	}

	Texture::~Texture()
	{
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		if(ext == L"bmp")
		{
			mType = TextureType::Bmp;
			mBitmap = (HBITMAP) LoadImageW(nullptr , path.c_str() , IMAGE_BITMAP , 0 , 0 , LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if ( mBitmap == nullptr )
				return S_FALSE;

			BITMAP info = {};
			GetObject(mBitmap , sizeof(BITMAP) , &info);

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			HDC mainDC = application.GetHdc();
			mHdc = CreateCompatibleDC(mainDC);

			HBITMAP oldBitmap = ( HBITMAP ) SelectObject(mHdc , mBitmap);
			DeleteObject(oldBitmap);
		}
		else if(ext == L"png")
		{
			mType = TextureType::Png;
			mImage = Gdiplus::Image::FromFile(path.c_str());
			if ( mImage == nullptr )
				return S_FALSE;

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}

		return S_OK;
	}
}
