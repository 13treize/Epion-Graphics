#pragma once
#include "../Node/NodeParam.h"
#include "../Node/NodeBase.h"

namespace epion::GUI
{
	enum NodeType :unsigned char
	{
		Artistic = 0,
		Channel,
		Input,
		Master,
		Math,
		Procedural,
		Utility,
		UV,
		Noise,
		ArraySize
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

		float m_scroll_scale;
		int	m_node_select_id;

		bool is_context;
		std::array<bool, NodeType::ArraySize> is_events;
		std::array<std::string , NodeType::ArraySize> is_names;

		void NodeUpdate(ImDrawList* draw_list);
		void NodeDraw(ImDrawList* draw_list, int size);
		void NodeMouseUpdate(ImDrawList* draw_list, int size);

	};
}