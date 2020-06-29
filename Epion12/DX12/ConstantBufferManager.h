#pragma once
#include	"Buffer.h"
#include	"DescriptorHeap.h"
namespace epion::DX12
{
	struct CBuffer0
	{
		Math::FVector4 Time;
		Math::FVector2 ScreenSize;
		Math::FVector2 MousePos;
	};
	struct CBuffer1
	{
		float Time;
		float A;
		float B;
		float C;
	};

	struct	CBuffer3
	{
		DirectX::XMFLOAT4X4	world_view_projection;
		DirectX::XMFLOAT4X4	world;
	};

	class ConstantBufferManager final
	{
	public:

		static bool Initialize();
		static bool Finalize();
		static void UpdateCBuffer0(const Math::FVector2& mouse_pos);
		static void SetCBuffer0();


	private:
		static std::unique_ptr<epion::DX12::DescriptorHeap> m_heap;
		static std::unique_ptr<DX12::ConstantBuffer> m_cbuffer0;
		static CBuffer0* m_cbuffer0_data;

	};
}