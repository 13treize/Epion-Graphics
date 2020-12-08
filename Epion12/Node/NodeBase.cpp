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
			if (ImGui::ColorButton(m_previous_name.c_str(), m_backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40)))
				m_color = m_backup_color;
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
		//	std::string	m_color_button_name;

		popup = ImGui::ColorButton(m_color_button_name.c_str(), ImVec4(num.x, num.y, num.z, 1.0f), m_edit_flags);
		ImGui::SameLine();
		//	std::string	m_button_name;

		popup |= ImGui::Button(m_button_name.c_str());

		Activate(popup, num);
		num = m_ret_color;
	}

	NodeBase::NodeBase(std::string_view name, int id, const Math::FVector2& pos)
		:m_Name(name), m_ID(id), m_Pos(pos), m_is_push(false), m_is_double_clicked(false)
	{
		m_NodeType = NODE_STATE::NORMAL;

		NodeParam data;
		FileIO::FileIOManager::InputJson<NodeParam>("Epion12\\Settings\\NodeSetting.json", name, data);
		auto input_num = data.Inputs.size();
		auto output_num = data.Outputs.size();
		m_Inputs.clear();
		m_Outputs.clear();
		m_is_slot_input.clear();
		for (int i = 0; i < input_num; i++)
		{
			m_Inputs.push_back({ data.Inputs[i].Name,data.Inputs[i].SlotType,{0.0f,0.0f,0.0f,0.0f},pos,GUI::ImColors::U32::BLACK,{} });
			m_is_slot_input.push_back(INPUT_SLOT_STATE::ZERO);

		}
		for (int o = 0; o < output_num; o++)
		{
			m_Outputs.push_back({ data.Outputs[o].Name,data.Outputs[o].SlotType,pos,GUI::ImColors::U32::BLACK,{} });
		}

		SizeSetting(input_num, output_num);
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
		m_DrawPos = GUI::ImGuiFunction::GetImVec2(m_Pos) + offset;
		ImVec2 node_rect_size = m_DrawPos + GUI::ImGuiFunction::GetImVec2(m_Size);
		ImVec2 node_rect_max = m_DrawPos + ImVec2(m_Size.x * 0.5f, m_Size.y) * scroll_scale;
		ImVec2 title_bar_pos = m_DrawPos + ImVec2(m_Size.x, 18.0f) * scroll_scale;
		draw_list->AddRectFilled(m_DrawPos, title_bar_pos, TITLE_BAR_COLOR, 2.0f);
		ImGui::SetCursorScreenPos(m_DrawPos + NODE_FONT_ADD_POS);	//ノードのタイトル描画の座標を指定
		draw_list->AddRectFilled(m_DrawPos, node_rect_size, RECT_COLOR, 2.0f);
		if (m_NodeType != NODE_STATE::MASTER)
		{
			draw_list->AddRectFilled(m_DrawPos, node_rect_max, RECT_COLOR, 2.0f);
		}
		draw_list->AddRectFilled(m_DrawPos, title_bar_pos, TITLE_BAR_COLOR, 2.0f);
		ImGui::SetCursorScreenPos(m_DrawPos + NODE_FONT_ADD_POS);	//ノードのタイトル描画の座標を指定
		ImGui::TextColored(GUI::ImColors::Vec4::WHITE, "%s", m_Name.c_str());
		ImGui::SetWindowFontScale(0.9f * scroll_scale);

		auto input_size = m_Inputs.size();
		auto output_size = m_Outputs.size();
		if (m_is_push && !m_is_double_clicked)
		{
			draw_list->AddRect(m_DrawPos, node_rect_size, GUI::ImColors::U32::GREEN);
		}
		if (m_is_double_clicked)
		{
			draw_list->AddRect(m_DrawPos, node_rect_size, GUI::ImColors::U32::REDPURPLE);
		}
		for (int i = 0; i < input_size; i++)
		{
			m_Inputs[i].Pos = GUI::ImGuiFunction::GetFVector2(offset) + GetInputSlotPos(i, Math::FVector2(0.0f, 10.0f));
			GUI::ImGuiFunction::DrawFont(GUI::ImGuiFunction::GetImVec2(m_Inputs[i].Pos + Math::FVector2(10.0f, -SLOT_INPUT_FLOAT)), m_Inputs[i].Name);
			NodeFunction::NodeCircle(draw_list, GUI::ImGuiFunction::GetImVec2(m_Inputs[i].Pos), NODE_SLOT_RADIUS, m_Inputs[i].SlotType);
			NodeFunction::HitCircle(draw_list, m_Inputs[i].Pos, GUI::ImColors::U32::GREEN);
		}
		for (int i = 0; i < output_size; i++)
		{
			m_Outputs[i].Pos = GUI::ImGuiFunction::GetFVector2(offset) + GetOutputSlotPos(i, Math::FVector2(0.0f, 10.0f));
			GUI::ImGuiFunction::DrawFont(GUI::ImGuiFunction::GetImVec2(m_Outputs[i].Pos + Math::FVector2(-50.0f, -SLOT_INPUT_FLOAT)), m_Outputs[i].Name);
			NodeFunction::NodeCircle(draw_list, GUI::ImGuiFunction::GetImVec2(m_Outputs[i].Pos), NODE_SLOT_RADIUS, m_Outputs[i].SlotType);
			NodeFunction::HitCircle(draw_list, m_Outputs[i].Pos, GUI::ImColors::U32::RED);
		}

		draw_list->ChannelsSetCurrent(0); // input_slot
		for (int i = 0; i < input_size; i++)
		{
			if (m_is_slot_input[i] == INPUT_SLOT_STATE::ZERO)
			{
				draw_list->AddLine(GUI::ImGuiFunction::GetImVec2(m_Inputs[i].Pos) + ImVec2(-20, 0), GUI::ImGuiFunction::GetImVec2(m_Inputs[i].Pos), GUI::ImColors::U32::GREEN, 1.0f);
				NodeFunction::InputRectDraw(draw_list, GUI::ImGuiFunction::GetImVec2(m_Inputs[i].Pos), m_Inputs[i].SlotType);
				if (m_Inputs[i].SlotType == SLOT_TYPE::COLOR)
				{
					m_color_picker[0].SetInputSlotColor2(GUI::ImGuiFunction::GetImVec2(m_Inputs[i].Pos), m_open_popup[0], m_Inputs[i].InputData, 1);
				}
				else
				{
					NodeFunction::SetInputSlotDynamic(GUI::ImGuiFunction::GetImVec2(m_Inputs[i].Pos), m_Inputs[i].InputData, m_Inputs[i].SlotType, i * static_cast<int>(input_size));
				}
			}
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
		if (m_is_slot_input[index] == INPUT_SLOT_STATE::ONE)
		{
			return true;
		}
		return false;
	}

	void NodeBase::SetPos(const Math::FVector2& pos)
	{
		m_Pos = pos;
	}

	void NodeBase::SetDrawPos(const ImVec2& draw_pos)
	{
		m_DrawPos = draw_pos;
	}

	void NodeBase::SetIsSlotInput(int index, INPUT_SLOT_STATE type)
	{
		m_is_slot_input[index] = type;
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
		if (input < output)
		{
			m_Size = { SIZE_BASE * output ,SIZE_BASE * output };
		}
		else
		{
			m_Size = { SIZE_BASE * input ,SIZE_BASE * input };
		}
		if (input == 1 && output == 1)
		{
			m_Size = { 130.0f,SIZE_BASE };
		}

		if (input == 0)
		{
			m_Size = { SIZE_BASE * output + 30.0f,SIZE_BASE * output };
		}
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
		:NodeBase("Default", -1, Math::FVector2(0,0))
	{

	}

	FunctionNode::FunctionNode(std::string_view name, int id, const Math::FVector2& pos)
		:NodeBase(name, id, pos)
	{

	}
	FunctionNode::~FunctionNode()
	{
	}

}