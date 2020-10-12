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
		__forceinline static bool CreateCommandList(com_ptr<T>& device, com_ptr<ID3D12GraphicsCommandList>& cmd_list, com_ptr<ID3D12CommandAllocator>& cmd_alloc);

		template<class T>
		__forceinline static bool CreateCommandQueue(com_ptr<T>& device, com_ptr<ID3D12CommandQueue>& queue);

		template<class T>
		__forceinline static bool CreateDepthStencilHeap(com_ptr<T>& device, com_ptr<ID3D12DescriptorHeap>& dsv_heaps, unsigned int num);

		template<class T>
		__forceinline static bool CreateDepthStencilView(com_ptr<T>& device, com_ptr<ID3D12DescriptorHeap>& dsv_heap, com_ptr<ID3D12Resource>& depth_buffer,UINT width,UINT height);

		template<class T>
		__forceinline static bool CreateFactory(com_ptr<T>& factory);

		template<class T>
		__forceinline static bool CreateFence(com_ptr<T>& device, com_ptr<ID3D12Fence>& fence, UINT64 fence_value);

		template<class T>
		__forceinline static bool CreateRenderTargetHeap(com_ptr<T>& device, com_ptr<ID3D12DescriptorHeap>& rtv_heaps, unsigned int num);

		template<class	T>
		__forceinline static bool CreateSwapChains(com_ptr<T>& swap_ptr, com_ptr<IDXGIFactory6>& factory, com_ptr<ID3D12CommandQueue>& cmd_queue, HWND hwnd, const Math::Vector2<int>& screen_size_, int buffer_num);

		static constexpr DXGI_SWAP_CHAIN_DESC1 SWAP_CHAIN_DESC1 =
		{
			.Width=0,
			.Height=0,
			.Format= DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM,
			.Stereo=false,
			.SampleDesc = {1,0},
			.BufferUsage=DXGI_USAGE_BACK_BUFFER,
			.BufferCount=0,
			.Scaling = DXGI_SCALING::DXGI_SCALING_STRETCH,
			.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD,
			.AlphaMode = DXGI_ALPHA_MODE::DXGI_ALPHA_MODE_UNSPECIFIED,
			.Flags= DXGI_SWAP_CHAIN_FLAG::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH,
		};
		static constexpr D3D12_HEAP_PROPERTIES DSV_HEAP_PROPERTIES =
		{
			.Type= D3D12_HEAP_TYPE_DEFAULT,
			.CPUPageProperty= D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference= D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask=0,
			.VisibleNodeMask=0,
		};
		static constexpr D3D12_RESOURCE_DESC RESOURCE_DESC_TEX2D =
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
			.Alignment=0,
			.Width=0,
			.Height=0,
			.DepthOrArraySize=1,
			.MipLevels=0,
			.Format= DXGI_FORMAT_D32_FLOAT,
			.SampleDesc = {1,0},
			.Layout= D3D12_TEXTURE_LAYOUT_UNKNOWN,
			.Flags= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL,
		};

		static constexpr D3D12_RENDER_TARGET_BLEND_DESC RENDER_TARGET_BLEND_DESC =
		{
			.BlendEnable = false,
			.LogicOpEnable = false,
			.SrcBlend = D3D12_BLEND_ONE,
			.DestBlend = D3D12_BLEND_ZERO,
			.BlendOp = D3D12_BLEND_OP_ADD,
			.SrcBlendAlpha = D3D12_BLEND_ONE,
			.DestBlendAlpha = D3D12_BLEND_ZERO,
			.BlendOpAlpha = D3D12_BLEND_OP_ADD,
			.LogicOp = D3D12_LOGIC_OP_NOOP,
			.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL,
		};
		static constexpr D3D12_BLEND_DESC BLEND_DESC =
		{
			.AlphaToCoverageEnable = false,
			.IndependentBlendEnable = false,
			.RenderTarget =
			{
				RENDER_TARGET_BLEND_DESC,
				RENDER_TARGET_BLEND_DESC,
				RENDER_TARGET_BLEND_DESC,
				RENDER_TARGET_BLEND_DESC,
				RENDER_TARGET_BLEND_DESC,
				RENDER_TARGET_BLEND_DESC,
				RENDER_TARGET_BLEND_DESC,
				RENDER_TARGET_BLEND_DESC,
			}
		};
		static constexpr D3D12_DEPTH_STENCILOP_DESC DEFAULT_STENCIL_OP =
		{
			.StencilFailOp = D3D12_STENCIL_OP_KEEP,
			.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP,
			.StencilPassOp = D3D12_STENCIL_OP_KEEP,
			.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS
		};

		static constexpr D3D12_DEPTH_STENCIL_DESC DEPTH_STENCIL_DEFAULT_DESC =
		{
			.DepthEnable = true,
			.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL,
			.DepthFunc = D3D12_COMPARISON_FUNC_LESS,
			.StencilEnable = false,
			.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK,
			.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK,
			.FrontFace = DEFAULT_STENCIL_OP,
			.BackFace = DEFAULT_STENCIL_OP,

		};
		static constexpr D3D12_RASTERIZER_DESC RASTERIZER_SOLID_DESC =
		{
			.FillMode = D3D12_FILL_MODE_SOLID,
			.CullMode = D3D12_CULL_MODE_BACK,
			.FrontCounterClockwise = false,
			.DepthBias = D3D12_DEFAULT_DEPTH_BIAS,
			.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
			.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
			.DepthClipEnable = true,
			.MultisampleEnable = false,
			.AntialiasedLineEnable = false,
			.ForcedSampleCount = 0,
			.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF,
		};

		static constexpr D3D12_RASTERIZER_DESC RASTERIZER_WIREFRAME_DESC =
		{
			.FillMode = D3D12_FILL_MODE_WIREFRAME,
			.CullMode = D3D12_CULL_MODE_BACK,
			.FrontCounterClockwise = false,
			.DepthBias = D3D12_DEFAULT_DEPTH_BIAS,
			.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
			.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
			.DepthClipEnable = true,
			.MultisampleEnable = false,
			.AntialiasedLineEnable = false,
			.ForcedSampleCount = 0,
			.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF,
		};

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
		HRESULT hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmd_alloc.Get(), nullptr, IID_PPV_ARGS(&cmd_list));
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
		D3D12_DESCRIPTOR_HEAP_DESC dsv_heap_desc= 
		{ D3D12_DESCRIPTOR_HEAP_TYPE_DSV, num, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, 0 
		};
		HRESULT hr = device->CreateDescriptorHeap(&dsv_heap_desc, IID_PPV_ARGS(&dsv_heaps));
		if (FAILED(hr))	return false;
		return true;
	}

	template<class T>
	__forceinline static bool DX12Wrapper::CreateDepthStencilView(com_ptr<T>& device, com_ptr<ID3D12DescriptorHeap>& dsv_heap, com_ptr<ID3D12Resource>& depth_buffer, UINT width, UINT height)
	{
		D3D12_RESOURCE_DESC depth_desc = DX12Wrapper::RESOURCE_DESC_TEX2D;
		depth_desc.Width = width;
		depth_desc.Height = height;

		D3D12_CLEAR_VALUE dsv_clear_value;
		dsv_clear_value.Format = DXGI_FORMAT_D32_FLOAT;
		dsv_clear_value.Color[0] = 0.0f;
		dsv_clear_value.Color[1] = 0.0f;
		dsv_clear_value.Color[2] = 0.0f;
		dsv_clear_value.Color[3] = 0.0f;
		dsv_clear_value.DepthStencil.Depth = 1.0f;
		dsv_clear_value.DepthStencil.Stencil = 0;
		device->CreateCommittedResource(
			&DX12Wrapper::DSV_HEAP_PROPERTIES,
			D3D12_HEAP_FLAG_NONE,
			&depth_desc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&dsv_clear_value,
			IID_PPV_ARGS(depth_buffer.ReleaseAndGetAddressOf()));
		D3D12_DEPTH_STENCIL_VIEW_DESC descDSV = {};
		descDSV.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		descDSV.Format = DXGI_FORMAT_D32_FLOAT;
		descDSV.Texture2D.MipSlice = 0;
		device->CreateDepthStencilView(	depth_buffer.Get(),	&descDSV,	dsv_heap->GetCPUDescriptorHandleForHeapStart());
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
		DXGI_SWAP_CHAIN_DESC1 sc_desc = SWAP_CHAIN_DESC1;

		sc_desc.Width = static_cast<UINT>(screen_size_.x);
		sc_desc.Height = static_cast<UINT>(screen_size_.y);
		sc_desc.BufferCount = buffer_num;
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