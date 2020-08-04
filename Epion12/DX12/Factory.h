#pragma once
/**
 * @file Factory.h
 * @brief FactoryçÏê¨
 * @author treize
 * @date 2020/02/26
 * @details
 FactoryçÏê¨ÉNÉâÉX
 <br>https://docs.microsoft.com/en-us/windows/win32/api/dxgi1_6/nn-dxgi1_6-idxgifactory6
 */
namespace epion::DX12
{
	class Factory final
	{
	public:

	private:
	};

	struct FactoryFunction final
	{
		template<class T>
		__forceinline static bool CreateFactory(com_ptr<T>& factory);
	};
	template<class T>
	__forceinline static bool FactoryFunction::CreateFactory(com_ptr<T>& factory)
	{
		static_assert(std::is_base_of<IDXGIFactory, T>::value == true, "BaseClass not IDXGIFactory");
		HRESULT hr;
		hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));
		if (FAILED(hr))	return false;
		return true;
	}

}