#include	"../Epion12.h"
#include	"ViewPort.h"
#include	"Device.h"
#include	"CommandList.h"
#include	"SwapChain.h"
#include	"CommandQueue.h"
#include	"Factory.h"
#include	"RenderTarget.h"
//#include	"../Shader/ShaderManager.h"
#include	"PipeLine.h"

namespace
{
}
namespace epion::DX12
{
	bool PipeLine::Initialize(HWND hwnd)
	{
		HRESULT hr = S_OK;

		FactoryFunction::CreateFactory<IDXGIFactory6>(m_factory);

		Device::Initialize(m_factory);

		hr = Device::Get()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_cmd_alloc));
		CommandList::Initialize(m_cmd_alloc);

		CommandQueueFunction::CreateCommandQueue(Device::Get(), m_cmd_queue);
		SwapChainFunction::CreateSwapChains<IDXGISwapChain4>(m_swap, m_factory, m_cmd_queue, hwnd, ViewPort::GetScreenSize(), 2);
		RenderTargetFunction::CreateRenderTarget(Device::Get(), m_heap_rtv);
		DXGI_SWAP_CHAIN_DESC swcDesc = {};
		hr = m_swap->GetDesc(&swcDesc);
		m_back_buffers.resize(swcDesc.BufferCount);
		int count = 0;
		D3D12_CPU_DESCRIPTOR_HANDLE handle = m_heap_rtv->GetCPUDescriptorHandleForHeapStart();
		for (int i = 0; i < static_cast<int>(swcDesc.BufferCount); ++i)
		{
			hr = m_swap->GetBuffer(i, IID_PPV_ARGS(&m_back_buffers[i]));
			Device::Get()->CreateRenderTargetView(m_back_buffers[i].Get(), nullptr, handle);
			handle.ptr +=Device::Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
			count++;
		}
		hr =Device::Get()->CreateFence(m_fence_value, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));

		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		desc.NodeMask = 0;
		desc.NumDescriptors = 1;
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		Device::Get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(m_heap_imgui.ReleaseAndGetAddressOf()));

		return true;
	}
	bool PipeLine::Finalize()
	{
		return true;
	}
	void PipeLine::Update()
	{
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
		m_cmd_queue->ExecuteCommandLists(1, cmdlists);
		WaitForGPU();
		Reset();
	}

	__forceinline void PipeLine::WaitForGPU()
	{
		m_cmd_queue->Signal(m_fence.Get(), ++m_fence_value);

		if (m_fence->GetCompletedValue() != m_fence_value)
		{
			auto event = CreateEvent(nullptr, false, false, nullptr);
			m_fence->SetEventOnCompletion(m_fence_value, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}
		// フレームバッファ番号を更新.
	}
	__forceinline void PipeLine::Reset()
	{
		m_cmd_alloc->Reset();//キューをクリア
		CommandList::GetCmd()->Reset(m_cmd_alloc.Get(), nullptr);//再びコマンドリストをためる準備
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

	void	PipeLine::SetBackColor(std::array<float, 4>& color)
	{
		m_clear_color = color;
	}


	void	PipeLine::ClearRenderTarget()
	{
		auto bbIdx = m_swap->GetCurrentBackBufferIndex();
		m_rtv_handle = m_heap_rtv->GetCPUDescriptorHandleForHeapStart();
		m_rtv_handle.ptr += static_cast<SIZE_T>(bbIdx) * Device::Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		CommandList::GetCmd()->OMSetRenderTargets(1, &m_rtv_handle, false, nullptr);
		CommandList::GetCmd()->ClearRenderTargetView(m_rtv_handle, m_clear_color.data(), 0, nullptr);
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