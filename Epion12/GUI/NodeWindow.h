#pragma once
#include "../Node/NodeParam.h"
#include "../Node/NodeBase.h"

namespace epion::GUI
{
	struct	ClickState
	{
		int	id;
		int	slot;
		ImVec2	pos;
		bool	is_click_display;
		bool	is_click_input_slot;
		bool	is_click_output_slot;
	};


	class NodeWindow
	{
	public:
		bool	Initialize();
		bool	Finalize();
		void	Update();

	private:
		ImGuiTabBarFlags m_bar_flags;

		std::vector<std::unique_ptr<Node::NodeBase>>	m_nodes;
		std::vector<Node::NodeLink>	m_links;
		ImVec2	m_offset;

		ClickState m_click_param;
		float m_scroll_scale;
		int	m_node_select_id;

		bool m_is_context;

		int	m_node_select_num;
		int	m_node_hovered_list;
		int	m_node_hovered_in_scene;

		int m_hit_line_num;
		float m_line_size;
		bool m_is_node_hit;
		bool m_is_line_hit;
		bool m_is_slot_hit;


		bool	m_is_node_widgets_active;
		bool	m_is_now_any_active;
		bool	m_is_old_any_active;

		//std::array<bool, NodeType::ArraySize> is_events;
		//std::array<std::string , NodeType::ArraySize> is_names;

		void Begin();
		void End();

		void ContextUpdate();

		void MouseUpdate(ImDrawList* draw_list);
		void CallContext();

		void Drag(ImDrawList* draw_list);
		void Enclose(ImDrawList* draw_list);
		void Scroll();

		void NodeUpdate(ImDrawList* draw_list);
		void NodeInputUpdate(ImDrawList* draw_list, int size);
		void NodeOutputUpdate(ImDrawList* draw_list, int size);

		void NodeDraw(ImDrawList* draw_list, int size);
		void NodeMouseUpdate(ImDrawList* draw_list, int size);

		void DrawLinkLine(ImDrawList* draw_list);

		bool IsOpenContextMenu();

		void LineDeleteContext();
		void PopUpBegin(std::string_view str);
		void PopUpEnd();

	};
}