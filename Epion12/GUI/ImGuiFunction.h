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
	void CloseContext(bool& is_current);
	void BackContext(bool& is_back, bool& is_current);
	void TextMenu(std::string_view name);

	bool IsLeftMouseDown();
	bool IsRightClick();
	bool MenuItem(std::string_view name, bool& is_event);
	class MenuItemBase
	{
	public:
		MenuItemBase() {}
		~MenuItemBase() {}
		bool Show(std::string_view name, bool& is_event)
		{
			MenuItem(name, is_event);
		}
	};
	class MenuItems
	{
	public:
		void ShowItems()
		{

		}
	private:
		std::vector<MenuItemBase>	Items;
	};
	class ContextObject abstract
	{
	public:
		ContextObject()
			:m_menu_pos(0.0f, 0.0f), m_is_open_menu(false)
		{
		}

		virtual	~ContextObject() {};

		virtual void OpenMenu() = 0;
		virtual void CloseMenu() = 0;

		virtual void PopupBeginSettings() = 0;
		virtual void PopupEndSettings() = 0;
		virtual void ContextMenu(std::string_view popup_name, bool& is_event)=0;
	protected:
		ImVec2 m_menu_pos;
		bool m_is_open_menu;

	};

	class ImGuiFunction
	{
	public:
		static void DefaultWindowFlagsSetiing(ImGuiWindowFlags& window_flags);

		static void DrawFont(const ImVec2& pos,std::string_view name)
		{
			ImGui::SetCursorScreenPos(pos);
			ImGui::TextColored(GUI::ImColors::Vec4::WHITE, "%s",name.data());
		}
		static Math::FVector2 GetFVector2(ImVec2& vec2)
		{
			return Math::FVector2(vec2.x, vec2.y);
		}
		static Math::FVector2 GetFVector2(const ImVec2& vec2)
		{
			return Math::FVector2(vec2.x, vec2.y);
		}

		static ImVec2 GetImVec2(Math::FVector2& vec2)
		{
			return ImVec2(vec2.x, vec2.y);
		}
		static ImVec2 GetImVec2(const Math::FVector2& vec2)
		{
			return ImVec2(vec2.x, vec2.y);
		}

	};
}