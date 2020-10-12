#include	"../Epion12.h"
#include	"Device.h"

namespace
{
}

namespace epion::DX12
{
	com_ptr<ID3D12Device> Device::m_device;
	D3D_FEATURE_LEVEL Device::m_feature_level;

	Device::Device()
	{
	}
	Device::~Device()
	{
	}

	bool Device::Initialize(com_ptr<IDXGIFactory6>& factory)
	{
		com_ptr<IDXGIAdapter> adapter = {};

		//TODO Adapterセットでエラーが無くなる、原因追求
		std::vector <com_ptr<IDXGIAdapter>> adapters = {};
		for (int i = 0; factory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			adapters.push_back(adapter);
		}
		for (auto adpt : adapters)
		{
			DXGI_ADAPTER_DESC adesc = {};
			adpt->GetDesc(&adesc);
			std::wstring strDesc = adesc.Description;
			if (strDesc.find(L"NVIDIA") != std::string::npos)
			{
				adapter = adpt;
				break;
			}
		}

		CreateDevice(m_device, adapter, m_feature_level);
		m_device->SetName(L"Device");
		return true;
	}
	bool Device::Finalize()
	{
		//m_device->Release();
		return true;

	}
	com_ptr<ID3D12Device>& Device::Get()
	{
		return m_device;
	}

	D3D_FEATURE_LEVEL Device::GetFeatureLevel()
	{
		return m_feature_level;
	}


	bool CreateDevice(com_ptr<ID3D12Device>& device, com_ptr<IDXGIAdapter>& adapter, D3D_FEATURE_LEVEL feature_level)
	{
		D3D_FEATURE_LEVEL feature_levels[] =
		{
			D3D_FEATURE_LEVEL_12_1,
			D3D_FEATURE_LEVEL_12_0,
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		for (auto l : feature_levels)
		{
			if (D3D12CreateDevice(adapter.Get(), l, IID_PPV_ARGS(&device)) == S_OK)
			{
				feature_level = l;
				break;
			}
		}
		return true;
	}

}