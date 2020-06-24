#include "../Epion12.h"
#include "ConstantBufferManager.h"
#include "Device.h"
#include "CommandList.h"

namespace epion::DX12
{
	std::unique_ptr<epion::DX12::DescriptorHeap> ConstantBufferManager::m_heap;
	std::unique_ptr<DX12::ConstantBuffer> ConstantBufferManager::m_cbuffer0;
	CBuffer0* ConstantBufferManager::m_cbuffer0_data;

	bool ConstantBufferManager::Initialize()
	{
		m_heap = std::make_unique<DX12::DescriptorHeap>();
		m_heap->Initialize(1, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		m_cbuffer0 = std::make_unique<DX12::ConstantBuffer>();
		m_cbuffer0->Initialize(256);

		DX12::Device::Get()->CreateConstantBufferView(&m_cbuffer0->GetView(), m_heap->m_heap->GetCPUDescriptorHandleForHeapStart());


		m_cbuffer0->GetBuffer()->Map(0, nullptr, reinterpret_cast<void**>(&m_cbuffer0_data));
		CBuffer0 data2 = { 1.0f,0.0f,0.0f,0.0f };
		memcpy(m_cbuffer0_data, &data2, sizeof(data2));

		return true;
	}

	bool ConstantBufferManager::Finalize()
	{
		//m_cbuffer0->GetBuffer()->Unmap();
		return true;
	}

	void ConstantBufferManager::UpdateCBuffer0()
	{
		CBuffer0 data2 = { 1.0f,0.0f,1.0f,0.0f };
		memcpy(m_cbuffer0_data, &data2, sizeof(data2));
	}

	void ConstantBufferManager::SetCBuffer0()
	{
		ID3D12DescriptorHeap* pp_heaps[] = { m_heap->m_heap.Get() };

		DX12::CommandList::GetPtr()->SetDescriptorHeaps(1, pp_heaps);
		DX12::CommandList::GetPtr()->SetGraphicsRootDescriptorTable(0, m_heap->m_heap->GetGPUDescriptorHandleForHeapStart());
	}

}