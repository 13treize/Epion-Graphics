#pragma once

/**
 * @file DX12SwapChain.h
 * @brief SwapChain�쐬
 * @author treize
 * @date 2020/02/18
 * @details
 SwapChain�쐬�N���X�A1����4�܂ł̐�����Windows10��
 <br>�A�b�v�f�[�g�Œǉ����ꂽ�@�\����������Ă���B
 <br>https://docs.microsoft.com/ja-jp/windows/win32/api/dxgi1_5/nn-dxgi1_5-idxgiswapchain4
 */

namespace epion::DX12
{
	class SwapChain final
	{
	public:
		SwapChain();
		~SwapChain();
		bool Initialize(HWND hwnd, com_ptr<IDXGIFactory6>& factory, com_ptr<ID3D12CommandQueue>& cmd_queue, int width, int height);
		bool Finalize();

		void Present();

		com_ptr<IDXGISwapChain4>& GetPtr();

	private:
		com_ptr<IDXGISwapChain4> m_swap_chain;
	};


	struct SwapChainFunction
	{
		/**
		* @fn
		* SwapChain�쐬�֐�
		* @brief �v�����
		* @param (������) �����̐���
		* @param (������) �����̐���
		* @return �߂�l�̐���
		* @sa �Q�Ƃ��ׂ��֐��������΃����N���\���
		* @detail �֐������Ŏ���,template�ŗ~�����^(1����4���擾)
		*/
		template	<class	T>
		__forceinline static bool CreateSwapChains(com_ptr<T>& swap_ptr, com_ptr<IDXGIFactory6>& factory, com_ptr<ID3D12CommandQueue>& cmd_queue, HWND hwnd, const Math::Vector2<int>& screen_size_, int buffer_num);
	};


	//Implementation
	template	<class	T>
	__forceinline static bool SwapChainFunction::CreateSwapChains(com_ptr<T>& swap_ptr, com_ptr<IDXGIFactory6>& factory, com_ptr<ID3D12CommandQueue>& cmd_queue, HWND hwnd, const Math::Vector2<int>& screen_size_, int buffer_num)
	{
		static_assert(std::is_base_of<IDXGIDeviceSubObject, T>::value == true, "BaseClass not IDXGIDeviceSubObject");
		DXGI_SWAP_CHAIN_DESC1 sc_desc = {};
		sc_desc.Width = screen_size_.x;
		sc_desc.Height = screen_size_.y;
		sc_desc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		sc_desc.Stereo = false;
		sc_desc.SampleDesc.Count = 1;
		sc_desc.SampleDesc.Quality = 0;
		sc_desc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
		sc_desc.BufferCount = static_cast<UINT>(buffer_num);
		sc_desc.Scaling = DXGI_SCALING::DXGI_SCALING_STRETCH;
		sc_desc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
		sc_desc.AlphaMode = DXGI_ALPHA_MODE::DXGI_ALPHA_MODE_UNSPECIFIED;
		sc_desc.Flags = DXGI_SWAP_CHAIN_FLAG::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		com_ptr<IDXGISwapChain1> p_swap_chain;

		HRESULT hr = factory->CreateSwapChainForHwnd(
			cmd_queue.Get(),
			hwnd,
			&sc_desc,
			nullptr,
			nullptr,
			p_swap_chain.GetAddressOf());
		if (FAILED(hr))
		{
			return false;
		}

		hr = p_swap_chain->QueryInterface(IID_PPV_ARGS(swap_ptr.GetAddressOf()));

		return true;

	}

}