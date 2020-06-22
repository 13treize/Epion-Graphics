#include	"../Epion12.h"
#include	"RasterizerManager.h"
namespace epion::DX12
{
	Rasterizer::Rasterizer()
	{
	}
	Rasterizer::~Rasterizer()
	{
	}

	bool Rasterizer::Initialize(const D3D12_FILL_MODE fill)
	{
		m_desc = {};
		m_desc.FillMode = fill;
		m_desc.CullMode = D3D12_CULL_MODE_NONE;
		m_desc.FrontCounterClockwise = false;
		m_desc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
		m_desc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
		m_desc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		m_desc.DepthClipEnable = true;
		m_desc.MultisampleEnable = false;
		m_desc.AntialiasedLineEnable = false;
		m_desc.ForcedSampleCount = 0;
		m_desc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
		return true;
	}
	bool Rasterizer::Finalize()
	{
		return true;
	}

	D3D12_RASTERIZER_DESC& Rasterizer::GetDesc()
	{
		return m_desc;
	}

	Rasterizer RasterizerManager::m_solid;
	Rasterizer RasterizerManager::m_wire;

	bool RasterizerManager::Initialize()
	{
		m_solid.Initialize(D3D12_FILL_MODE::D3D12_FILL_MODE_SOLID);
		m_wire.Initialize(D3D12_FILL_MODE::D3D12_FILL_MODE_WIREFRAME);
		return true;
	}

	bool RasterizerManager::Finalize()
	{
		return true;
	}

	D3D12_RASTERIZER_DESC& RasterizerManager::GetSolidDesc()
	{
		return m_solid.GetDesc();
	}
	D3D12_RASTERIZER_DESC& RasterizerManager::GetWireDesc()
	{
		return m_wire.GetDesc();
	}
}