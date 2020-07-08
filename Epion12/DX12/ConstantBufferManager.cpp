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
	std::unique_ptr<DX12::ConstantBuffer> ConstantBufferManager::m_cbuffer2;

	CBuffer0* ConstantBufferManager::m_cbuffer0_data;
	CBuffer1* ConstantBufferManager::m_cbuffer1_data;
	CBuffer2* ConstantBufferManager::m_cbuffer2_data;

	bool ConstantBufferManager::Initialize()
	{
		m_heap = std::make_unique<DX12::DescriptorHeap>();
		m_heap->Initialize(2, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		m_cbuffer0 = std::make_unique<DX12::ConstantBuffer>();
		m_cbuffer0->Initialize(256);
		DX12::Device::Get()->CreateConstantBufferView(&m_cbuffer0->GetView(), m_heap->GetHandleCPU(0));
		m_cbuffer0->GetBuffer()->Map(0, nullptr, reinterpret_cast<void**>(&m_cbuffer0_data));

		m_cbuffer1 = std::make_unique<DX12::ConstantBuffer>();
		m_cbuffer1->Initialize(256);
		DX12::Device::Get()->CreateConstantBufferView(&m_cbuffer1->GetView(), m_heap->GetHandleCPU(1));
		m_cbuffer1->GetBuffer()->Map(0, nullptr, reinterpret_cast<void**>(&m_cbuffer1_data));

		m_cbuffer2 = std::make_unique<DX12::ConstantBuffer>();
		m_cbuffer2->Initialize(256);
		DX12::Device::Get()->CreateConstantBufferView(&m_cbuffer2->GetView(), m_heap->GetHandleCPU(2));
		m_cbuffer2->GetBuffer()->Map(0, nullptr, reinterpret_cast<void**>(&m_cbuffer2_data));

		return true;
	}

	bool ConstantBufferManager::Finalize()
	{
		//m_cbuffer0->GetBuffer()->Unmap();
		return true;
	}
	void ConstantBufferManager::SetHeap()
	{
		DX12::CommandList::GetPtr()->SetDescriptorHeaps(1, m_heap->GetHeap().GetAddressOf());
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
	void ConstantBufferManager::UpdateCBuffer1(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& projection)
	{
		CBuffer1 data1;
		data1.World = world;
		data1.View = view;
		data1.Proj = projection;
		memcpy(m_cbuffer1_data, &data1, sizeof(data1));
	}

	void ConstantBufferManager::UpdateCBuffer2(const Math::FVector4& color, const Math::FVector4& dir, const Math::FVector4& ambient)
	{
		CBuffer2 data2;
		data2.LightColor = color;
		data2.LightColor = dir;
		data2.AmbientColor = ambient;
		memcpy(m_cbuffer2_data, &data2, sizeof(data2));
	}

	void ConstantBufferManager::SetCBuffer0()
	{
		DX12::CommandList::GetPtr()->SetGraphicsRootDescriptorTable(0, m_heap->GetHandleGPU(0));
		//auto passCB = m_cbuffer0->GetBuffer().Get();
		//DX12::CommandList::GetPtr()->SetGraphicsRootConstantBufferView(0, passCB->GetGPUVirtualAddress());
	}

	void ConstantBufferManager::SetCBuffer1(unsigned int index)
	{
		auto handle = m_heap->GetHandleGPU(index);
		DX12::CommandList::GetPtr()->SetGraphicsRootDescriptorTable(1, handle);
	}
	void ConstantBufferManager::SetCBuffer2()
	{
		DX12::CommandList::GetPtr()->SetGraphicsRootDescriptorTable(2, m_heap->GetHandleGPU(2));
	}

	UINT ConstantBufferManager::CalcConstantBufferByteSize(UINT byteSize)
	{
		return (byteSize + 255) & ~255;
	}

}