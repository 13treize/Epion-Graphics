#include	"../Epion12.h"
#include	"SwapChain.h"

namespace epion::DX12
{
	SwapChain::SwapChain()
	{
	}

	SwapChain::~SwapChain()
	{
	}

	bool SwapChain::Initialize(HWND hwnd, com_ptr<IDXGIFactory6>& factory, com_ptr<ID3D12CommandQueue>& cmd_queue, int width, int height)
	{
		DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
		swapchainDesc.Width = width;
		swapchainDesc.Height = height;
		swapchainDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		swapchainDesc.Stereo = false;
		swapchainDesc.SampleDesc.Count = 1;
		swapchainDesc.SampleDesc.Quality = 0;
		swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
		swapchainDesc.BufferCount = 2;
		swapchainDesc.Scaling = DXGI_SCALING::DXGI_SCALING_STRETCH;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapchainDesc.AlphaMode = DXGI_ALPHA_MODE::DXGI_ALPHA_MODE_UNSPECIFIED;
		swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


		com_ptr<IDXGISwapChain1> p_swap_chain;

		HRESULT hr = factory->CreateSwapChainForHwnd(cmd_queue.Get(),
			hwnd,
			&swapchainDesc,
			nullptr,
			nullptr,
			p_swap_chain.GetAddressOf());
		if (FAILED(hr))
		{
			return false;
		}
		//SwapChain1¨3‚É•ÏŠ·
		hr = p_swap_chain->QueryInterface(IID_PPV_ARGS(m_swap_chain.GetAddressOf()));

		return true;
	}
	bool SwapChain::Finalize()
	{
		//m_swap_chain->Release();
		return true;
	}

	void SwapChain::Present()
	{
		m_swap_chain->Present(1, 0);
	}
	com_ptr<IDXGISwapChain4>& SwapChain::GetPtr()
	{
		return m_swap_chain;
	}
}