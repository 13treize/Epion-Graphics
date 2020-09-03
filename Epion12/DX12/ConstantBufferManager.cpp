#include "../Epion12.h"
#include "ConstantBufferManager.h"
#include "Device.h"
#include "CommandList.h"
#include	"../DX12/ViewPort.h"

namespace
{
}
namespace epion::DX12
{
	std::unique_ptr<DescriptorHeap> ConstantBufferManager::m_heap;

	std::unique_ptr<ResourceBuffer<CBuffer0>> ConstantBufferManager::m_cbuffer0;
	std::unique_ptr<ResourceBuffer<CBuffer1>> ConstantBufferManager::m_cbuffer1;
	std::unique_ptr<ResourceBuffer<CBuffer2>> ConstantBufferManager::m_cbuffer2;
	std::unique_ptr<ResourceBuffer<CBuffer3>> ConstantBufferManager::m_cbuffer3;

	CBuffer0* ConstantBufferManager::m_cbuffer0_data;
	CBuffer1* ConstantBufferManager::m_cbuffer1_data;
	CBuffer2* ConstantBufferManager::m_cbuffer2_data;
	CBuffer3* ConstantBufferManager::m_cbuffer3_data;



	bool ConstantBufferManager::Initialize()
	{
		return true;
	}
	bool ConstantBufferManager::Build2D(const int buffer_num)
	{
		//m_heap = std::make_unique<DX12::DescriptorHeap>();
		//m_heap->Initialize(buffer_num, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		m_cbuffer0 = std::make_unique<DX12::ResourceBuffer<CBuffer0>>();
		m_cbuffer0->Initialize(DX12::Device::Get(), sizeof(CBuffer0), true);
		m_cbuffer3 = std::make_unique<DX12::ResourceBuffer<CBuffer3>>();
		m_cbuffer3->Initialize(DX12::Device::Get(), sizeof(CBuffer3), true);

		return true;
	}
	bool ConstantBufferManager::Build3D(const int buffer_num)
	{
		m_heap = std::make_unique<DX12::DescriptorHeap>();
		m_heap->Initialize(buffer_num, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		m_cbuffer0 = std::make_unique<DX12::ResourceBuffer<CBuffer0>>();
		m_cbuffer0->Initialize(DX12::Device::Get(), sizeof(CBuffer0), true);
		m_cbuffer1 = std::make_unique<DX12::ResourceBuffer<CBuffer1>>();
		m_cbuffer1->Initialize(DX12::Device::Get(), sizeof(CBuffer1), true);
		m_cbuffer2 = std::make_unique<DX12::ResourceBuffer<CBuffer2>>();
		m_cbuffer2->Initialize(DX12::Device::Get(), sizeof(CBuffer2), true);
		m_cbuffer3 = std::make_unique<DX12::ResourceBuffer<CBuffer3>>();
		m_cbuffer3->Initialize(DX12::Device::Get(), sizeof(CBuffer3), true);
		return true;
	}

	bool ConstantBufferManager::Finalize()
	{
		//m_cbuffer0->GetBuffer()->Unmap();
		return true;
	}
	void ConstantBufferManager::SetHeap()
	{
		DX12::CommandList::GetCmd()->SetDescriptorHeaps(1, m_heap->GetHeap().GetAddressOf());
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
		m_cbuffer0->CopyResource(data0);
	}
	void ConstantBufferManager::UpdateCBuffer1(const DirectX::XMMATRIX& world,const unsigned int index)
	{
		CBuffer1 data1;
		data1.World = world;
		m_cbuffer1->CopyResource(data1,index);
	}

	void ConstantBufferManager::UpdateCBuffer2(const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& projection, const Math::FVector3& camera_pos, const Math::FVector4& color, const Math::FVector4& dir, const Math::FVector4& ambient)
	{
		CBuffer2 data2;
		data2.View = view;
		data2.Proj = projection;
		//data2.CameraPos.x = camera_pos.x;
		//data2.CameraPos.y = camera_pos.y;
		//data2.CameraPos.z = camera_pos.z;
		//data2.CameraPos.w = 1.0f;

		data2.LightColor = color;
		data2.LightDir = dir;
		data2.AmbientColor = ambient;
		m_cbuffer2->CopyResource(data2);
	}
	void ConstantBufferManager::UpdateCBuffer3(const std::array < Math::FVector4, 4>& data)
	{
		CBuffer3 data3;
		data3.Data = data;
		m_cbuffer3->CopyResource(data3);
	}

	void ConstantBufferManager::SetCBuffer0(int index)
	{
		UINT objCBByteSize =CalcConstantBufferByteSize(sizeof(CBuffer0));
		auto objectCB = m_cbuffer0->Get();
		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress();
		DX12::CommandList::GetCmd()->SetGraphicsRootConstantBufferView(0, objCBAddress);
	}

	void ConstantBufferManager::SetCBuffer1(int frame_count, int index)
	{
		UINT objCBByteSize = CalcConstantBufferByteSize(sizeof(CBuffer1));
		auto objectCB = m_cbuffer1->Get();
		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress1 = objectCB->GetGPUVirtualAddress() + (objCBByteSize * frame_count);
		DX12::CommandList::GetCmd()->SetGraphicsRootConstantBufferView(1, objCBAddress1);
	}
	void ConstantBufferManager::SetCBuffer2(int index)
	{
		UINT objCBByteSize = CalcConstantBufferByteSize(sizeof(CBuffer2));
		auto objectCB = m_cbuffer2->Get();
		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress();
		DX12::CommandList::GetCmd()->SetGraphicsRootConstantBufferView(2, objCBAddress);
	}

	void ConstantBufferManager::SetCBuffer3(int index)
	{
		UINT objCBByteSize = CalcConstantBufferByteSize(sizeof(CBuffer3));
		auto objectCB = m_cbuffer3->Get();
		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress();
		DX12::CommandList::GetCmd()->SetGraphicsRootConstantBufferView(index, objCBAddress);
	}

	UINT ConstantBufferManager::CalcConstantBufferByteSize(UINT byteSize)
	{
		return (byteSize + 255) & ~255;
	}

}