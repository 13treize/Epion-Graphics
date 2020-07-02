#include "../Epion12.h"
#include "ConstantBufferManager.h"
#include "Device.h"
#include "CommandList.h"
#include	"../DX12/ViewPort.h"

namespace epion::DX12
{
	std::unique_ptr<epion::DX12::DescriptorHeap> ConstantBufferManager::m_heap;
	std::unique_ptr<DX12::ConstantBuffer> ConstantBufferManager::m_cbuffer0;
	std::unique_ptr<DX12::ConstantBuffer> ConstantBufferManager::m_cbuffer1;
	CBuffer0* ConstantBufferManager::m_cbuffer0_data;
	CBuffer1* ConstantBufferManager::m_cbuffer1_data;

	bool ConstantBufferManager::Initialize()
	{
		m_heap = std::make_unique<DX12::DescriptorHeap>();
		m_heap->Initialize(1, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	
		m_cbuffer0 = std::make_unique<DX12::ConstantBuffer>();
		m_cbuffer0->Initialize(256);
		DX12::Device::Get()->CreateConstantBufferView(&m_cbuffer0->GetView(), m_heap->GetHeap()->GetCPUDescriptorHandleForHeapStart());

		m_cbuffer0->GetBuffer()->Map(0, nullptr, reinterpret_cast<void**>(&m_cbuffer0_data));
		CBuffer0 data0;
		data0.Time = { 0.0f,0.0f,0.0f,0.0f };
		data0.ScreenSize = { 0.0f,0.0f };
		data0.MousePos = { 0.0f,0.0f };
		memcpy(m_cbuffer0_data, &data0, sizeof(data0));

		m_cbuffer1 = std::make_unique<DX12::ConstantBuffer>();
		m_cbuffer1->Initialize(256);
		DX12::Device::Get()->CreateConstantBufferView(&m_cbuffer1->GetView(), m_heap->GetHeap()->GetCPUDescriptorHandleForHeapStart());
		m_cbuffer1->GetBuffer()->Map(0, nullptr, reinterpret_cast<void**>(&m_cbuffer1_data));
		return true;
	}

	bool ConstantBufferManager::Finalize()
	{
		//m_cbuffer0->GetBuffer()->Unmap();
		return true;
	}

	void ConstantBufferManager::UpdateCBuffer0(const Math::FVector2& mouse_pos)
	{
		static float time= 0.0f;
		time += 1.0f / 400.0f;
		CBuffer0 data0;
		data0.ScreenSize =
		{
			static_cast<float>(ViewPort::GetScreenSize().x),
			static_cast<float>(ViewPort::GetScreenSize().y)
		};
		data0.MousePos = mouse_pos;
		data0.Time = { time,0.0f,0.0f,0.0f };
		memcpy(m_cbuffer0_data, &data0, sizeof(data0));
	}
	void ConstantBufferManager::UpdateCBuffer1(/*DirectX::XMFLOAT4X4& matrix,*/const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection)
	{

	}

	void ConstantBufferManager::SetCBuffer0()
	{
		ID3D12DescriptorHeap* pp_heaps[] = { m_heap->GetHeap().Get() };

		DX12::CommandList::GetPtr()->SetDescriptorHeaps(1, pp_heaps);
		DX12::CommandList::GetPtr()->SetGraphicsRootDescriptorTable(0, m_heap->GetHeap()->GetGPUDescriptorHandleForHeapStart());
	}

	void ConstantBufferManager::SetCBuffer1()
	{
		ID3D12DescriptorHeap* pp_heaps[] = { m_heap->GetHeap().Get() };

		DX12::CommandList::GetPtr()->SetDescriptorHeaps(1, pp_heaps);
		DX12::CommandList::GetPtr()->SetGraphicsRootDescriptorTable(0, m_heap->GetHeap()->GetGPUDescriptorHandleForHeapStart());
	}

}