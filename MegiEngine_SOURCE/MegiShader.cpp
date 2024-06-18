#include "MegiShader.h"

#include "MegiGraphicDevice_DX11.h"

namespace MegiEngine::graphics
{
	Shader::Shader()
	: Resource(ResourceType::Shader)
	{
	}

	Shader::~Shader()
	{
	}

	HRESULT Shader::Load(const std::wstring& path)
	{
		size_t findNameBeginOffset = path.rfind(L"\\") + 1;
		size_t fileNameLength = path.length() - findNameBeginOffset;

		const std::wstring fileName(path.substr(findNameBeginOffset , fileNameLength));

		if ( !Create(ShaderStage::VS , fileName) )
			return S_FALSE;
		if ( !Create(ShaderStage::PS , fileName) )
			return S_FALSE;

		return S_OK;
	}

	bool Shader::Create(const ShaderStage stage, const std::wstring& fileName)
	{
		if ( stage == ShaderStage::VS )
			CreateVertexShader(fileName);
		if ( stage == ShaderStage::PS )
			CreatePixelShader(fileName);

		return true;
	}

	bool Shader::CreateVertexShader(const std::wstring& fileName)
	{
		if ( !GetDevice()->CreateVertexShader(fileName , mVSBlob.GetAddressOf() , mVS.GetAddressOf()) )
			return false;
		return true;
	}

	bool Shader::CreatePixelShader(const std::wstring& fileName)
	{
		if ( !GetDevice()->CreatePixelShader(fileName , mPSBlob.GetAddressOf() , mPS.GetAddressOf()) )
			return false;
		return true;
	}

	void Shader::Bind()
	{
		if ( mVS ) GetDevice()->BindVS(mVS.Get());
		if ( mPS ) GetDevice()->BindPS(mPS.Get());
	}
}
