#pragma once
/**
 * @file DX12Wrapper.h
 * @brief DX12Wrapper関数
 * @author treize
 * @date 2020/08/04
 * @details
 DX12Wrapper
*/
namespace epion::DX12
{
	struct DX12Wrapper
	{
		template<class T>
		__forceinline static bool CreateCommandAllocator(com_ptr<T>& device, com_ptr<ID3D12CommandAllocator>& alloc);

		template<class T>
		__forceinline static bool CreateCommandQueue(com_ptr<T>& device, com_ptr<ID3D12CommandQueue>& queue);

		template<class T>
		__forceinline static bool CreateFactory(com_ptr<T>& factory);

		template	<class	T>
		__forceinline static bool CreateSwapChains(com_ptr<T>& swap_ptr, com_ptr<IDXGIFactory6>& factory, com_ptr<ID3D12CommandQueue>& cmd_queue, HWND hwnd, const Math::Vector2<int>& screen_size_, int buffer_num);

	};

	template<class T>
	__forceinline static bool DX12Wrapper::CreateCommandAllocator(com_ptr<T>& device, com_ptr<ID3D12CommandAllocator>& alloc)
	{
		static_assert(std::is_base_of<ID3D12Device, T>::value == true, "BaseClass not ID3D12Device");
		HRESULT hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(alloc.ReleaseAndGetAddressOf()));
		if (FAILED(hr))	return false;
		return true;
	}

	template<class T>
	__forceinline static bool DX12Wrapper::CreateCommandQueue(com_ptr<T>& device, com_ptr<ID3D12CommandQueue>& queue)
	{
		static_assert(std::is_base_of<ID3D12Device, T>::value == true, "BaseClass not ID3D12Device");
		D3D12_COMMAND_QUEUE_DESC cmdQueueDesc =
		{
			D3D12_COMMAND_LIST_TYPE_DIRECT,//コマンドリストと合わせる
			D3D12_COMMAND_QUEUE_PRIORITY_NORMAL,
			D3D12_COMMAND_QUEUE_FLAG_NONE,//タイムアウトなし
			0
		};
		HRESULT hr = device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(queue.ReleaseAndGetAddressOf()));//コマンドキュー生成
		if (FAILED(hr))	return false;
		return true;
	}

	template<class T>
	__forceinline static bool DX12Wrapper::CreateFactory(com_ptr<T>& factory)
	{
		static_assert(std::is_base_of<IDXGIFactory, T>::value == true, "BaseClass not IDXGIFactory");
		HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(factory.ReleaseAndGetAddressOf()));
		if (FAILED(hr))	return false;
		return true;
	}

	template	<class	T>
	__forceinline static bool DX12Wrapper::CreateSwapChains(com_ptr<T>& swap_ptr, com_ptr<IDXGIFactory6>& factory, com_ptr<ID3D12CommandQueue>& cmd_queue, HWND hwnd, const Math::Vector2<int>& screen_size_, int buffer_num)
	{
		static_assert(std::is_base_of<IDXGIDeviceSubObject, T>::value == true, "BaseClass not IDXGIDeviceSubObject");
		DXGI_SWAP_CHAIN_DESC1 sc_desc = {};
		sc_desc.Width = screen_size_.x;
		sc_desc.Height = screen_size_.y;
		sc_desc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		sc_desc.Stereo = false;
		sc_desc.SampleDesc.Count = 1;
		sc_desc.SampleDesc.Quality = 0;
		sc_desc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
		sc_desc.BufferCount = static_cast<UINT>(buffer_num);
		sc_desc.Scaling = DXGI_SCALING::DXGI_SCALING_STRETCH;
		sc_desc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
		sc_desc.AlphaMode = DXGI_ALPHA_MODE::DXGI_ALPHA_MODE_UNSPECIFIED;
		sc_desc.Flags = DXGI_SWAP_CHAIN_FLAG::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		com_ptr<IDXGISwapChain1> swap_chain1;

		HRESULT hr = factory->CreateSwapChainForHwnd(
			cmd_queue.Get(),
			hwnd,
			&sc_desc,
			nullptr,
			nullptr,
			swap_chain1.GetAddressOf());
		if (FAILED(hr))	return false;
		hr = swap_chain1->QueryInterface(IID_PPV_ARGS(swap_ptr.GetAddressOf()));
		if (FAILED(hr))	return false;
		return true;
	}

}