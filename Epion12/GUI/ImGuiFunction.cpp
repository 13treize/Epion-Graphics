#include "../Epion12.h"
#include "EpionGUI.h"
#include "ImGuiFunction.h"

namespace
{

}

namespace epion::GUI
{
	void Begin(const std::string& bar_title, ImGuiWindowFlags flags)
	{
		if (!ImGui::Begin(bar_title.c_str(), nullptr, flags))
		{
			ImGui::End();
			return;
		}
	}
	void End()
	{
		ImGui::End();
	}

	void ShowFPS()
	{
		auto& io = ImGui::GetIO();
		ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);
	}
	void DrawGrid(ImDrawList* draw_list, float	size, ImU32	color, const	ImVec2& scroll)
	{
		ImVec2 win_pos = ImGui::GetCursorScreenPos();
		ImVec2 canvas_size = ImGui::GetWindowSize();

		for (float x = fmodf(scroll.x, size); x < canvas_size.x; x += size)
		{
			draw_list->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, canvas_size.y) + win_pos, color);
		}

		for (float y = fmodf(scroll.y, size); y < canvas_size.y; y += size)
		{
			draw_list->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(canvas_size.x, y) + win_pos, color);
		}
	}

}