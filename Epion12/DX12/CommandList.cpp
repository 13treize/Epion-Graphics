#include	"../Epion12.h"
#include	"Device.h"
#include	"DX12Wrapper.h"
#include	"CommandList.h"

namespace epion::DX12
{
	com_ptr<ID3D12GraphicsCommandList> CommandList::m_cmd_list;

	CommandList::CommandList()
	{
	}
	CommandList::~CommandList()
	{
	}

	bool CommandList::Initialize(com_ptr<ID3D12CommandAllocator>& cmd_alloc)
	{
		DX12Wrapper::CreateCommandList<ID3D12Device>(Device::Get(),m_cmd_list, cmd_alloc);
		return true;
	}
	bool CommandList::Finalize()
	{
		return true;
	}

	com_ptr<ID3D12GraphicsCommandList>& CommandList::GetCmd()
	{
		return m_cmd_list;
	}

}