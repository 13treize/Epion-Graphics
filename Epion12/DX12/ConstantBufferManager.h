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
		DirectX::XMFLOAT4X4	WorldViewProjection;
		DirectX::XMFLOAT4X4	World;
	};
	class ConstantBufferManager final
	{
	public:


		static bool Initialize();
		static bool Finalize();
		static void UpdateCBuffer0(const Math::FVector2& mouse_pos);
		static void UpdateCBuffer1(/*DirectX::XMFLOAT4X4& matrix,*/ const	DirectX::XMFLOAT4X4& view, const	DirectX::XMFLOAT4X4& projection);
		static void SetCBuffer0();
		static void SetCBuffer1();




//	private:
		static std::unique_ptr<DX12::DescriptorHeap> m_heap;
		static std::unique_ptr<DX12::ConstantBuffer> m_cbuffer0;
		static std::unique_ptr<DX12::ConstantBuffer> m_cbuffer1;
		static CBuffer0* m_cbuffer0_data;
		static CBuffer3* m_cbuffer1_data;

	};
}