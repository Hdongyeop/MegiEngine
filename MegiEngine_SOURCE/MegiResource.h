#pragma once
#include "CommonInclude.h"
#include "MegiEntity.h"
#include "MegiEnums.h"

namespace MegiEngine
{
	using namespace Type;
	class Resource abstract : public Entity
	{
	public:
		Resource(ResourceType type);
		virtual ~Resource();

		virtual HRESULT Save(const std::wstring& path) = 0;
		virtual HRESULT Load(const std::wstring& path) = 0;
		const std::wstring& GetPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		const ResourceType mType;
		std::wstring mPath;
	};


}
