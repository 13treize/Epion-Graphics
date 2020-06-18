#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"Scene2D.h"
#include	"../DX12/ShaderManager.h"

namespace
{
}
namespace epion
{
	bool Scene2D::Initialize()
	{
		D3D12_RASTERIZER_DESC solid_desc;

		solid_desc.FillMode = D3D12_FILL_MODE_SOLID;
		solid_desc.CullMode = D3D12_CULL_MODE_NONE;
		solid_desc.FrontCounterClockwise = false;
		solid_desc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
		solid_desc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
		solid_desc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		solid_desc.DepthClipEnable = true;
		solid_desc.MultisampleEnable = false;
		solid_desc.AntialiasedLineEnable = false;
		solid_desc.ForcedSampleCount = 0;
		solid_desc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;


		DX12::ShaderManager::Compile(L"Epion12\\HLSL\\VS\\VertexShader.hlsl", vs_blob, DX12::ShaderType::VERTEX);
		DX12::ShaderManager::Compile(L"Epion12\\HLSL\\PS\\PixelShader.hlsl", ps_blob, DX12::ShaderType::PIXEL);
		m_square = std::make_unique<Model::Square>();
		m_square->Initialize(vs_blob, ps_blob);

		return true;
	}
	bool Scene2D::Finalize()
	{
		return true;
	}
	void Scene2D::Update()
	{
		m_square->Update(Math::FVector2(200, 200), Math::FVector2(200, 200));
	}
	void Scene2D::Render()
	{
		m_square->Render();
	}
	void Scene2D::RenderTex()
	{
	}

}