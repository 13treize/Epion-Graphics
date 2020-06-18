#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"Scene2D.h"
#include	"../DX12/ShaderManager.h"

namespace
{
	epion::com_ptr<ID3DBlob> vs_blob;
	epion::com_ptr<ID3DBlob> ps_blob;

}
namespace epion
{
	bool Scene2D::Initialize()
	{
		vs_blob = nullptr;
		ps_blob = nullptr;
		bool a=DX12::ShaderManager::Compile(L"VertexShader.hlsl", vs_blob, DX12::ShaderType::VERTEX);
		DX12::ShaderManager::Compile(L"HLSL\\PS\\PixelShader.hlsl", ps_blob, DX12::ShaderType::PIXEL);

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
		m_square->Update(Math::FVector2(0, 0), Math::FVector2(200, 200));
	}
	void Scene2D::Render()
	{
		m_square->Render();
	}
	void Scene2D::RenderTex()
	{
	}

}