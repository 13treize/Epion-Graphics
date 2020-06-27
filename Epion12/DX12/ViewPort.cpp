#include	"../Epion12.h"
#include	"ViewPort.h"


namespace epion::DX12
{
	D3D12_VIEWPORT ViewPort::m_viewport;
	D3D12_RECT ViewPort::m_scissorrect;
	Math::Vector2<int> ViewPort::m_screen_size;


	bool ViewPort::Initialize()
	{
		m_viewport.Width = static_cast<FLOAT>(m_screen_size.x);//�o�͐�̕�(�s�N�Z����)
		m_viewport.Height = static_cast<FLOAT>(m_screen_size.y);//�o�͐�̍���(�s�N�Z����)
		m_viewport.TopLeftX = 0;//�o�͐�̍�����WX
		m_viewport.TopLeftY = 0;//�o�͐�̍�����WY
		m_viewport.MaxDepth = 1.0f;//�[�x�ő�l
		m_viewport.MinDepth = 0.0f;//�[�x�ŏ��l

		m_scissorrect.top = 0;//�؂蔲������W
		m_scissorrect.left = 0;//�؂蔲�������W
		m_scissorrect.right = m_scissorrect.left + static_cast<LONG>(m_screen_size.x);//�؂蔲���E���W
		m_scissorrect.bottom = m_scissorrect.top + static_cast<LONG>(m_screen_size.y);//�؂蔲�������W

		return true;
	}
	bool ViewPort::Finalize()
	{
		return true;
	}

	void ViewPort::RSSets(com_ptr<ID3D12GraphicsCommandList>& cmd_list)
	{
		cmd_list->RSSetViewports(1, &m_viewport);
		cmd_list->RSSetScissorRects(1, &m_scissorrect);
	}

	void ViewPort::SetScreenSize(const Math::Vector2<int>& screen_size)
	{
		m_screen_size = screen_size;
	}

	const Math::Vector2<int>& ViewPort::GetScreenSize()
	{
		return m_screen_size;
	}
	const float ViewPort::GetAspect()
	{
		return static_cast<float>(m_screen_size.x / m_screen_size.y);
	}

}