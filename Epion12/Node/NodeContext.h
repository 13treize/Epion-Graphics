#pragma once
namespace	epion::Node
{
	class NodeBase;
	class NodeLink;

	struct ContextData
	{
		std::vector<std::string> Name;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(Name));
		}

	};
	struct MenuItemState
	{
		std::string Name;
		bool IsOpen;
		std::vector<MenuItemState> ItemChild;
	};
	class NodeMenuContext final :public GUI::ContextObject
	{
	public:
		NodeMenuContext();
		~NodeMenuContext();
		void OpenMenu() override;
		void CloseMenu() override;
		void PopupBeginSettings() override;
		void PopupEndSettings() override;
		void ContextMenu(std::string_view popup_name, bool& is_event) override;

	private:
		std::array<MenuItemState,NodeType::ArraySize>m_menu_item_states;
	};
	
	class NodeTypeMenuContext final :public GUI::ContextObject
	{
	public:
		NodeTypeMenuContext();
		~NodeTypeMenuContext();
		void Update();
		void OpenMenu() override;
		void CloseMenu() override;
		void PopupBeginSettings() override;
		void PopupEndSettings() override;
		void ContextMenu(std::string_view popup_name, bool& is_event) override;

		void ContextChild(std::vector<std::unique_ptr<Node::NodeBase>>& nodes);

	private:
		std::array<ContextData, NodeType::ArraySize> m_context_data;
		std::array<MenuItemState, NodeType::ArraySize>m_menu_item_states;
		bool m_is_first_click;

		int m_create_node_count;
	};

	template<class First>
	static inline void SetFalse(First& first)
	{
		first = false;
	}

	template<class First, class... Args>
	static inline void SetFalse(First& first, Args&... args)
	{
		first = false;
		SetFalse(args...);
	}

	template <class T = epion::Node::NodeBase>
	static inline void MenuCreateNode(std::vector<std::unique_ptr<Node::NodeBase>>& nodes, std::string_view name, ImVec2& pos, int& count, bool& is_open)
	{
		static_assert(std::is_base_of<epion::Node::NodeBase, T>::value == true, "BaseClass not NodeBase");
		//if (ImGui::MenuItem(name.data()))
		if(GUI::MenuItem(name, is_open))
		{
			nodes.push_back(std::make_unique<T>(name,count, Math::FVector2(pos.x, pos.y)));
			count++;
			is_open = false;
			//	SetFalse(first, args...);
		}
	};
}