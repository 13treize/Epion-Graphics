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

}