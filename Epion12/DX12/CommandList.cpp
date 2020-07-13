#include	"../Epion12.h"
#include	"Device.h"
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
		HRESULT hr = S_OK;

		hr = Device::Get()->CreateCommandList(
			0,
			D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT,
			cmd_alloc.Get(),
			nullptr,
			IID_PPV_ARGS(&m_cmd_list));
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