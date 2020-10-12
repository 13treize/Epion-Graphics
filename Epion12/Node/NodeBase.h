#pragma once

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

	struct NodeData
	{
		std::string Name;
		Math::FVector2 Pos;
		ImU32 Color;
		LinkVector Links;
	};
	using NodeVector = std::vector<NodeData>;

	class NodeBase abstract
	{
	public:
		NodeBase(std::string_view name,int id, const Math::FVector2&	pos,const Math::FVector2&	size);
		virtual	~NodeBase() {};

	private:
		std::string	m_Name;
		int	m_ID;
		Math::FVector2	m_Pos;
		Math::FVector2	m_Size;
		NodeVector m_Inputs;
		NodeVector m_Outputs;
	};
}