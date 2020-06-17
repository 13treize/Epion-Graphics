#pragma once

namespace epion::GUI
{
	namespace ImColors
	{
		namespace	U32
		{
			static ImU32 RED = IM_COL32(250, 0, 0, 250);
			static ImU32 GREEN = IM_COL32(0, 250, 0, 250);
			static ImU32 BLUE = IM_COL32(0, 0, 250, 250);
			static ImU32 BLACK = IM_COL32(0, 0, 0, 250);
			static ImU32 LAWNGREEN = IM_COL32(124, 252, 0, 250);
			static ImU32 YELLOW = IM_COL32(255, 255, 0, 250);
			static ImU32 LIGHTBLUE = IM_COL32(0, 255, 255, 250);
			static ImU32 REDPURPLE = IM_COL32(255, 0, 124, 250);
			static ImU32 PURPLE = IM_COL32(255, 0, 255, 250);
			static ImU32 WHITE = IM_COL32(255, 255, 255, 250);
			static ImU32 GRAY = IM_COL32(128, 128, 128, 250);
			static ImU32 GRAYWHITE = IM_COL32(204, 204, 204, 250);
			static ImU32 GRAYBLACK = IM_COL32(77, 77, 77, 250);

			static ImU32 ZERO = IM_COL32(0, 0, 0, 0);
		}

		namespace	Vec4
		{
			static ImVec4	BLACK = { 0, 0, 0, 255 };
			static ImVec4	WHITE = { 255, 255, 255, 255 };
		}
	}
	void Begin(const std::string& bar_title, ImGuiWindowFlags flags);
	void End();
	void ShowFPS();
	void DrawGrid(ImDrawList* draw_list, float	size, ImU32	color, const	ImVec2& scroll);

	class ImGuiFunction
	{
	public:
		static void DefaultWindowFlagsSetiing(ImGuiWindowFlags& window_flags);

		static Math::FVector2 GetFVector2(ImVec2& vec2)
		{
			return Math::FVector2(vec2.x, vec2.y);
		}
		static ImVec2 GetImVec2(Math::FVector2& vec2)
		{
			return ImVec2(vec2.x, vec2.y);
		}
	};
}