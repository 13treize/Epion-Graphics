#pragma once
namespace epion::DX12
{
	class DescriptorHeap final
	{
	public:
		DescriptorHeap();
		~DescriptorHeap();
		bool Initialize(int size, D3D12_DESCRIPTOR_HEAP_TYPE heap_type);

		com_ptr<ID3D12DescriptorHeap>& GetHeap();
		D3D12_CPU_DESCRIPTOR_HANDLE GetHandleCPU(const unsigned index);
		D3D12_GPU_DESCRIPTOR_HANDLE GetHandleGPU(const unsigned index);
		const unsigned int GetSize();
	private:
		com_ptr<ID3D12DescriptorHeap> m_heap;
		unsigned int m_size;
	};
}