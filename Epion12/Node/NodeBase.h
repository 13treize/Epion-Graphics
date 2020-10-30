#pragma once

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

namespace epion::Node
{
	struct LinkData
	{
		int id;
		int slot;
		bool	operator==(const	 LinkData& vec)const
		{
			if (id == vec.id && slot == vec.slot)	return	true;
			return	false;
		}
		bool	operator!=(const	 LinkData& vec)const
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

	struct SlotData
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
	using NodeVector = std::vector<SlotData>;

	//外部から読み込みするときのパラメータ
	struct NodeParam
	{
		std::string	Name;
		NodeVector	Inputs;
		NodeVector	Outputs;
		std::string ShaderCode;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(Inputs), Outputs);
		}

	};


	class NodeBase abstract
	{
	public:
		NodeBase(std::string_view name,int id, const Math::FVector2&	pos,int input_num,int output_num);
		NodeBase(std::string_view name, int id, const Math::FVector2& pos);

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

		void SetPos(const Math::FVector2& pos);
		void SetDrawPos(const ImVec2& draw_pos);

		void PushEventBegin();
		void PushEventEnd();
	//private:
	protected:
		std::string	m_Name;
		int	m_ID;
		Math::FVector2	m_Pos;
		Math::FVector2	m_Size;
		ImVec2	m_DrawPos;
		NodeVector	m_Inputs;
		NodeVector	m_Outputs;
		NODE_STATE	m_NodeType;

		bool	m_is_push;
		bool	m_is_double_clicked;


		//inputslotにノードが刺さっているかどうか
		//TODO 複数に対応
		std::deque<INPUT_SLOT_STATE> m_is_slot_input;

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
		//left
		ChildParam m_output;
		//right
		ChildParam m_input;
	};




	class FunctionNode final :public NodeBase
	{
	public:
		FunctionNode() = delete;
		FunctionNode(std::string_view name, int id, const Math::FVector2& pos);
		~FunctionNode();
	private:

	};

	class SampleNode final :public NodeBase
	{
	public:
		SampleNode() = delete;
		SampleNode(std::string_view name, int id, const Math::FVector2& pos);

	private:

	};
}