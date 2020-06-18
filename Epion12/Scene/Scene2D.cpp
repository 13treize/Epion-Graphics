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
		vs_blob = nullptr;
		ps_blob = nullptr;
		bool a;
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