#include "../Epion12.h"
#include "../GUI/ImGuiFunction.h"
#include "NodeParam.h"
#include "NodeBase.h"
namespace
{
}
namespace	epion::Node
{

	//std::string	NodeFunction::SetVarFloat(std::string_view in, std::string_view out) { return "    float " + out.substr() + "=" + in + ";\n"; }
	//std::string	NodeFunction::SetVarFloat2(std::string_view in_x, std::string_view in_y, std::string_view out) { return"    float2 " + out + "=" + "float2(" + in_x + "," + in_y + ");\n"; }
	//std::string	NodeFunction::SetVarFloat3(std::string_view in_x, std::string_view in_y, std::string_view in_z, std::string_view out) { return"    float3 " + out + "=" + "float3(" + in_x + "," + in_y + "," + in_z + ");\n"; }
	//std::string	NodeFunction::SetVarFloat4(std::string_view in_x, std::string_view in_y, std::string_view in_z, std::string_view in_w, std::string_view out) { return"    float4 " + out + "=" + "float4(" + in_x + "," + in_y + "," + in_z + "," + in_w + ");\n"; }

	//std::string	NodeFunction::SetInputToString(float str) { return std::to_string(str); }
	//std::string	NodeFunction::SetInputToString2(Math::FVector2& str) { return "float2(" + StringConverter::to_string2(str, ",") + ")"; }
	//std::string	NodeFunction::SetInputToString3(Math::FVector3& str) { return "float3(" + StringConverter::to_string3(str, ",") + ")"; }
	//std::string	NodeFunction::SetInputToString4(Math::FVector4& str) { return "float4(" + StringConverter::to_string4(str, ",") + ")"; }

	void NodeFunction::SetInputSlotFloat(const ImVec2& set_cursor, std::string_view label, float& num)
	{
		ImGui::SetCursorScreenPos(set_cursor + ImVec2(SLOT_INPUT_POS_X, -SLOT_INPUT_FLOAT));
		ImGui::SetNextItemWidth(30.0f);
		ImGui::InputFloat(label.data(), &num, 0.0f, 1.0f, "%.2f");
	}

	void NodeFunction::SetInputSlotFloat(const ImVec2& set_cursor, float x, std::string_view label, float& num)
	{
		ImGui::SetCursorScreenPos(set_cursor + ImVec2(x, -SLOT_INPUT_FLOAT));
		ImGui::SetNextItemWidth(30.0f);
		ImGui::InputFloat(label.data(), &num, 0.0f, 1.0f, "%.2f");
	 }
	//void NodeFunction::SetInputSlotFloat2(ImVec2& set_cursor, math::FVector2& num, int label_num)
	//{
	//	SetInputSlotFloat(set_cursor, SLOT_INPUT_POS_X, StringConverter::GetSpace(1 + (label_num + 1) * 2), num.x);
	//	SetInputSlotFloat(set_cursor, SLOT_INPUT_POS_X * 2, StringConverter::GetSpace(2 + (label_num + 1) * 2), num.y);
	//}

	//void NodeFunction::SetInputSlotUV(ImVec2& set_cursor)
	//{
	//	ImGui::SetCursorScreenPos(set_cursor + ImVec2(-50, -SLOT_INPUT_FLOAT));
	//	ImGui::TextColored(ImColors::Vec4::WHITE, "%s", "uv");
	//}
	//void NodeFunction::SetInputSlotTexture2D(ImVec2& set_cursor)
	//{
	//	ImGui::SetCursorScreenPos(set_cursor + ImVec2(-50, -SLOT_INPUT_FLOAT));
	//	ImGui::TextColored(ImColors::Vec4::WHITE, "%s", "tex");
	//}
	//void NodeFunction::SetInputSlotSamplerState(ImVec2& set_cursor)
	//{
	//	ImGui::SetCursorScreenPos(set_cursor + ImVec2(-50, -SLOT_INPUT_FLOAT));
	//void NodeFunction::SetInputSlotColor(ImVec2& set_cursor, bool& popup, math::FVector3& num, int label_num)
	//{
	//	ImGui::SetCursorScreenPos(set_cursor + SLOT_INPUT_POS + ImVec2(-30, 0));
	//	popup = ImGui::ColorButton("MyColor", ImVec4(num.x, num.y, num.z, 1.0f), ColorPicker::GetFrag());
	//	ImGui::SameLine();
	//	popup |= ImGui::Button("Color");

	//	ColorPicker::Activate(popup, num);
	//	num = ColorPicker::GetColor();
	//}

