#pragma once

namespace epion::DX12
{
	template<class T>
	class ResourceBuffer final
	{
	public:
		ResourceBuffer()
			:m_byte_size(0),
			m_count(0),
			m_is_constant_buffer(false)
		{
		}
		~ResourceBuffer()
		{

		}

		bool Initialize(com_ptr<ID3D12Device>& device, unsigned int buffer_count, bool is_constant)
		{
			m_byte_size = sizeof(T);
			m_count = buffer_count;
			m_is_constant_buffer = is_constant;

			if (is_constant)
			{
				m_byte_size = (sizeof(T) + 255) & ~255;
			}
			D3D12_HEAP_PROPERTIES heap_prop = {};
			heap_prop.Type = D3D12_HEAP_TYPE_UPLOAD;
			heap_prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			heap_prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

			D3D12_RESOURCE_DESC resource_desc = {};
			resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			resource_desc.Width = buffer_count;
			resource_desc.Height = 1;
			resource_desc.DepthOrArraySize = 1;
			resource_desc.MipLevels = 1;
			resource_desc.Format = DXGI_FORMAT_UNKNOWN;
			resource_desc.SampleDesc.Count = 1;
			resource_desc.Flags = D3D12_RESOURCE_FLAG_NONE;
			resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

			device->CreateCommittedResource(
				&heap_prop,
				D3D12_HEAP_FLAG_NONE,
				&resource_desc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(m_resource_buffer.ReleaseAndGetAddressOf()));

			m_resource_buffer->Map(0, nullptr, reinterpret_cast<void**>(&m_mapped_resource));
			return true;
		}
		bool Finalize()
		{
			if (m_resource_buffer != nullptr)
			{
				m_resource_buffer->Unmap(0, nullptr);
			}
			m_mapped_resource = nullptr;
			return true;
		}

		template<size_t N>
		void CopyResource(const std::array<T, N>& data)
		{
			memcpy(m_mapped_resource, data.data(), sizeof(data));
		}

		void CopyResource(const std::vector<T>& data)
		{
			memcpy(m_mapped_resource, data.data(), sizeof(data));
		}

		D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress()
		{
			return m_resource_buffer->GetGPUVirtualAddress();
		}
		const unsigned int GetCount()
		{
			return m_count;
		}

	private:
		T* m_mapped_resource = nullptr;
		com_ptr<ID3D12Resource>	m_resource_buffer;
		bool m_is_constant_buffer;
		unsigned int m_byte_size;
		unsigned int m_count;

	};
	class Buffer abstract
	{
	public:
		Buffer();
		virtual	~Buffer() {};
		virtual bool	Finalize() = 0;
		virtual void	SetState() = 0;
		unsigned int GetBufferCount();
		com_ptr<ID3D12Resource>& GetBuffer()
		{
			return m_resource_buffer;
		}

	protected:
		com_ptr<ID3D12Resource>	m_resource_buffer;

		unsigned int m_buffer_count;

	};

	class VertexBuffer :public Buffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();
		bool Initialize(int size, int bytes);
		bool Finalize() override;
		void SetState() override;

		//com_ptr<ID3D12Resource>& GetBuffer();
		D3D12_VERTEX_BUFFER_VIEW& GetView();

	private:
		D3D12_VERTEX_BUFFER_VIEW m_vertex_buffer_view;
	};

	class ConstantBuffer :public Buffer
	{
	public:
		ConstantBuffer();
		~ConstantBuffer();
		bool Initialize(int size);
		bool Finalize() override;
		void SetState() override;
		//com_ptr<ID3D12Resource>& GetBuffer();
		D3D12_CONSTANT_BUFFER_VIEW_DESC& GetView();

	private:
		D3D12_CONSTANT_BUFFER_VIEW_DESC m_constant_buffer_view;

	};

}

