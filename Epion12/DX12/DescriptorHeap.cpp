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

		return true;
	}

}