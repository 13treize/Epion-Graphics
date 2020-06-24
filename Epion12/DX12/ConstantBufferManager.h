#pragma once
#include	"Buffer.h"
#include	"DescriptorHeap.h"
namespace epion::DX12
{
	struct CBuffer0
	{
		float Time;
		float A;
		float B;
		float C;

	};

	class ConstantBufferManager final
	{
	public:

		static bool Initialize();
		static bool Finalize();
		static void SetCBuffer0();


	private:
		static std::unique_ptr<epion::DX12::DescriptorHeap> m_heap;
		static std::unique_ptr<DX12::ConstantBuffer> m_cbuffer0;
		static std::unique_ptr<CBuffer0> m_cbuffer0_data;

	};
}