#pragma once
#include	"FrameResource.h"
namespace epion::DX12
{
	class FrameResourceManager final
	{
	public:
		static bool Initialize();
		static bool Finalize();

		static void Update(com_ptr<ID3D12Fence>& fence);
		static void Draw();
	private:

		static std::vector<std::unique_ptr<FrameResource>> m_frame_resources;
		static FrameResource* m_curr_frame_resource;
		static int m_curr_frame_resource_index;
	};
}