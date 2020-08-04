#pragma once
#include	"Buffer.h"
namespace epion::DX12
{
	__declspec(align(256))
		struct CBuffer2D
	{
		Math::FVector4 Time;
		Math::FVector2 ScreenSize;
		Math::FVector2 MousePos;
	};

	__declspec(align(512))
		struct CBuffer3D
	{
		DirectX::XMMATRIX	World;
		DirectX::XMMATRIX	View;
		DirectX::XMMATRIX	Proj;
	};

	class FrameResource final
	{
	public:
		template<class T>
		FrameResource(com_ptr<T>& device)
		{
			device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_cmdlist_alloc.ReleaseAndGetAddressOf()));
			m_cbuffer0 = std::make_unique<DX12::ResourceBuffer<CBuffer2D>>();
			m_cbuffer0->Initialize(device, sizeof(CBuffer2D), true);
			m_cbuffer1 = std::make_unique<DX12::ResourceBuffer<CBuffer3D>>();
			m_cbuffer1->Initialize(device, sizeof(CBuffer3D), true);
		}
		FrameResource(const FrameResource& rhs) = delete;
		FrameResource& operator=(const FrameResource& rhs) = delete;
		~FrameResource()
		{
		}

	private:
		com_ptr<ID3D12CommandAllocator> m_cmdlist_alloc;
		std::unique_ptr<ResourceBuffer<CBuffer2D>> m_cbuffer0;
		std::unique_ptr<ResourceBuffer<CBuffer3D>> m_cbuffer1;
		UINT64 m_fence;
	};
}