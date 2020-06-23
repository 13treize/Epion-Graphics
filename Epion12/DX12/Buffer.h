#pragma once

namespace epion::DX12
{
	class Buffer abstract
	{
	public:
		Buffer() {};
		virtual	~Buffer() {};
		virtual bool	Finalize() = 0;
		virtual void	SetState() = 0;
	private:
	};

	class VertexBuffer :public Buffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();
		bool Initialize(int size, int bytes);
		bool Finalize() override;
		void SetState() override;

		com_ptr<ID3D12Resource>& GetBuffer();
		D3D12_VERTEX_BUFFER_VIEW& GetView();

	private:
		com_ptr<ID3D12Resource>	m_vertex_buffer;
		D3D12_VERTEX_BUFFER_VIEW m_vertex_buffer_view;
	};

	class IndexBuffer :public Buffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();
		bool Initialize(int size);
		bool Finalize() override;
		void SetState() override;

		com_ptr<ID3D12Resource>& GetBuffer();
		D3D12_INDEX_BUFFER_VIEW& GetView();

	private:
		com_ptr<ID3D12Resource>	m_index_buffer;
		D3D12_INDEX_BUFFER_VIEW m_index_buffer_view;
	};
	
	class ConstantBuffer :public Buffer
	{
	public:
		ConstantBuffer();
		~ConstantBuffer();
		bool Initialize(int size);
		bool Finalize() override;
		void SetState() override;

		com_ptr<ID3D12Resource>& GetBuffer();
		D3D12_CONSTANT_BUFFER_VIEW_DESC& GetView();

	private:
		com_ptr<ID3D12Resource>	m_constant_buffer;
		D3D12_CONSTANT_BUFFER_VIEW_DESC m_constant_buffer_view;
	};

}

