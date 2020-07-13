#include "../Epion12.h"
#include "Buffer.h"
#include "Device.h"
#include "CommandList.h"

namespace epion::DX12
{
	Buffer::Buffer()
		:m_buffer_count(0)
	{
	}
	unsigned int Buffer::GetBufferCount()
	{
		return m_buffer_count;
	}
	VertexBuffer::VertexBuffer()
		: m_vertex_buffer_view({})
	{
	}
	VertexBuffer::~VertexBuffer()
	{
	}
	bool VertexBuffer::Initialize(int size, int bytes)
	{
		HRESULT hr = S_OK;

		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = size;
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.Format = DXGI_FORMAT_UNKNOWN;
		resdesc.SampleDesc.Count = 1;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		hr = DX12::Device::Get()->CreateCommittedResource(
			&heapprop,
			D3D12_HEAP_FLAG_NONE,
			&resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(m_resource_buffer.ReleaseAndGetAddressOf()));

		m_vertex_buffer_view = { m_resource_buffer->GetGPUVirtualAddress() ,static_cast<UINT>(bytes),static_cast<UINT>(size)};
		return true;
	}

	bool VertexBuffer::Finalize()
	{
		return true;
	}
	void VertexBuffer::SetState()
	{
		DX12::CommandList::GetCmd()->IASetVertexBuffers(0, 1, &m_vertex_buffer_view);
	}


	D3D12_VERTEX_BUFFER_VIEW& VertexBuffer::GetView()
	{
		return m_vertex_buffer_view;
	}

	ConstantBuffer::ConstantBuffer()
		: m_constant_buffer_view({})
	{
	}
	ConstantBuffer::~ConstantBuffer()
	{
	}
	bool ConstantBuffer::Initialize(int size)
	{
		HRESULT hr = S_OK;


		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapprop.CreationNodeMask = 1;
		heapprop.VisibleNodeMask = 1;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Alignment = 0;
		resdesc.Width = size;
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.Format = DXGI_FORMAT_UNKNOWN;
		resdesc.SampleDesc.Count = 1;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		hr = DX12::Device::Get()->CreateCommittedResource(
			&heapprop,
			D3D12_HEAP_FLAG_NONE,
			&resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(m_resource_buffer.ReleaseAndGetAddressOf()));

		if (FAILED(hr))
		{
			return false;
		}
		m_constant_buffer_view = {};
		m_constant_buffer_view.BufferLocation = m_resource_buffer->GetGPUVirtualAddress();
		m_constant_buffer_view.SizeInBytes = size;
		return true;
	}

	bool ConstantBuffer::Finalize()
	{
		return true;
	}
	void ConstantBuffer::SetState()
	{
	}


	D3D12_CONSTANT_BUFFER_VIEW_DESC& ConstantBuffer::GetView()
	{
		return m_constant_buffer_view;
	}

}