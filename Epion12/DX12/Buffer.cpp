#include "../Epion12.h"
#include "Buffer.h"
#include "Device.h"
#include "CommandList.h"

namespace epion::DX12
{
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
			IID_PPV_ARGS(&m_vertex_buffer));

		m_vertex_buffer_view = {};
		m_vertex_buffer_view.BufferLocation = m_vertex_buffer->GetGPUVirtualAddress();//バッファの仮想アドレス
		m_vertex_buffer_view.SizeInBytes = bytes;//全バイト数
		m_vertex_buffer_view.StrideInBytes = size;//1頂点あたりのバイト数
		return true;
	}

	bool VertexBuffer::Finalize()
	{
		return true;
	}
	void VertexBuffer::SetState()
	{
		DX12::CommandList::GetPtr()->IASetVertexBuffers(0, 1, &m_vertex_buffer_view);
	}

	com_ptr<ID3D12Resource>& VertexBuffer::GetBuffer()
	{
		return m_vertex_buffer;
	}

	D3D12_VERTEX_BUFFER_VIEW& VertexBuffer::GetView()
	{
		return m_vertex_buffer_view;
	}

	IndexBuffer::IndexBuffer()
		: m_index_buffer_view({})
	{
	}
	IndexBuffer::~IndexBuffer()
	{
	}
	bool IndexBuffer::Initialize(int size)
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
			IID_PPV_ARGS(&m_index_buffer));

		m_index_buffer_view = {};
		m_index_buffer_view.BufferLocation = m_index_buffer->GetGPUVirtualAddress();
		m_index_buffer_view.Format = DXGI_FORMAT_R16_UINT;
		m_index_buffer_view.SizeInBytes = size;
		return true;
	}

	bool IndexBuffer::Finalize()
	{
		return true;
	}
	void IndexBuffer::SetState()
	{
		//DX12::DX12CommandList::GetPtr()->IASetVertexBuffers(0, 1, &m_vertex_buffer_view);
	}

	com_ptr<ID3D12Resource>& IndexBuffer::GetBuffer()
	{
		return m_index_buffer;
	}

	D3D12_INDEX_BUFFER_VIEW& IndexBuffer::GetView()
	{
		return m_index_buffer_view;
	}

	//ConstantBuffer::ConstantBuffer()
	//	: m_constant_buffer_view({})
	//{
	//}
	//ConstantBuffer::~ConstantBuffer()
	//{
	//}
	//bool ConstantBuffer::Initialize(int size)
	//{
	//	HRESULT hr = S_OK;


	//	D3D12_HEAP_PROPERTIES heapprop = {};
	//	heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
	//	heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	//	heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	//	heapprop.CreationNodeMask = 1;
	//	heapprop.VisibleNodeMask = 1;

	//	D3D12_RESOURCE_DESC resdesc = {};
	//	resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	//	resdesc.Alignment = 0;
	//	resdesc.Width = size;
	//	resdesc.Height = 1;
	//	resdesc.DepthOrArraySize = 1;
	//	resdesc.MipLevels = 1;
	//	resdesc.Format = DXGI_FORMAT_UNKNOWN;
	//	resdesc.SampleDesc.Count = 1;
	//	resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	//	resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//	hr = DX12::Device::Get()->CreateCommittedResource(
	//		&heapprop,
	//		D3D12_HEAP_FLAG_NONE,
	//		&resdesc,
	//		D3D12_RESOURCE_STATE_GENERIC_READ,
	//		nullptr,
	//		IID_PPV_ARGS(&m_constant_buffer));

	//	if (FAILED(hr))
	//	{
	//		return false;
	//	}
	//	m_constant_buffer_view = {};
	//	m_constant_buffer_view.BufferLocation = m_constant_buffer->GetGPUVirtualAddress();
	//	m_constant_buffer_view.SizeInBytes = size;
	//	return true;
	//}

	//bool ConstantBuffer::Finalize()
	//{
	//	return true;
	//}
	//void ConstantBuffer::SetState()
	//{
	//}

	//com_ptr<ID3D12Resource>& ConstantBuffer::GetBuffer()
	//{
	//	return m_constant_buffer;
	//}

	//D3D12_CONSTANT_BUFFER_VIEW_DESC& ConstantBuffer::GetView()
	//{
	//	return m_constant_buffer_view;
	//}

}