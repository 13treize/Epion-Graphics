#include	"../Epion12.h"
#include	"ViewPort.h"

namespace epion::DX12
{
	ViewPortBase::ViewPortBase()
	{
	}

	ViewPortBase::ViewPortBase(const D3D12_VIEWPORT& view_port)
		:m_viewport(view_port)
	{
		m_scissorrect.top = 0;
		m_scissorrect.left = 0;
		m_scissorrect.right = m_scissorrect.left + static_cast<LONG>(m_viewport.Width);
		m_scissorrect.bottom = m_scissorrect.top + static_cast<LONG>(m_viewport.Height);
	}
	void ViewPortBase::RSSets(com_ptr<ID3D12GraphicsCommandList>& cmd)
	{
		cmd->RSSetViewports(1, &m_viewport);
		cmd->RSSetScissorRects(1, &m_scissorrect);
	}

	D3D12_VIEWPORT ViewPortBase::Get()
	{
		return m_viewport;
	}
	D3D12_RECT ViewPortBase::GetRect()
	{
		return m_scissorrect;
	}

	const float ViewPortBase::GetAspect()
	{
		return static_cast<float>(m_viewport.Width) / static_cast<float>(m_viewport.Height);
	}
	DefaultViewPort::DefaultViewPort()
	{
	}


	DefaultViewPort::DefaultViewPort(const D3D12_VIEWPORT& view_port)
		:ViewPortBase(view_port)
	{
	}
	DefaultViewPort::~DefaultViewPort()
	{
	}

	bool DefaultViewPort::Initialize()
	{
		return true;
	}
	bool DefaultViewPort::Initialize(D3D12_VIEWPORT& view_port)
	{
		m_viewport = view_port;
		m_scissorrect.top = 0;
		m_scissorrect.left = 0;
		m_scissorrect.right = m_scissorrect.left + static_cast<LONG>(m_viewport.Width);
		m_scissorrect.bottom = m_scissorrect.top + static_cast<LONG>(m_viewport.Height);
		return true;
	}
	bool DefaultViewPort::Initialize(int width, int height)
	{
		m_viewport.Width = static_cast<float>(width);
		m_viewport.Height = static_cast<float>(height);
		m_viewport.TopLeftX = 0;
		m_viewport.TopLeftY = 0;
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;

		m_scissorrect.top = 0;
		m_scissorrect.left = 0;
		m_scissorrect.right = m_scissorrect.left + static_cast<LONG>(m_viewport.Width);
		m_scissorrect.bottom = m_scissorrect.top + static_cast<LONG>(m_viewport.Height);
		return true;
	}

	bool DefaultViewPort::Finalize()
	{
		return true;
	}


}