#pragma once
/**
 * @file ViewPort.h
 * @brief ViewPort�N���X
 * @author treize
 * @date 2020/02/21
 * @details ViewPort�ARECT�����A�킴�킴�N���X�ɂ���̂������A�J�����Ɏ������邩����
 */
namespace epion::DX12
{
	class ViewPort final
	{
	public:
		static bool	Initialize();
		static bool	Finalize();

		static void	RSSets(com_ptr<ID3D12GraphicsCommandList>& cmd_list);
		static void	SetScreenSize(const Math::Vector2<int>& screen_size);

		static const Math::Vector2<int>& GetScreenSize();

		static const float GetAspect();
	private:
		static D3D12_VIEWPORT m_viewport;
		static D3D12_RECT m_scissorrect;
		static Math::Vector2<int> m_screen_size;
	};
}