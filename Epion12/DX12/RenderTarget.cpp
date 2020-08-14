#include	"../Epion12.h"
#include	"RenderTarget.h"

namespace epion::DX12
{
	RenderTarget::RenderTarget()
	{
	}

	RenderTarget::~RenderTarget()
	{
	}

	bool RenderTarget::Initialize(com_ptr<ID3D12Device>& m_device, com_ptr<IDXGISwapChain4>& m_swap)
	{
		HRESULT hr;
		D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc = { D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 2, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, 0 };
		hr = m_device->CreateDescriptorHeap(&rtv_heap_desc, IID_PPV_ARGS(&m_rtv_heaps));
		DXGI_SWAP_CHAIN_DESC swcDesc = {};
		//	m_hr = m_swap->GetDesc(&swcDesc);
		m_back_buffers.resize(2);

		D3D12_CPU_DESCRIPTOR_HANDLE handle = m_rtv_heaps->GetCPUDescriptorHandleForHeapStart();
		for (int i = 0; i < static_cast<int>(swcDesc.BufferCount); ++i)
		{
			hr = m_swap->GetBuffer(i, IID_PPV_ARGS(&m_back_buffers[i]));
			m_device->CreateRenderTargetView(m_back_buffers[i].Get(), nullptr, handle);
			handle.ptr += m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}
		return true;
	}
	bool RenderTarget::Finalize()
	{
		return true;
	}

	void RenderTarget::Clear(com_ptr<ID3D12Device>& m_device, com_ptr<ID3D12GraphicsCommandList>& cmd_list, com_ptr<IDXGISwapChain4>& m_swap)
	{
		auto bbIdx = m_swap->GetCurrentBackBufferIndex();
		//レンダーターゲットを指定
		auto rtvH = m_rtv_heaps->GetCPUDescriptorHandleForHeapStart();
		rtvH.ptr += bbIdx * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		cmd_list->OMSetRenderTargets(1, &rtvH, false, nullptr);
		//画面クリア
		float clearColor[] = { 1.0f,0.0f,0.0f,1.0f };
		cmd_list->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	}
	bool RenderTargetFunction::CreateRenderTargetHeap(com_ptr<ID3D12Device>& device, com_ptr<ID3D12DescriptorHeap>& rtv_heaps)
	{
		D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc = { D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 2, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, 0 };
		HRESULT hr = device->CreateDescriptorHeap(&rtv_heap_desc, IID_PPV_ARGS(&rtv_heaps));
		if (FAILED(hr))	return false;
		return true;
	}



}