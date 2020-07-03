#include "../Epion12.h"
#include "DescriptorHeap.h"
#include "Device.h"
#include "CommandList.h"

namespace epion::DX12
{
	DescriptorHeap::DescriptorHeap()
	{
	}

	DescriptorHeap::~DescriptorHeap()
	{
	}

	bool DescriptorHeap::Initialize(int size, D3D12_DESCRIPTOR_HEAP_TYPE heap_type)
	{
		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.NumDescriptors = size;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		desc.Type = heap_type;
		DX12::Device::Get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_heap));
		m_size = DX12::Device::Get()->GetDescriptorHandleIncrementSize(desc.Type);

		return true;
	}

	com_ptr<ID3D12DescriptorHeap>& DescriptorHeap::GetHeap()
	{
		return m_heap;
	}
	D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetHandleCPU(const unsigned index)
	{
		auto handle = m_heap->GetCPUDescriptorHandleForHeapStart();
		handle.ptr += static_cast<UINT64>(m_size * index);
		return handle;

	}
	D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::GetHandleGPU(const unsigned index)
	{
		D3D12_GPU_DESCRIPTOR_HANDLE handle = m_heap->GetGPUDescriptorHandleForHeapStart();
		handle.ptr += static_cast<UINT64>(m_size * index);
		return handle;
	}

	const unsigned int DescriptorHeap::GetSize()
	{
		return m_size;
	}

}