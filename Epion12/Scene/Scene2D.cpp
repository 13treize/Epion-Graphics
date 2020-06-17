#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"Scene2D.h"

namespace
{
}
namespace epion
{
	bool Scene2D::Initialize()
	{
		//Shader::ShaderManager::Compile(L"ShaderCode\\HLSL\\VS\\VertexShader.hlsl", vs_blob, Shader::ShaderType::VERTEX);
		//Shader::ShaderManager::Compile(L"ShaderCode\\HLSL\\PS\\PixelShader.hlsl", ps_blob, Shader::ShaderType::PIXEL);
		//DX12::StateDescManager::Initialize();

		//m_square = std::make_unique<Model::Square>();
		//m_square->Initialize(vs_blob, ps_blob, DX12::StateDescManager::GetRasterizerSolid());

		return true;
	}
	bool Scene2D::Finalize()
	{
		return true;
	}
	void Scene2D::Update()
	{
		//m_square->Update(Math::FVector2(0, 0), Math::FVector2(200, 200));
	}
	void Scene2D::Render()
	{
		//m_square->Render();
	}
	void Scene2D::RenderTex()
	{
	}

}