#pragma once
namespace	epion::Node
{

	enum class SLOT_TYPE
	{
		VECTOR1 = 1,
		VECTOR2,
		VECTOR3,
		VECTOR4,
		BOOLEAN,
		TEXTURE2D,
		TEXTURE3D,
		SAMPLERSTATE,
		POS,//inputのみ、扱いはVECTOR3同じ
		UV,	//inputのみ、扱いはVECTOR2同じ
		COLOR,//inputのみ、扱いはVECTOR3同じ
	};

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
		Hash,
		Noise,
		ArraySize
	};

	static constexpr std::array<std::string_view, NodeType::ArraySize> NodeTypeName =
	{
		"Artistic",
		"Channel",
		"Input",
		"Master",
		"Math",
		"Procedural",
		"Utility",
		"UV",
		"Hash",
		"Noise",
	};
	enum class NODE_STATE :unsigned char
	{
		NORMAL,
		DYNAMIC,
		MASTER,
		VARIABLE,
	};

	//刺さったnodeの数
	enum class INPUT_SLOT_STATE :unsigned char
	{
		ZERO,
		ONE,
		OUTOFRANGE,
	};

	static constexpr int INIT_NUM = -1;
	static constexpr int SLOT_POS = 10;
	static constexpr float SLOT_INPUT_RECT_X = -70.0f;
	static constexpr float SLOT_INPUT_FLOAT = 8;

	const ImVec2 NODE_MIN_SIZE = { 80.0f, 50.0f };

	static constexpr float NODE_SIZE = 35.0f;

	static constexpr float SLOT_INPUT_POS_X = -60.0f;
	const ImVec2 SLOT_INPUT_POS = { SLOT_INPUT_POS_X, -SLOT_INPUT_FLOAT };

	static constexpr float NODE_SLOT_RADIUS = 5.0f;
	const ImVec2 NODE_FONT_ADD_POS = { 10.0f, 5.0f };


	const ImVec2 BEZIERCURVE_LEFT_POS = { 80.0f, 0.0f };

	const ImVec2 BEZIERCURVE_RIGHT_POS = { -80.0f, 0.0f };

	const ImU32	NODE_LINE_COLOR = IM_COL32(0, 150, 250, 250);
	const ImU32	NODE_LINE_HIT_COLOR = IM_COL32(0, 250, 120, 250);



	const ImU32 RECT_COLOR = IM_COL32(60, 60, 60, 200);
	const ImU32 TITLE_BAR_COLOR = IM_COL32(40, 40, 40, 250);

	static constexpr float TITLE_BAR_POS_Y = 18.0f;

	const	ImVec2	NODE_WINDOW_PADDING = { 165.0f, 165.0f };

	class NodeFunction final
	{
	public:
		//static std::string SetVarFloat(std::string_view in, std::string_view out);
		//static std::string SetVarFloat2(std::string_view in_x, std::string_view in_y, std::string_view out);
		//static std::string SetVarFloat3(std::string_view in_x, std::string_view in_y, std::string_view in_z, std::string_view out);
		//static std::string SetVarFloat4(std::string_view in_x, std::string_view in_y, std::string_view in_z, std::string_view in_w, std::string_view out);

		////vectorの数値を文字列に変換
		//static std::string SetInputToString(float str);
		//static std::string SetInputToString2(Math::FVector2& str);
		//static std::string SetInputToString3(Math::FVector3& str);
		//static std::string SetInputToString4(Math::FVector4& str);


		static void SetInputSlotFloat(const ImVec2& set_cursor, std::string_view label, float& num);
		static void SetInputSlotFloat(const ImVec2& set_cursor, float x, std::string_view label, float& num);

		//static void SetInputSlotFloat2(ImVec2& set_cursor, Math::FVector2& num, int label_num = 0);
		//static void SetInputSlotUV(ImVec2& set_cursor);
		//static void SetInputSlotTexture2D(ImVec2& set_cursor);
		//static void SetInputSlotSamplerState(ImVec2& set_cursor);
		//static void SetInputSlotColor(ImVec2& set_cursor, bool& popup, Math::FVector3& num, int label_num = 0);

		//最後の引数はImguiでのバグ誘発防止
		static void SetInputSlotDynamic(const ImVec2& set_cursor, Math::FVector4& num, SLOT_TYPE type, int label_num = 0);

		////引数にNodeのnameとid、nameに関してはDynamic時考慮
		//static std::string SetDefineOutName(std::string_view, int id);

		////関数定義
		//static std::string SetFuncCall(std::string_view str);

		////out指定の引数を定義
		//static std::string SetDefineOutStr1(std::string_view str);
		//static std::string SetDefineOutStr2(std::string_view str);
		//static std::string SetDefineOutStr3(std::string_view str);
		//static std::string SetDefineOutStr4(std::string_view str);
		//static std::string SetDefineOutSamplerState(std::string_view str, int num);
		//static std::string SetDefineOutDynamic(std::string_view str, SLOT_TYPE type);

		static void InputRectDraw(ImDrawList* draw_list, const ImVec2& pos, SLOT_TYPE type);
		//static std::string GetType(SLOT_TYPE type);
		//static std::string GetSlotTypeName(SLOT_TYPE type);
		//static void SetSlotData(Math::FVector4& data, std::string_view str, SLOT_TYPE type);
		static ImU32 CircleColor(SLOT_TYPE type = SLOT_TYPE::VECTOR1);
		static void NodeCircle(ImDrawList* draw_list, const ImVec2& centrer, float radius,SLOT_TYPE type = SLOT_TYPE::VECTOR1);
		static void HitCircle(ImDrawList* draw_list, const Math::FVector2& pos, ImU32 color);

	};
}
