#pragma once

namespace epion::GUI
{
	class ImGuiManager final
	{
	public:
		static	void	Init(HWND& hwnd, com_ptr<ID3D12Device>& device, com_ptr<ID3D12DescriptorHeap>& heap_imgui);
		static	void	Release();

		//	毎フレーム必要な処理
		static	void	Begin();
		static	void	End(com_ptr<ID3D12GraphicsCommandList>& cmd_list, com_ptr<ID3D12DescriptorHeap>& heap_imgui);
		static	void	UpdatePlatformWindow(com_ptr<ID3D12GraphicsCommandList>& cmd_list);
	private:

	};
}
