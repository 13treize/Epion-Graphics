#pragma once

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/polymorphic.hpp>

namespace epion::Node
{
	/**
	* @brief Imguiを用いたColorPickerクラス
	*/

	class ColorPicker2 final
	{
	public:
		ColorPicker2();
		~ColorPicker2();
		/**
		* @brief privateメンバー変数の初期化、Activateを呼び出す前に使う
		*/
		void Init(std::string_view str, std::string_view str2);
		/**
		* @brief ColorPickerを開ける
		* @param[in] (is_popup) ColorPickerを開けるかどうか,trueで	open
		* @param[in] (color) baseのcolorを渡す
		*/
		void Activate(bool is_popup, Math::FVector4& color);

		void SetInputSlotColor2(const ImVec2& set_cursor, bool popup, Math::FVector4& num, int label_num = 0);

	private:
		ImGuiColorEditFlags m_edit_flags;
		ImVec4 m_backup_color;
		ImVec4 m_color;
		Math::FVector4 m_ret_color;
		std::string	m_popup_name;
		std::string	m_picker_name;
		std::string	m_current_name;
		std::string	m_previous_name;
		std::string	m_color_button_name;
		std::string	m_button_name;

	};

	struct LinkData
	{
		int id;
		int slot;
		bool	operator==(const LinkData& vec)const
		{
			if (id == vec.id && slot == vec.slot)	return	true;
			return	false;
		}
		bool	operator!=(const LinkData& vec)const
		{
			if (id != vec.id || slot != vec.slot)	return	true;
			return	false;
		}
	};
	using LinkVector = std::vector<LinkData>;

	struct ChildParam
	{
		LinkData LinkData;
		SLOT_TYPE SlotType;
	};

	struct InputSlotData
	{
		std::string Name;
		SLOT_TYPE	SlotType;
		Math::FVector4	InputData;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(cereal::make_nvp("Name", Name), cereal::make_nvp("Type", SlotType), cereal::make_nvp("Data",InputData));
		};
		Math::FVector2 Pos;
		ImU32 Color;
		LinkVector Links;
	};

	struct OutputSlotData
	{
		std::string Name;
		SLOT_TYPE	SlotType;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(cereal::make_nvp("Name", Name), cereal::make_nvp("Type", SlotType));
		};
		Math::FVector2 Pos;
		ImU32 Color;
		LinkVector Links;
	};
	using InNodeVector = std::vector<InputSlotData>;
	using OutNodeVector = std::vector<OutputSlotData>;

	//外部から読み込みするときのパラメータ
	struct NodeParam
	{
		std::string	Name;
		InNodeVector	Inputs;
		OutNodeVector	Outputs;
		std::string ShaderCode;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(Inputs), CEREAL_NVP(Outputs));
		}
	};

	enum class NodeState :unsigned char
	{
		NORMAL=0,
		CONPACT
	};

	class NodeBase abstract
	{
	public:
		NodeBase(std::string_view type, std::string_view name, int id, const Math::FVector2& pos);

		virtual	~NodeBase() {};

		void Draw(ImDrawList* draw_list, const ImVec2& offset, float scroll_scale);

		void DrawLinkLine(ImDrawList* draw_list);

		const int GetID() const;
		const Math::FVector2& GetPos() const;
		const Math::FVector2& GetSize() const;

		SLOT_TYPE GetInputSlotType(size_t id) const;
		SLOT_TYPE GetOutputSlotType(size_t id) const;

		const size_t	GetInputsSize() const;
		const size_t	GetOutputsSize() const;


		const Math::FVector2 GetInputSlotPos(int slot_no, const Math::FVector2& adjustment_pos) const;
		const Math::FVector2 GetOutputSlotPos(int slot_no, const Math::FVector2& adjustment_pos) const;

		bool GetIsPush();
		bool GetIsSlotInputONE(int index);

		void SetPos(const Math::FVector2& pos);
		void SetDrawPos(const ImVec2& draw_pos);
		void SetIsSlotInput(int index, INPUT_SLOT_STATE type);

		void PushEventBegin();
		void PushEventEnd();

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(
				CEREAL_NVP(m_Name),
				CEREAL_NVP(m_ID),
				CEREAL_NVP(m_Pos),
				cereal::make_nvp("Input Data",m_Inputs)
				);
		}

	private:
		void SizeSetting(const size_t input, const size_t output);
		void FileSetting(std::string_view type, std::string_view name, NodeParam& data);
	protected:
		std::string	m_Name;
		int	m_ID;
		Math::FVector2	m_Pos;
		Math::FVector2	m_Size;
		ImVec2	m_DrawPos;
		InNodeVector	m_Inputs;
		OutNodeVector	m_Outputs;
		NODE_STATE	m_NodeType;
	//	std::vector<Math::FVector4> m_In
		bool	m_is_push;
		bool	m_is_double_clicked;

		ColorPicker2	m_color_picker[3];
		bool			m_open_popup[3];


		//inputslotにノードが刺さっているかどうか
		//TODO 複数に対応
		std::vector<INPUT_SLOT_STATE> m_is_slot_input;

	};

	class	NodeLink
	{
	public:
		NodeLink() = delete;
		NodeLink(int output_id, int output_slot, int input_id, int input_slot);
		NodeLink(int output_id, int output_slot, SLOT_TYPE output_type, int input_id, int input_slot, SLOT_TYPE input_type);
		~NodeLink();
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(m_input.LinkData.id), CEREAL_NVP(m_input.LinkData.slot), CEREAL_NVP(m_input.SlotType),
				CEREAL_NVP(m_output.LinkData.id), CEREAL_NVP(m_output.LinkData.slot), CEREAL_NVP(m_output.SlotType));
		};

		int	GetOutputID();
		int	GetOutputSlot();
		SLOT_TYPE GetOutputType();
		void SetOutputType(SLOT_TYPE type);

		//right
		int	GetInputID();
		int	GetInputSlot();
		SLOT_TYPE GetInputType();
		void SetInputType(SLOT_TYPE type);

		bool	operator==(const	NodeLink& vec)const
		{
			if (m_output.LinkData.id == vec.m_output.LinkData.id &&
				m_output.SlotType == vec.m_output.SlotType &&
				m_input.LinkData.id == vec.m_input.LinkData.id &&
				m_input.SlotType == vec.m_input.SlotType)
			{
				return	true;
			};
			return	false;
		}
		bool	operator!=(const	NodeLink& vec)const
		{
			if (m_output.LinkData.id != vec.m_output.LinkData.id ||
				m_output.SlotType != vec.m_output.SlotType ||
				m_input.LinkData.id != vec.m_input.LinkData.id ||
				m_input.SlotType != vec.m_input.SlotType)
			{
				return	true;
			};
			return	false;
		}
		bool m_is_hit;
		bool m_is_delete_menu;
		std::string StateStr();
	private:
		ChildParam m_output;	//left
		ChildParam m_input;		//right
	};




	class FunctionNode final :public NodeBase
	{
	public:
		FunctionNode();
		FunctionNode(std::string_view type, std::string_view name, int id, const Math::FVector2& pos);
		~FunctionNode();

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(cereal::base_class<NodeBase>(this));
		}

	private:

	};
}