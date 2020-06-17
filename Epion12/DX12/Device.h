#pragma once
/**
 * @file Device.h
 * @brief Device作成
 * @author treize
 * @date 2020/02/18
 * @details
 デバイス作成クラス
 <br>https://docs.microsoft.com/en-us/windows/win32/api/d3d12/nn-d3d12-id3d12device
 */
namespace epion::DX12
{
	class Device final
	{
	public:
		Device();
		~Device();

		static bool Initialize(com_ptr<IDXGIFactory6>& factory);
		static bool Finalize();
		//get
		static com_ptr<ID3D12Device>& Get();
		static D3D_FEATURE_LEVEL GetFeatureLevel();

	private:
		static com_ptr<ID3D12Device> m_device;
		static D3D_FEATURE_LEVEL m_feature_level;

	};

	__forceinline bool CreateDevice(com_ptr<ID3D12Device>& device, com_ptr<IDXGIAdapter>& adapter, D3D_FEATURE_LEVEL feature_level);
}