	void NodeFunction::SetInputSlotDynamic(const ImVec2& set_cursor, Math::FVector4& num, SLOT_TYPE type, int label_num)
	{
		switch (type)
		{
		case SLOT_TYPE::VECTOR4:	SetInputSlotFloat(set_cursor, (static_cast<float>(type) - 3.0f) * SLOT_INPUT_POS_X, String::StringConverter::GetSpace(static_cast<int>(type) + (label_num + 1) * 4), num.w);
		case SLOT_TYPE::VECTOR3:	SetInputSlotFloat(set_cursor, (static_cast<float>(type) - 2.0f) * SLOT_INPUT_POS_X, String::StringConverter::GetSpace(static_cast<int>(type) - 1 + (label_num + 1) * 4), num.z);
		case SLOT_TYPE::VECTOR2:	SetInputSlotFloat(set_cursor, (static_cast<float>(type) - 1.0f) * SLOT_INPUT_POS_X, String::StringConverter::GetSpace(static_cast<int>(type) - 2 + (label_num + 1) * 4), num.y);
		case SLOT_TYPE::VECTOR1:	SetInputSlotFloat(set_cursor, static_cast<float>(type) * SLOT_INPUT_POS_X, String::StringConverter::GetSpace(static_cast<int>(type) - 3 + (label_num + 1) * 4), num.x);
			break;
		}
	}

	//std::string NodeFunction::SetDefineOutName(std::string	str, int id)
	//{
	//	return str + "_out" + std::to_string(id);
	//}

	//std::string NodeFunction::SetFuncCall(const std::string& str) { return "    " + str + "("; }

	//std::string NodeFunction::SetDefineOutStr1(const std::string& str) { return	"    float " + str + ";\n"; }
	//std::string NodeFunction::SetDefineOutStr2(const std::string& str) { return	"    float2 " + str + ";\n"; }
	//std::string NodeFunction::SetDefineOutStr3(const std::string& str) { return	"    float3 " + str + ";\n"; }
	//std::string NodeFunction::SetDefineOutStr4(const std::string& str) { return	"    float4 " + str + ";\n"; }
	//std::string NodeFunction::SetDefineOutDynamic(const std::string& str, SLOT_TYPE type) { return	"    " + GetType(type) + " " + str + ";\n"; }


	void NodeFunction::InputRectDraw(ImDrawList* draw_list, const ImVec2& pos, SLOT_TYPE type)
	{
		switch (type)
		{
		default:
		case epion::Node::SLOT_TYPE::VECTOR1:
		case epion::Node::SLOT_TYPE::UV:
		case epion::Node::SLOT_TYPE::TEXTURE2D:
		case epion::Node::SLOT_TYPE::SAMPLERSTATE:
			draw_list->AddRectFilled(pos + ImVec2(SLOT_INPUT_RECT_X, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), IM_COL32(60, 60, 60, 255), 2.0f);
			draw_list->AddRect(pos + ImVec2(SLOT_INPUT_RECT_X, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), GUI::ImColors::U32::GREEN, 2.0f);
			break;
		case epion::Node::SLOT_TYPE::VECTOR2:
			draw_list->AddRectFilled(pos + ImVec2(SLOT_INPUT_RECT_X * 2 + 10.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), IM_COL32(60, 60, 60, 255), 2.0f);
			draw_list->AddRect(pos + ImVec2(SLOT_INPUT_RECT_X * 2 + 10.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), GUI::ImColors::U32::GREEN, 2.0f);
			break;
		case epion::Node::SLOT_TYPE::VECTOR3:
			draw_list->AddRectFilled(pos + ImVec2(SLOT_INPUT_RECT_X * 3 + 20.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), IM_COL32(60, 60, 60, 255), 2.0f);
			draw_list->AddRect(pos + ImVec2(SLOT_INPUT_RECT_X * 3 + 20.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), GUI::ImColors::U32::GREEN, 2.0f);
			break;
		case epion::Node::SLOT_TYPE::VECTOR4:
			draw_list->AddRectFilled(pos + ImVec2(SLOT_INPUT_RECT_X * 4 + 30.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), IM_COL32(60, 60, 60, 255), 2.0f);
			draw_list->AddRect(pos + ImVec2(SLOT_INPUT_RECT_X * 4 + 30.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), GUI::ImColors::U32::GREEN, 2.0f);
			break;
		case epion::Node::SLOT_TYPE::COLOR:
			draw_list->AddRectFilled(pos + ImVec2(SLOT_INPUT_RECT_X * 1.8 + 30.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), IM_COL32(60, 60, 60, 255), 2.0f);
			draw_list->AddRect(pos + ImVec2(SLOT_INPUT_RECT_X * 1.8 + 30.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), GUI::ImColors::U32::GREEN, 2.0f);
			break;
		}
	}
	//}
	//std::string	NodeFunction::GetType(SLOT_TYPE type)
	//{
	//	std::string	ret_str = "";
	//	switch (type)
	//	{
	//	case SLOT_TYPE::VECTOR1:	ret_str = "float";	break;
	//	case SLOT_TYPE::VECTOR2:	ret_str = "float2";	break;
	//	case SLOT_TYPE::VECTOR3:	ret_str = "float3";	break;
	//	case SLOT_TYPE::VECTOR4:	ret_str = "float4";	break;
	//	case SLOT_TYPE::COLOR:	break;
	//	case SLOT_TYPE::TEXTURE2D:	break;
	//	case SLOT_TYPE::BOOLEAN:	break;
	//	}
	//	return ret_str;
	//}

