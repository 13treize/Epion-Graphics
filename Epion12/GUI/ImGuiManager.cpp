#include"../Epion12.h"
#include "ImGuiManager.h"

namespace
{
}

namespace epion::GUI
{
	void ImGuiManager::Init(HWND& hwnd, com_ptr<ID3D12Device>& device, com_ptr<ID3D12DescriptorHeap>& heap_imgui)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		ImGui::StyleColorsDark();

		//ImGuiStyle& style = ImGui::GetStyle();
		//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		//{
		//	style.WindowRounding = 0.0f;
		//	style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		//}
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX12_Init(device.Get(),//DirectX12デバイス
			2,//frames_in_flightと説明にはあるがflightの意味が掴めず(後述)
			DXGI_FORMAT_R8G8B8A8_UNORM,//書き込み先RTVのフォーマット
			heap_imgui.Get(),//imgui用デスクリプタヒープ
			heap_imgui->GetCPUDescriptorHandleForHeapStart(),//CPUハンドル
			heap_imgui->GetGPUDescriptorHandleForHeapStart());//GPUハンドル

	}
	void ImGuiManager::Release()
	{
		ImGui_ImplDX12_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}
	void ImGuiManager::Begin()
	{
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiManager::End(com_ptr<ID3D12GraphicsCommandList>& cmd_list, com_ptr<ID3D12DescriptorHeap>& heap_imgui)
	{
		ImGui::Render();
		cmd_list->SetDescriptorHeaps(1, heap_imgui.GetAddressOf());
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cmd_list.Get());
	}

	void ImGuiManager::UpdatePlatformWindow(com_ptr<ID3D12GraphicsCommandList>& cmd_list)
	{
		//ImGuiIO& io = ImGui::GetIO();
		//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		//{
		//	ImGui::UpdatePlatformWindows();
		//	ImGui::RenderPlatformWindowsDefault(nullptr, reinterpret_cast<void*>(cmd_list.Get()));
		//}
	}
}