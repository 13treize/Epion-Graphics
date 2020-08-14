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
		__forceinline static bool CreateCBufferHeap(com_ptr<T>& device, com_ptr<ID3D12DescriptorHeap>& csv_heaps, unsigned int num);

		template<class T>
		__forceinline static bool CreateCommandAllocator(com_ptr<T>& device, com_ptr<ID3D12CommandAllocator>& alloc);

		template<class T>
		__forceinline static bool CreateCommandList(com_ptr<T>& device, com_ptr<ID3D12GraphicsCommandList> &cmd_list,com_ptr<ID3D12CommandAllocator>& cmd_alloc);

		template<class T>
		__forceinline static bool CreateCommandQueue(com_ptr<T>& device, com_ptr<ID3D12CommandQueue>& queue);

		template<class T>
		__forceinline static bool CreateDepthStencilHeap(com_ptr<T>& device, com_ptr<ID3D12DescriptorHeap>& dsv_heaps, unsigned int num);

		template<class T>
		__forceinline static bool CreateFactory(com_ptr<T>& factory);

		template<class T>
		__forceinline static bool CreateFence(com_ptr<T>& device, com_ptr<ID3D12Fence>& fence, UINT64 fence_value);

		template<class T>
		__forceinline static bool CreateRenderTargetHeap(com_ptr<T>& device, com_ptr<ID3D12DescriptorHeap>& rtv_heaps, unsigned int num);

		template	<class	T>
		__forceinline static bool CreateSwapChains(com_ptr<T>& swap_ptr, com_ptr<IDXGIFactory6>& factory, com_ptr<ID3D12CommandQueue>& cmd_queue, HWND hwnd, const Math::Vector2<int>& screen_size_, int buffer_num);
	};

	template<class T>
	__forceinline static bool DX12Wrapper::CreateCBufferHeap(com_ptr<T>& device, com_ptr<ID3D12DescriptorHeap>& csv_heaps, unsigned int num)
	{
		static_assert(std::is_base_of<ID3D12Device, T>::value == true, "BaseClass not ID3D12Device");
		D3D12_DESCRIPTOR_HEAP_DESC csv_heap_desc = { D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, num, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, 0 };
		HRESULT hr = device->CreateDescriptorHeap(&csv_heap_desc, IID_PPV_ARGS(&csv_heaps));
		if (FAILED(hr))	return false;
		return true;
	}

	template<class T>
	__forceinline static bool DX12Wrapper::CreateCommandAllocator(com_ptr<T>& device, com_ptr<ID3D12CommandAllocator>& alloc)
	{
		static_assert(std::is_base_of<ID3D12Device, T>::value == true, "BaseClass not ID3D12Device");
		HRESULT hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(alloc.ReleaseAndGetAddressOf()));
		if (FAILED(hr))	return false;
		return true;
	}
	template<class T>
	__forceinline static bool DX12Wrapper::CreateCommandList(com_ptr<T>& device, com_ptr<ID3D12GraphicsCommandList>& cmd_list, com_ptr<ID3D12CommandAllocator>& cmd_alloc)
	{
		static_assert(std::is_base_of<ID3D12Device, T>::value == true, "BaseClass not ID3D12Device");
		HRESULT hr = device->CreateCommandList(0,D3D12_COMMAND_LIST_TYPE_DIRECT,	cmd_alloc.Get(),nullptr,IID_PPV_ARGS(&cmd_list));
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
	__forceinline static bool DX12Wrapper::CreateDepthStencilHeap(com_ptr<T>& device, com_ptr<ID3D12DescriptorHeap>& dsv_heaps, unsigned int num)
	{
		static_assert(std::is_base_of<ID3D12Device, T>::value == true, "BaseClass not ID3D12Device");
		D3D12_DESCRIPTOR_HEAP_DESC dsv_heap_desc = { D3D12_DESCRIPTOR_HEAP_TYPE_DSV, num, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, 0 };
		HRESULT hr = device->CreateDescriptorHeap(&dsv_heap_desc, IID_PPV_ARGS(&dsv_heaps));
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

	template<class T>
	__forceinline static bool DX12Wrapper::CreateFence(com_ptr<T>& device, com_ptr<ID3D12Fence>& fence, UINT64 fence_value)
	{
		static_assert(std::is_base_of<ID3D12Device, T>::value == true, "BaseClass not ID3D12Device");
		HRESULT hr = device->CreateFence(fence_value, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
		if (FAILED(hr))	return false;
		return true;
	}

	template<class T>
	__forceinline static bool DX12Wrapper::CreateRenderTargetHeap(com_ptr<T>& device, com_ptr<ID3D12DescriptorHeap>& rtv_heaps, unsigned int num)
	{
		static_assert(std::is_base_of<ID3D12Device, T>::value == true, "BaseClass not ID3D12Device");
		D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc = { D3D12_DESCRIPTOR_HEAP_TYPE_RTV, num, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, 0 };
		HRESULT hr = device->CreateDescriptorHeap(&rtv_heap_desc, IID_PPV_ARGS(&rtv_heaps));
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