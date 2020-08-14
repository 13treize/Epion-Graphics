#include	"../Epion12.h"
#include	"Device.h"
#include	"FrameResourceManager.h"

namespace epion::DX12
{
	std::vector<std::unique_ptr<FrameResource>> FrameResourceManager::m_frame_resources;
	FrameResource* FrameResourceManager::m_curr_frame_resource;
	int FrameResourceManager::m_curr_frame_resource_index;

	bool FrameResourceManager::Initialize()
	{
		for (int i = 0; i <3; ++i)
		{
			m_frame_resources.push_back(std::make_unique<FrameResource>(Device::Get()));
		}
		return true;
	}
	bool FrameResourceManager::Finalize()
	{
		return true;
	}
	void FrameResourceManager::Update(com_ptr<ID3D12Fence>& fence)
	{
		m_curr_frame_resource_index = (m_curr_frame_resource_index + 1) %3;
		m_curr_frame_resource = m_frame_resources[m_curr_frame_resource_index].get();

		if (m_curr_frame_resource->GetFenceValue() != 0 && fence->GetCompletedValue() < m_curr_frame_resource->GetFenceValue())
		{
			auto event = CreateEvent(nullptr, false, false, nullptr);
			fence->SetEventOnCompletion(m_curr_frame_resource->GetFenceValue(), event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}
	}
	void FrameResourceManager::Draw()
	{
	}
}