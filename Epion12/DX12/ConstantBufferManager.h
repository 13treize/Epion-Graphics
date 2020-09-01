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
	};

	__declspec(align(256))
		struct CBuffer2
	{
		DirectX::XMMATRIX	View;
		DirectX::XMMATRIX	Proj;
		//Math::FVector4		CameraPos;
		Math::FVector4		LightColor;
		Math::FVector4		LightDir;
		Math::FVector4		AmbientColor;
	};

	__declspec(align(512))
		struct CBuffer3
	{
		std::array<Math::FVector4, 4> Data;
	};


	template<class T>
	class CBufferData final
	{
	public:
		CBufferData() :
			m_cbuffer(nullptr),
			m_constant_buffer_view({}),
			m_slot_data(0)
		{

		}
		~CBufferData()
		{

		}
		bool Initialize(com_ptr<ID3D12Device>& device, D3D12_CPU_DESCRIPTOR_HANDLE handle)
		{
			m_cbuffer = std::make_unique<DX12::ResourceBuffer<T>>();
			m_cbuffer->Initialize(device, sizeof(T), true);
			m_constant_buffer_view = { m_cbuffer->GetGPUVirtualAddress(),256 };
			device->CreateConstantBufferView(&m_constant_buffer_view, handle);
			return true;
		}
		bool Finalize()
		{
			return true;
		}
		void CopyResource(const T& data)
		{
			m_cbuffer->CopyResource(data);
		}

	private:
		std::unique_ptr<ResourceBuffer<T>> m_cbuffer;
		D3D12_CONSTANT_BUFFER_VIEW_DESC m_constant_buffer_view;
		D3D12_GPU_VIRTUAL_ADDRESS m_gpu_virtual_address;
		unsigned int m_slot_data;
	};

	class ConstantBufferManager final
	{
	public:
		static bool Initialize();
		static bool Build2D(const int buffer_num = 1);
		static bool Build3D(const int buffer_num = 2);

		static bool Finalize();
		static void UpdateCBuffer0(const Math::FVector2& mouse_pos);
		static void UpdateCBuffer1(const DirectX::XMMATRIX& world, const unsigned int index);
		static void UpdateCBuffer2(const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& projection, const Math::FVector3& camera_pos, const Math::FVector4& color, const Math::FVector4& dir, const Math::FVector4& ambient);
		static void UpdateCBuffer3(const std::array < Math::FVector4, 4>& data);

		static void SetHeap();

		static void SetCBuffer0(int index);
		static void SetCBuffer1(unsigned int index, int frame_count);
		static void SetCBuffer2(int index);
		static void SetCBuffer3(int index);

		static UINT CalcConstantBufferByteSize(UINT byteSize);

		//	private:
		static std::unique_ptr<DX12::DescriptorHeap> m_heap;

		//static std::unique_ptr <CBufferData<CBuffer0>>	m_cbuffer0;
		static std::unique_ptr<ResourceBuffer<CBuffer0>> m_cbuffer0;
		static std::unique_ptr<ResourceBuffer<CBuffer1>> m_cbuffer1;
		static std::unique_ptr<ResourceBuffer<CBuffer2>> m_cbuffer2;
		static std::unique_ptr<ResourceBuffer<CBuffer3>> m_cbuffer3;

		static CBuffer0* m_cbuffer0_data;
		static CBuffer1* m_cbuffer1_data;
		static CBuffer2* m_cbuffer2_data;
		static CBuffer3* m_cbuffer3_data;

		static D3D12_GPU_VIRTUAL_ADDRESS m_gpu_virtual_address1;
		static D3D12_GPU_VIRTUAL_ADDRESS m_gpu_virtual_address2;


	};
}