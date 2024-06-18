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

	HRESULT Texture::Save(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		return S_OK;
	}
}
