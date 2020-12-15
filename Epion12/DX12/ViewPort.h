#pragma once
/**
 * @file ViewPort.h
 * @brief ViewPortクラス
 * @author treize
 * @date 2020/02/21
 * @details ViewPort、RECTをもつ、わざわざクラスにすんのか微妙、カメラに持たせるか検討
 */
namespace epion::DX12
{
	class ViewPortBase
	{
	public:
		ViewPortBase();
		ViewPortBase(const D3D12_VIEWPORT& view_port);
		virtual ~ViewPortBase() {};
		virtual bool Initialize() = 0;
		virtual bool Finalize() = 0;
		void RSSets(com_ptr<ID3D12GraphicsCommandList>& cmd);
		D3D12_VIEWPORT Get();
		D3D12_RECT GetRect();
		const float GetAspect();
	protected:
		D3D12_VIEWPORT m_viewport;
		D3D12_RECT m_scissorrect;
	};
	class DefaultViewPort final :public ViewPortBase
	{
	public:
		DefaultViewPort();
		DefaultViewPort(const D3D12_VIEWPORT& view_port);
		~DefaultViewPort();
		bool Initialize() override;
		bool Initialize(D3D12_VIEWPORT& view_port);
		bool Initialize(int width,int height);
		bool Finalize() override;
	private:

	};
}