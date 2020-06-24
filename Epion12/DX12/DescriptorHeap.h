#pragma once
namespace epion::DX12
{
	class DescriptorHeap final
	{
	public:
		DescriptorHeap();
		~DescriptorHeap();
		bool Initialize(int size, D3D12_DESCRIPTOR_HEAP_TYPE heap_type);

	//private:
		com_ptr<ID3D12DescriptorHeap> m_heap;

	};
}