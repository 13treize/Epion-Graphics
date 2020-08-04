#pragma once
namespace epion::DX12
{
	struct DX12Wrapper
	{
		template<class T>
		__forceinline static bool CreateFactory(com_ptr<T>& factory);

	};

	template<class T>
	__forceinline static bool DX12Wrapper::CreateFactory(com_ptr<T>& factory)
	{
		static_assert(std::is_base_of<IDXGIFactory, T>::value == true, "BaseClass not IDXGIFactory");
		HRESULT hr;
		hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));
		if (FAILED(hr))	return false;
		return true;
	}

}