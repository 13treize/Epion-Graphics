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

	std::unique_ptr<ResourceBuffer<CBufferDefault2D>> ConstantBufferManager::m_cbuffer0;
	std::unique_ptr<ResourceBuffer<CBufferObjects>> ConstantBufferManager::m_cbuffer1;
	std::unique_ptr<ResourceBuffer<CBufferPassConstants>> ConstantBufferManager::m_cbuffer2;
	std::unique_ptr<ResourceBuffer<CBufferMaterials>> ConstantBufferManager::m_cbuffer3;
	std::unique_ptr<ResourceBuffer<CBufferParams>> ConstantBufferManager::m_cbuffer4;

	CBufferDefault2D* ConstantBufferManager::m_cbuffer0_data;
	CBufferObjects* ConstantBufferManager::m_cbuffer1_data;
	CBufferPassConstants* ConstantBufferManager::m_cbuffer2_data;
	CBufferMaterials* ConstantBufferManager::m_cbuffer3_data;
	CBufferParams* ConstantBufferManager::m_cbuffer4_data;



	bool ConstantBufferManager::Initialize()
	{
		return true;
	}
	bool ConstantBufferManager::Build2D(const int buffer_num)
	{
		//m_heap = std::make_unique<DX12::DescriptorHeap>();
		//m_heap->Initialize(buffer_num, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		m_cbuffer0 = std::make_unique<DX12::ResourceBuffer<CBufferDefault2D>>();
		m_cbuffer0->Initialize(DX12::Device::Get(), sizeof(CBufferDefault2D), true);
		m_cbuffer4 = std::make_unique<DX12::ResourceBuffer<CBufferParams>>();
		m_cbuffer4->Initialize(DX12::Device::Get(), sizeof(CBufferParams), true);

		return true;
	}
	bool ConstantBufferManager::Build3D(const int buffer_num)
	{
		m_heap = std::make_unique<DX12::DescriptorHeap>();
		m_heap->Initialize(buffer_num, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		m_cbuffer0 = std::make_unique<DX12::ResourceBuffer<CBufferDefault2D>>();
		m_cbuffer0->Initialize(DX12::Device::Get(), sizeof(CBufferDefault2D), true);
		m_cbuffer1 = std::make_unique<DX12::ResourceBuffer<CBufferObjects>>();
		m_cbuffer1->Initialize(DX12::Device::Get(), sizeof(CBufferObjects), true);
		m_cbuffer2 = std::make_unique<DX12::ResourceBuffer<CBufferPassConstants>>();
		m_cbuffer2->Initialize(DX12::Device::Get(), sizeof(CBufferPassConstants), true);
		m_cbuffer3 = std::make_unique<DX12::ResourceBuffer<CBufferMaterials>>();
		m_cbuffer3->Initialize(DX12::Device::Get(), sizeof(CBufferMaterials), true);
		m_cbuffer4 = std::make_unique<DX12::ResourceBuffer<CBufferParams>>();
		m_cbuffer4->Initialize(DX12::Device::Get(), sizeof(CBufferParams), true);
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
		CBufferDefault2D data0;
		data0.ScreenSize =
		{
			static_cast<float>(1280),
			static_cast<float>(720)
		};
		data0.MousePos = mouse_pos;
		data0.Time = { time,0.0f,0.0f,0.0f };
		m_cbuffer0->CopyResource(data0);
	}
	void ConstantBufferManager::UpdateCBuffer1(const DirectX::XMMATRIX& world,const unsigned int index)
	{
		CBufferObjects data1;
		data1.World = world;
		m_cbuffer1->CopyResource(data1,index);
	}

	void ConstantBufferManager::UpdateCBuffer2(const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& projection, const Math::FVector3& camera_pos, const Math::FVector4& color, const Math::FVector4& dir, const Math::FVector4& ambient)
	{
		CBufferPassConstants data2;
		data2.View = view;
		data2.Proj = projection;
		data2.CameraPos.x = camera_pos.x;
		data2.CameraPos.y = camera_pos.y;
		data2.CameraPos.z = camera_pos.z;
		data2.CameraPos.w = 1.0f;

		data2.LightColor = color;
		data2.LightDir = dir;
		data2.AmbientColor = ambient;
		data2.Lights[0].Direction = { 0.57735f, -0.57735f, 0.57735f };
		data2.Lights[0].Strength = { 0.6f, 0.6f, 0.6f };
		data2.Lights[1].Direction = { -0.57735f, -0.57735f, 0.57735f };
		data2.Lights[1].Strength = { 0.3f, 0.3f, 0.3f };
		data2.Lights[2].Direction = { 0.0f, -0.707f, -0.707f };
		data2.Lights[2].Strength = { 0.15f, 0.15f, 0.15f };


		m_cbuffer2->CopyResource(data2);
	}
	void ConstantBufferManager::UpdateCBuffer3(const Math::FVector4& DiffuseAlbedo, const Math::FVector3& FresnelR0, float Roughness, const unsigned int index)
	{
		CBufferMaterials mat;
		mat.DiffuseAlbedo = DiffuseAlbedo;
		mat.FresnelR0 = FresnelR0;
		mat.Roughness = Roughness;
		mat.MatTransform = Math::Identity4x4();
		m_cbuffer3->CopyResource(mat, index);
	}

	void ConstantBufferManager::UpdateCBuffer4(const std::array < Math::FVector4, 4>& data)
	{
		CBufferParams data4;
		data4.Data = data;
		m_cbuffer4->CopyResource(data4);
	}

	void ConstantBufferManager::SetCBuffer0(int index)
	{
		UINT objCBByteSize =CalcConstantBufferByteSize(sizeof(CBufferDefault2D));
		auto objectCB = m_cbuffer0->Get();
		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress();
		DX12::CommandList::GetCmd()->SetGraphicsRootConstantBufferView(0, objCBAddress);
	}

	void ConstantBufferManager::SetCBuffer1(int cb_num, int index)
	{
		UINT objCBByteSize = CalcConstantBufferByteSize(sizeof(CBufferObjects));
		auto objectCB = m_cbuffer1->Get();
		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress1 = objectCB->GetGPUVirtualAddress() + (objCBByteSize * cb_num);
		DX12::CommandList::GetCmd()->SetGraphicsRootConstantBufferView(1, objCBAddress1);
	}
	void ConstantBufferManager::SetCBuffer2(int index)
	{
		UINT objCBByteSize = CalcConstantBufferByteSize(sizeof(CBufferPassConstants));
		auto objectCB = m_cbuffer2->Get();
		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress();
		DX12::CommandList::GetCmd()->SetGraphicsRootConstantBufferView(2, objCBAddress);
	}
	void ConstantBufferManager::SetCBuffer3(int cb_num, int index)
	{
		UINT objCBByteSize = CalcConstantBufferByteSize(sizeof(CBufferMaterials));
		auto objectCB = m_cbuffer3->Get();
		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress1 = objectCB->GetGPUVirtualAddress() + (objCBByteSize * cb_num);
		DX12::CommandList::GetCmd()->SetGraphicsRootConstantBufferView(3, objCBAddress1);
	}

	void ConstantBufferManager::SetCBuffer4(int index)
	{
		UINT objCBByteSize = CalcConstantBufferByteSize(sizeof(CBufferParams));
		auto objectCB = m_cbuffer4->Get();
		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress();
		DX12::CommandList::GetCmd()->SetGraphicsRootConstantBufferView(index, objCBAddress);
	}

	UINT ConstantBufferManager::CalcConstantBufferByteSize(UINT byteSize)
	{
		return (byteSize + 255) & ~255;
	}

}