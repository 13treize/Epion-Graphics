#include	"../Epion12.h"

#include "../GUI/ImGuiFunction.h"
#include "../FileIO/EpionFileIO.h"

#include "NodeParam.h"
#include "NodeBase.h"

namespace
{
	constexpr float SIZE_BASE = 47.0f;
}
CEREAL_REGISTER_TYPE(epion::Node::FunctionNode)

namespace epion::Node
{
	ColorPicker2::ColorPicker2()
		: m_edit_flags(0)
	{
	}
	ColorPicker2::~ColorPicker2()
	{
	}

	void	ColorPicker2::Init(std::string_view str, std::string_view str2)
	{
		std::string str3 = str.data();
		m_backup_color = ImVec4(0, 0, 0, 0);
		m_color = ImVec4(0, 0, 0, 0);
		m_popup_name = "mypicker" + str3;
		m_picker_name = "##picker" + str3;
		m_current_name = "##current" + str3;
		m_previous_name = "##previous" + str3;
		m_color_button_name = "MyColor" + str3;
		m_button_name = str2;
	}

	void	ColorPicker2::Activate(bool is_popup, Math::FVector4& color)
	{
		if (is_popup)
		{
			ImGui::OpenPopup(m_popup_name.c_str());
			m_backup_color.x = color.x;
			m_backup_color.y = color.y;
			m_backup_color.z = color.z;
			m_backup_color.w = 1.0;
		}
		if (ImGui::BeginPopup(m_popup_name.c_str()))
		{
			ImGui::Text("ColorPicker");
			ImGui::Separator();
			ImGui::ColorPicker4(m_picker_name.c_str(), (float*)&m_color, m_edit_flags);
			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::Text("Current");
			ImGui::ColorButton(m_current_name.c_str(), m_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));
			ImGui::Text("Previous");
			if (ImGui::ColorButton(m_previous_name.c_str(), m_backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40)))	m_color = m_backup_color;
			ImGui::EndGroup();
			ImGui::EndPopup();
		}

		m_ret_color.x = m_color.x;
		m_ret_color.y = m_color.y;
		m_ret_color.z = m_color.z;
	}

	void	ColorPicker2::SetInputSlotColor2(const ImVec2& set_cursor, bool popup, Math::FVector4& num, int label_num)
	{
		m_edit_flags |= ImGuiColorEditFlags_AlphaBar;
		m_edit_flags |= ImGuiColorEditFlags_NoSidePreview;
		m_edit_flags |= ImGuiColorEditFlags_PickerHueBar;
		m_edit_flags |= ImGuiColorEditFlags_Float;
		ImGui::SetCursorScreenPos(set_cursor + ImVec2(-90, -8));
		popup = ImGui::ColorButton(m_color_button_name.c_str(), ImVec4(num.x, num.y, num.z, 1.0f), m_edit_flags);
		ImGui::SameLine();
		popup |= ImGui::Button(m_button_name.c_str());
		Activate(popup, num);
		num = m_ret_color;
	}

	NodeBase::NodeBase(NodeType type, std::string_view name, int id, const Math::FVector2& pos)
		:m_Name(name), m_ID(id), m_Pos(pos), m_is_push(false), m_is_double_clicked(false)
	{
		m_NodeType = NODE_STATE::NORMAL;
		NodeParam data;
		FileSetting(type, name,data);
		SizeSetting(data.Inputs.size(), data.Outputs.size());
		m_Inputs.clear();
		m_Outputs.clear();
		for (const auto& i : data.Inputs)
		{
			m_Inputs.push_back({ i.Name,i.SlotType,i.InputData,pos,GUI::ImColors::U32::BLACK,{},INPUT_SLOT_STATE::ZERO });
		}
		for (const auto& o : data.Outputs)
		{
			m_Outputs.push_back({ o.Name,o.SlotType,pos,GUI::ImColors::U32::BLACK,{} });
		}

		m_open_popup[0] = false;
		m_color_picker[0].Init("1", "Color");
		m_open_popup[1] = false;
		m_color_picker[1].Init("2", "Color ");
		m_open_popup[2] = false;
		m_color_picker[2].Init("3", "Color  ");
	}
	void	NodeBase::Draw(ImDrawList* draw_list, const ImVec2& offset, float scroll_scale)
	{
		draw_list->ChannelsSetCurrent(1);
		ImGui::SetWindowFontScale(1.0f);
		ImVec2 draw_pos = GUI::ImGuiFunction::GetImVec2(m_Pos) + offset;
		ImVec2 node_rect_size = draw_pos + GUI::ImGuiFunction::GetImVec2(m_Size);
		ImVec2 node_rect_max = draw_pos + ImVec2(m_Size.x * 0.5f, m_Size.y) * scroll_scale;
		ImVec2 title_bar_pos = draw_pos + ImVec2(m_Size.x, 18.0f) * scroll_scale;
		draw_list->AddRectFilled(draw_pos, title_bar_pos, TITLE_BAR_COLOR, 2.0f);
		ImGui::SetCursorScreenPos(draw_pos + NODE_FONT_ADD_POS);	//ノードのタイトル描画の座標を指定
		draw_list->AddRectFilled(draw_pos, node_rect_size, RECT_COLOR, 2.0f);
		if (m_NodeType != NODE_STATE::MASTER)
		{
			draw_list->AddRectFilled(draw_pos, node_rect_max, RECT_COLOR, 2.0f);
		}
		draw_list->AddRectFilled(draw_pos, title_bar_pos, TITLE_BAR_COLOR, 2.0f);
		ImGui::SetCursorScreenPos(draw_pos + NODE_FONT_ADD_POS);	//ノードのタイトル描画の座標を指定
		ImGui::TextColored(GUI::ImColors::Vec4::WHITE, "%s", m_Name.c_str());
		ImGui::SetWindowFontScale(0.9f * scroll_scale);

		if (m_is_push && !m_is_double_clicked)	draw_list->AddRect(draw_pos, node_rect_size, GUI::ImColors::U32::GREEN);
		if (m_is_double_clicked)	draw_list->AddRect(draw_pos, node_rect_size, GUI::ImColors::U32::REDPURPLE);

		int index = 0;
		for (auto& i : m_Inputs)
		{
			i.Pos = GUI::ImGuiFunction::GetFVector2(offset) + GetInputSlotPos(index, Math::FVector2(0.0f, 10.0f));
			GUI::ImGuiFunction::DrawFont(GUI::ImGuiFunction::GetImVec2(i.Pos + Math::FVector2(10.0f, -SLOT_INPUT_FLOAT)),i.Name);
			NodeFunction::NodeCircle(draw_list, GUI::ImGuiFunction::GetImVec2(i.Pos), NODE_SLOT_RADIUS, i.SlotType);
			NodeFunction::HitCircle(draw_list, i.Pos, GUI::ImColors::U32::GREEN);
			index++;
		}
		index = 0;
		for (auto& o : m_Outputs)
		{
			o.Pos = GUI::ImGuiFunction::GetFVector2(offset) + GetOutputSlotPos(index, Math::FVector2(0.0f, 10.0f));
			GUI::ImGuiFunction::DrawFont(GUI::ImGuiFunction::GetImVec2(o.Pos + Math::FVector2(-50.0f, -SLOT_INPUT_FLOAT)), o.Name);
			NodeFunction::NodeCircle(draw_list, GUI::ImGuiFunction::GetImVec2(o.Pos), NODE_SLOT_RADIUS, o.SlotType);
			NodeFunction::HitCircle(draw_list,o.Pos, GUI::ImColors::U32::RED);
			index++;
		}
		draw_list->ChannelsSetCurrent(0); // input_slot
		for (auto& i : m_Inputs)
		{
			if (i.SlotInputState == INPUT_SLOT_STATE::ZERO)
			{
				draw_list->AddLine(GUI::ImGuiFunction::GetImVec2(i.Pos) + ImVec2(-20, 0), GUI::ImGuiFunction::GetImVec2(i.Pos), GUI::ImColors::U32::GREEN, 1.0f);
				NodeFunction::InputRectDraw(draw_list, GUI::ImGuiFunction::GetImVec2(i.Pos),i.SlotType);
				if (i.SlotType != SLOT_TYPE::COLOR)
				{
					NodeFunction::SetInputSlotDynamic(GUI::ImGuiFunction::GetImVec2(i.Pos), i.InputData,i.SlotType, index *sizeof(i));
				}
				else
				{
					m_color_picker[0].SetInputSlotColor2(GUI::ImGuiFunction::GetImVec2(i.Pos), m_open_popup[0],i.InputData, 1);
				}
			}
			index++;
		}
	}

	const int NodeBase::GetID() const
	{
		return m_ID;
	}
	SLOT_TYPE NodeBase::GetInputSlotType(size_t id) const
	{
		return m_Inputs[id].SlotType;
	}
	SLOT_TYPE NodeBase::GetOutputSlotType(size_t id) const
	{
		return m_Outputs[id].SlotType;
	}

	const size_t	NodeBase::GetInputsSize() const
	{
		return m_Inputs.size();
	}
	const size_t	NodeBase::GetOutputsSize() const
	{
		return m_Outputs.size();
	}

	const Math::FVector2& NodeBase::GetPos() const
	{
		return m_Pos;
	}

	const Math::FVector2& NodeBase::GetSize() const
	{
		return m_Size;
	}


	const Math::FVector2 NodeBase::GetInputSlotPos(int slot_no, const Math::FVector2& adjustment_pos) const
	{
		Math::FVector2 pos(m_Pos.x + SLOT_POS, m_Pos.y + m_Size.y * (static_cast<float>(slot_no) + 1) / (static_cast<float>(m_Inputs.size()) + 1));
		return pos + adjustment_pos;
	}
	const Math::FVector2 NodeBase::GetOutputSlotPos(int slot_no, const Math::FVector2& adjustment_pos) const
	{
		Math::FVector2 pos(m_Pos.x + m_Size.x - SLOT_POS, m_Pos.y + m_Size.y * (static_cast<float>(slot_no) + 1) / (static_cast<float>(m_Outputs.size()) + 1));
		return pos + adjustment_pos;
	}
	bool NodeBase::GetIsPush()
	{
		return m_is_push;
	}
	bool NodeBase::GetIsSlotInputONE(int index)
	{
		if (m_Inputs[index].SlotInputState == INPUT_SLOT_STATE::ONE)
		{
			return true;
		}
		return false;
	}
	void NodeBase::SetPos(const Math::FVector2& pos)
	{
		m_Pos = pos;
	}
	void NodeBase::SetIsSlotInput(int index, INPUT_SLOT_STATE type)
	{
		m_Inputs[index].SlotInputState = type;
	}
	void NodeBase::PushEventBegin()
	{
		m_is_push = true;
	}
	void NodeBase::PushEventEnd()
	{
		m_is_push = false;
	}

	void NodeBase::SizeSetting(const size_t input, const size_t output)
	{
		if (input < output)	m_Size = { SIZE_BASE * output ,SIZE_BASE * output };
		else m_Size = { SIZE_BASE * input ,SIZE_BASE * input };
		if (input == 1 && output == 1)	m_Size = { 130.0f,SIZE_BASE };
		if (input == 0)	m_Size = { SIZE_BASE * output + 30.0f,SIZE_BASE * output };
	}
	void NodeBase::FileSetting(NodeType type, std::string_view name, NodeParam& data)
	{
		std::string file_name = "Epion12\\Settings\\";
		file_name += NodeTypeName.at(type);
		file_name+="Settings.json";
		FileIO::FileIOManager::InputJson<NodeParam>(file_name, name, data);
	}
	NodeLink::NodeLink(int output_id, int output_slot, int input_id, int input_slot)
		:m_output({ { output_id ,output_slot }, SLOT_TYPE::VECTOR1 }),
		m_input({ {input_id, input_slot }, SLOT_TYPE::VECTOR1 }),
		m_is_hit(false), m_is_delete_menu(false)
	{
	}

	NodeLink::NodeLink(int output_id, int output_slot, SLOT_TYPE output_type, int input_id, int input_slot, SLOT_TYPE input_type)
		:m_output({ { output_id ,output_slot }, output_type }),
		m_input({ {input_id, input_slot }, input_type }),
		m_is_hit(false), m_is_delete_menu(false)
	{
	}
	NodeLink::~NodeLink()
	{
	}


	int	NodeLink::GetOutputID()
	{
		return	m_output.LinkData.id;
	}
	int	NodeLink::GetOutputSlot()
	{
		return	m_output.LinkData.slot;
	}
	SLOT_TYPE NodeLink::GetOutputType()
	{
		return m_output.SlotType;
	}
	void NodeLink::SetOutputType(SLOT_TYPE type)
	{
		m_output.SlotType = type;
	}

	//right
	int	NodeLink::GetInputID()
	{
		return	m_input.LinkData.id;
	}
	int	NodeLink::GetInputSlot()
	{
		return	m_input.LinkData.slot;
	}
	SLOT_TYPE NodeLink::GetInputType()
	{
		return m_input.SlotType;
	}

	void NodeLink::SetInputType(SLOT_TYPE type)
	{
		m_input.SlotType = type;
	}

	//Debug Text
	std::string NodeLink::StateStr()
	{
		return
			"out id " + std::to_string(m_output.LinkData.id) + " " +
			"out slot " + std::to_string(m_output.LinkData.slot) + " " +
			"in id " + std::to_string(m_input.LinkData.id) + " " +
			"in slot " + std::to_string(m_input.LinkData.slot);
	}

	FunctionNode::FunctionNode()
		:NodeBase(NodeType::ArraySize, "Default", -1, Math::FVector2(0, 0))
	{
	}

	FunctionNode::FunctionNode(NodeType type, std::string_view name, int id, const Math::FVector2& pos)
		: NodeBase(type, name, id, pos)
	{
	}
	FunctionNode::~FunctionNode()
	{
	}

}