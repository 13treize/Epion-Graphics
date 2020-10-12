#pragma once
#include	"Buffer.h"
#include	"DescriptorHeap.h"

#define MAX_LIGHTS 16
namespace epion::DX12
{
	struct Light
	{
		Math::FVector3 Strength = { 0.5f, 0.5f, 0.5f };
		float FalloffStart = 1.0f;                          // point/spot light only
		Math::FVector3 Direction = { 0.0f, -1.0f, 0.0f };// directional/spot light only
		float FalloffEnd = 10.0f;                           // point/spot light only
		Math::FVector3 Position = { 0.0f, 0.0f, 0.0f };  // point/spot light only
		float SpotPower = 64.0f;                            // spot light only
	};
	__declspec(align(256))
		struct CBufferDefault2D
	{
		Math::FVector4 Time;
		Math::FVector2 ScreenSize;
		Math::FVector2 MousePos;
	};

	__declspec(align(256))
		struct CBufferObjects
	{
		DirectX::XMMATRIX	World;
	};

	__declspec(align(512))
		struct CBufferPassConstants
	{
		DirectX::XMMATRIX	View;
		DirectX::XMMATRIX	Proj;
		Math::FVector4		CameraPos;
		Math::FVector4		LightColor;
		Math::FVector4		LightDir;
		Math::FVector4		AmbientColor;
		Light Lights[MAX_LIGHTS];
	};

	__declspec(align(512))
		struct CBufferMaterials
	{
		Math::FVector4 DiffuseAlbedo;
		Math::FVector3 FresnelR0;
		float Roughness;
		DirectX::XMFLOAT4X4 MatTransform;
	};

	__declspec(align(512))
		struct CBufferParams
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
		static void UpdateCBuffer3(const Math::FVector4& DiffuseAlbedo,const Math::FVector3& FresnelR0,float Roughness, const unsigned int index);
		static void UpdateCBuffer4(const std::array < Math::FVector4, 4>& data);

		static void SetHeap();

		static void SetCBuffer0(int index = 0);
		static void SetCBuffer1(int cb_num, int index = 1);
		static void SetCBuffer2(int index = 2);
		static void SetCBuffer3(int cb_num, int index = 3);
		static void SetCBuffer4(int index = 4);

		static UINT CalcConstantBufferByteSize(UINT byteSize);

		//	private:
		static std::unique_ptr<DX12::DescriptorHeap> m_heap;

		//static std::unique_ptr <CBufferData<CBuffer0>>	m_cbuffer0;
		static std::unique_ptr<ResourceBuffer<CBufferDefault2D>> m_cbuffer0;
		static std::unique_ptr<ResourceBuffer<CBufferObjects>> m_cbuffer1;
		static std::unique_ptr<ResourceBuffer<CBufferPassConstants>> m_cbuffer2;
		static std::unique_ptr<ResourceBuffer<CBufferMaterials>> m_cbuffer3;
		static std::unique_ptr<ResourceBuffer<CBufferParams>> m_cbuffer4;

		static CBufferDefault2D* m_cbuffer0_data;
		static CBufferObjects* m_cbuffer1_data;
		static CBufferPassConstants* m_cbuffer2_data;
		static CBufferMaterials* m_cbuffer3_data;
		static CBufferParams* m_cbuffer4_data;

		static D3D12_GPU_VIRTUAL_ADDRESS m_gpu_virtual_address1;
		static D3D12_GPU_VIRTUAL_ADDRESS m_gpu_virtual_address2;
	};

	//class CBufferIndexManager final
	//{
	//public:
	//	static void Reset();
	//	static void Counter();

	//private:
	//	static int obj_cbuffer_index;
	//	static int mat_cbuffer_index;
	//};
}