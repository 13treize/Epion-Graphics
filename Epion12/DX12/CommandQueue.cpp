#include	"../Epion12.h"
#include	"CommandQueue.h"

namespace epion::DX12
{
	CommandQueue::CommandQueue()
	{
	}
	CommandQueue::~CommandQueue()
	{
	}

	bool CommandQueue::Initialize(com_ptr<ID3D12Device>& device)
	{
		HRESULT hr = {};
		D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
		cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;//�^�C���A�E�g�Ȃ�
		cmdQueueDesc.NodeMask = 0;
		cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;//�v���C�I���e�B���Ɏw��Ȃ�
		cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;//�����̓R�}���h���X�g�ƍ��킹�Ă�������
		hr = device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&m_cmd_queue));//�R�}���h�L���[����
		if (SUCCEEDED(hr))
		{
			return true;
		}
		return false;
	}
	bool CommandQueue::Finalize()
	{
		return true;
	}
	void CommandQueue::Update(com_ptr<ID3D12GraphicsCommandList>& cmd_list)
	{
		ID3D12CommandList* ppCommandLists[] = { cmd_list.Get() };
		m_cmd_queue->ExecuteCommandLists(1, ppCommandLists);
	}

	com_ptr<ID3D12CommandQueue>& CommandQueue::GetPtr()
	{
		return m_cmd_queue;
	}

	bool CommandQueueFunction::CreateCommandQueue(com_ptr<ID3D12Device>& device, com_ptr<ID3D12CommandQueue>& queue)
	{
		D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
		cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;//�^�C���A�E�g�Ȃ�
		cmdQueueDesc.NodeMask = 0;
		cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;//�v���C�I���e�B���Ɏw��Ȃ�
		cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;//�����̓R�}���h���X�g�ƍ��킹�Ă�������
		HRESULT hr = device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&queue));//�R�}���h�L���[����
		if (FAILED(hr))
		{
			return false;
		}
		return true;

	}

}

