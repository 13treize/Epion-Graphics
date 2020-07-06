#pragma once
#include	"Buffer.h"
#include	"DescriptorHeap.h"
namespace epion::DX12
{
	__declspec(align(256))
		struct CBuffer0
	{
		Math::FVector4 Time;
		Math::FVector2 ScreenSize;
		Math::FVector2 MousePos;
	};

	__declspec(align(256))
		struct CBuffer1
	{
		DirectX::XMMATRIX	World;
		DirectX::XMMATRIX	View;
		DirectX::XMMATRIX	Proj;
	};

	__declspec(align(256))
		struct CBuffer2
	{
		Math::FVector4	LightColor;
		Math::FVector4	LightDir;
		Math::FVector4	AmbientColor;
	};


	class ConstantBufferManager final
	{
	public:


		static bool Initialize();
		static bool Finalize();
		static void UpdateCBuffer0(const Math::FVector2& mouse_pos);
		static void UpdateCBuffer1(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& projection);
		static void UpdateCBuffer2(const Math::FVector4& color, const Math::FVector4& dir, const Math::FVector4& ambient);

		static void SetCBuffer0();
		static void SetCBuffer1(unsigned int index);
		static void SetCBuffer2();




		//	private:
		static std::unique_ptr<DX12::DescriptorHeap> m_heap;
		static std::unique_ptr<DX12::ConstantBuffer> m_cbuffer0;
		static std::unique_ptr<DX12::ConstantBuffer> m_cbuffer1;
		static std::unique_ptr<DX12::ConstantBuffer> m_cbuffer2;

		static CBuffer0* m_cbuffer0_data;
		static CBuffer1* m_cbuffer1_data;
		static CBuffer2* m_cbuffer2_data;
	};
}