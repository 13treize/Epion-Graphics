#pragma once
/**
 * @file RenderTarget.h
 * @brief RenderTargetクラス
 * @author treize
 * @date 2020/02/20
 * @details RenderTarget、仮実装に近い
 */
namespace epion::DX12
{
	class RenderTarget final
	{
	public:
		RenderTarget();
		~RenderTarget();
		bool Initialize(com_ptr<ID3D12Device>& m_device, com_ptr<IDXGISwapChain4>& m_swap);
		bool Finalize();
		void Clear(com_ptr<ID3D12Device>& m_device, com_ptr<ID3D12GraphicsCommandList>& cmd_list, com_ptr<IDXGISwapChain4>& m_swap);

	private:
		com_ptr<ID3D12DescriptorHeap> m_rtv_heaps;
		std::vector<com_ptr<ID3D12Resource>> m_back_buffers;

	};

	struct RenderTargetFunction
	{
		static bool CreateRenderTarget(com_ptr<ID3D12Device>& device, com_ptr<ID3D12DescriptorHeap>& rtv_heaps);
	};
}