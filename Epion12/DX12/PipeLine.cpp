#include	"../Epion12.h"
#include	"ViewPort.h"
#include	"Device.h"
#include	"CommandList.h"
#include	"DX12Wrapper.h"
#include	"FrameResourceManager.h"
#include	"PipeLine.h"
namespace
{
}
namespace epion::DX12
{
	bool PipeLine::Initialize(HWND hwnd)
	{
		HRESULT hr = S_OK;
		m_swapchain_buffer_count=2;

		DX12Wrapper::CreateFactory<IDXGIFactory6>(m_factory);

		Device::Initialize(m_factory);

		DX12Wrapper::CreateFence<ID3D12Device>(Device::Get(), m_fence, m_fence_value);

		CreateCommandObjects();
		DX12Wrapper::CreateSwapChains<IDXGISwapChain4>(m_swap, m_factory, m_cmd_queue, hwnd, ViewPort::GetScreenSize(), m_swapchain_buffer_count);

		CreateHeaps();
		//DXGI_SWAP_CHAIN_DESC swcDesc = {};
		//hr = m_swap->GetDesc(&swcDesc);
		//m_back_buffers.resize(swcDesc.BufferCount);
		m_back_buffers.resize(m_swapchain_buffer_count);

		D3D12_CPU_DESCRIPTOR_HANDLE handle = m_heap_rtv->GetCPUDescriptorHandleForHeapStart();
		for (int i = 0; i < m_swapchain_buffer_count; ++i)
		{
			hr = m_swap->GetBuffer(i, IID_PPV_ARGS(&m_back_buffers[i]));
			Device::Get()->CreateRenderTargetView(m_back_buffers[i].Get(), nullptr, handle);
			handle.ptr +=Device::Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}
		DX12Wrapper::CreateDepthStencilView<ID3D12Device>(Device::Get(), m_heap_dsv, m_depth_stencil_buffer, static_cast<UINT>(ViewPort::GetScreenSize().x), static_cast<UINT>(ViewPort::GetScreenSize().y));

		m_dsv_handle = m_heap_dsv->GetCPUDescriptorHandleForHeapStart();
		CreateFrameResources();
		return true;
	}
	bool PipeLine::Finalize()
	{
		return true;
	}
	void PipeLine::Update()
	{
		FrameResourceManager::Update(m_fence);
	}
	void	PipeLine::Render()
	{
		ResouceBarrierBegin();
		ClearRenderTarget();
	}

	void	PipeLine::EndUpdate()
	{
		ResouceBarrierEnd();

		//命令のクローズ
		CommandList::GetCmd()->Close();

		//コマンドリストの実行
		ID3D12CommandList* cmdlists[] = { CommandList::GetCmd().Get() };
		m_cmd_queue->ExecuteCommandLists(_countof(cmdlists), cmdlists);
		WaitForGPU();
		Reset();
	}
	__forceinline void PipeLine::CreateCommandObjects()
	{
		DX12Wrapper::CreateCommandQueue<ID3D12Device>(Device::Get(), m_cmd_queue);
		DX12Wrapper::CreateCommandAllocator<ID3D12Device>(Device::Get(), m_cmd_alloc);
		CommandList::Initialize(m_cmd_alloc);
	}
	__forceinline void PipeLine::CreateHeaps()
	{
		DX12Wrapper::CreateRenderTargetHeap<ID3D12Device>(Device::Get(), m_heap_rtv, m_swapchain_buffer_count);
		DX12Wrapper::CreateDepthStencilHeap<ID3D12Device>(Device::Get(), m_heap_dsv, 1);
		DX12Wrapper::CreateCBufferHeap<ID3D12Device>(Device::Get(), m_heap_imgui, 1);
	}
	__forceinline void	PipeLine::CreateFrameResources()
	{
		FrameResourceManager::Initialize();
	}

	__forceinline void PipeLine::WaitForGPU()
	{
		m_fence_value++;
		m_cmd_queue->Signal(m_fence.Get(), m_fence_value);

		//if (m_fence->GetCompletedValue() != m_fence_value)
		if (m_fence->GetCompletedValue() < m_fence_value)
		{
			auto event = CreateEvent(nullptr, false, false, nullptr);
			m_fence->SetEventOnCompletion(m_fence_value, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}
	}
	__forceinline void PipeLine::Reset()
	{
		auto cmdListAlloc = m_cmd_alloc;
		cmdListAlloc->Reset();//キューをクリア
		CommandList::GetCmd()->Reset(cmdListAlloc.Get(), nullptr);//再びコマンドリストをためる準備
	}

	__forceinline void PipeLine::Begin()
	{
	}
	void PipeLine::End()
	{
		//フリップ
		m_swap->Present(0, 0);
	}

	com_ptr<ID3D12DescriptorHeap>& PipeLine::GetHeapImGui()
	{
		return m_heap_imgui;
	}
	int PipeLine::GetFrameCount()
	{
		return  static_cast<int>(m_swap->GetCurrentBackBufferIndex());
	}

	void	PipeLine::SetBackColor(std::array<float, 4>& color)
	{
		m_clear_color = color;
	}


	void	PipeLine::ClearRenderTarget()
	{
		auto bbIdx = m_swap->GetCurrentBackBufferIndex();
		m_rtv_handle = m_heap_rtv->GetCPUDescriptorHandleForHeapStart();
		m_rtv_handle.ptr += static_cast<SIZE_T>(bbIdx) * Device::Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		CommandList::GetCmd()->ClearDepthStencilView(m_dsv_handle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
		CommandList::GetCmd()->ClearRenderTargetView(m_rtv_handle, m_clear_color.data(), 0, nullptr);
		CommandList::GetCmd()->OMSetRenderTargets(1, &m_rtv_handle, false, &m_dsv_handle);

	}

	void	PipeLine::ResouceBarrierBegin()
	{
		auto bbIdx = m_swap->GetCurrentBackBufferIndex();

		m_barrier_desc = {};
		m_barrier_desc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		m_barrier_desc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		m_barrier_desc.Transition.pResource = m_back_buffers[bbIdx].Get();
		m_barrier_desc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		m_barrier_desc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		m_barrier_desc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		CommandList::GetCmd()->ResourceBarrier(1, &m_barrier_desc);
	}
	void	PipeLine::ResouceBarrierEnd()
	{
		m_barrier_desc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		m_barrier_desc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		CommandList::GetCmd()->ResourceBarrier(1, &m_barrier_desc);
	}

}