	//std::string	NodeFunction::GetSlotTypeName(SLOT_TYPE type)
	//{
	//	std::string	ret_str = "";
	//	switch (type)
	//	{
	//	case SLOT_TYPE::VECTOR1:	ret_str = "(1)";	break;
	//	case SLOT_TYPE::VECTOR2:
	//	case SLOT_TYPE::UV:			ret_str = "(2)";	break;
	//	case SLOT_TYPE::VECTOR3:	ret_str = "(3)";	break;
	//	case SLOT_TYPE::VECTOR4:	ret_str = "(4)";	break;
	//	case SLOT_TYPE::COLOR:	break;
	//	case SLOT_TYPE::TEXTURE2D:	break;
	//	case SLOT_TYPE::BOOLEAN:	break;
	//	}
	//	return ret_str;
	//}

	//void NodeFunction::SetSlotData(math::FVector4& data, std::string& str, SLOT_TYPE type)
	//{
	//	switch (type)
	//	{
	//	case SLOT_TYPE::VECTOR1:	str = std::to_string(data.x); break;
	//	case SLOT_TYPE::VECTOR2:	str = NodeFunction::GetType(type) + "(" + StringConverter::to_string2(data.x, data.y) + ")"; break;
	//	case SLOT_TYPE::VECTOR3:	str = NodeFunction::GetType(type) + "(" + StringConverter::to_string3(data.x, data.y, data.z) + ")"; break;
	//	case SLOT_TYPE::VECTOR4:	str = NodeFunction::GetType(type) + "(" + StringConverter::to_string4(data) + ")"; break;
	//	}
	//}
	ImU32 NodeFunction::CircleColor(SLOT_TYPE type)
	{
		switch (type)
		{
		case SLOT_TYPE::VECTOR1: return GUI::ImColors::U32::LIGHTBLUE;
		case SLOT_TYPE::VECTOR2:return GUI::ImColors::U32::LAWNGREEN;
		case SLOT_TYPE::UV: return GUI::ImColors::U32::LAWNGREEN;
		case SLOT_TYPE::VECTOR3:return GUI::ImColors::U32::YELLOW;
		case SLOT_TYPE::COLOR:return GUI::ImColors::U32::YELLOW;
		case SLOT_TYPE::VECTOR4:return GUI::ImColors::U32::PURPLE;
		case SLOT_TYPE::TEXTURE2D:return GUI::ImColors::U32::RED;
		case SLOT_TYPE::SAMPLERSTATE:return GUI::ImColors::U32::WHITE;
		case SLOT_TYPE::BOOLEAN:return GUI::ImColors::U32::BLUE;
		}
		return GUI::ImColors::U32::BLACK;
	}

	void NodeFunction::NodeCircle(ImDrawList* draw_list, const ImVec2& centrer, float radius, SLOT_TYPE type)
	{
		draw_list->AddCircle(centrer, NODE_SLOT_RADIUS, CircleColor(type));
	}
	void NodeFunction::HitCircle(ImDrawList* draw_list, const Math::FVector2& pos, ImU32 color)
	{
		if (Physics::Collider2D::SphereAndSphere(pos, GUI::ImGuiFunction::GetFVector2(ImGui::GetIO().MousePos), NODE_SLOT_RADIUS, 2.0f))
		{
			draw_list->AddCircleFilled(GUI::ImGuiFunction::GetImVec2(pos), NODE_SLOT_RADIUS-2.0f, color);
		}
	}

}