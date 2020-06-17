#pragma once
namespace epion::DX12
{
	struct PipeLineStates
	{
		const int NUM_BACK_BUFFERS = 3;
	};
	class PipeLine final
	{
	public:
		bool	Initialize(HWND hwnd);
		bool	Finalize();
		void	Update();
		void	Render();
		void	EndUpdate();

		__forceinline void	WaitForGPU();
		__forceinline void Reset();
		__forceinline void	Begin();
		void	End();

		//”÷–­

		void	ResouceBarrierBegin();
		void	ResouceBarrierEnd();

		//get
		com_ptr<ID3D12DescriptorHeap>& GetHeapImGui();

		//set
		void	SetBackColor(std::array<float, 4>& color);

	private:
		com_ptr<IDXGISwapChain4> m_swap;
		com_ptr<IDXGIFactory6> m_factory;
		com_ptr<ID3D12CommandQueue> m_cmd_queue;
		com_ptr<ID3D12CommandAllocator> m_cmd_alloc;

		com_ptr<ID3D12Fence> m_fence;

		com_ptr<ID3D12DescriptorHeap> m_heap_imgui;
		com_ptr<ID3D12DescriptorHeap> m_heap_rtv;

		std::vector<com_ptr<ID3D12Resource>> m_back_buffers;

		D3D12_CPU_DESCRIPTOR_HANDLE m_rtv_handle;

		D3D12_RESOURCE_BARRIER m_barrier_desc;
		UINT64 m_fence_value;
		std::array<float, 4> m_clear_color;

		__forceinline void	ClearRenderTarget();

	};
}