#include	"../Epion12.h"
#include "NodeBase.h"

namespace epion::Node
{
	NodeBase::NodeBase(std::string_view name, int id, const Math::FVector2& pos, const Math::FVector2& size)
		:m_Name(name),m_ID(id),m_Pos(pos),m_Size(size)
	{

	}
}