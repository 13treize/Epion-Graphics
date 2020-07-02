#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"Scene3D.h"

#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"
#include	"../DX12/ViewPort.h"
#include	"../Camera/CameraManager.h"
#include	"../DX12/ShaderManager.h"
#include	"../DX12/RasterizerManager.h"
#include	"../DX12/ConstantBufferManager.h"
#include	"../DX12/RootSignature.h"
#include	"../DX12/DescriptorHeap.h"

namespace
{
}
namespace epion
{
	bool Scene3D::Initialize()
	{
		//Camera::CameraManager::Init(DX12::ViewPort::GetAspect());
		DX12::ConstantBufferManager::Initialize();
		DX12::RootSignatureManager::Build();
		DX12::RasterizerManager::Initialize();

		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\VS\\ObjVertexShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PS\\ObjPixelShader.hlsl", ps_blob, DX12::ShaderType::TYPE_PIXEL);

		m_mesh= std::make_unique<Model::StaticMesh>();
		m_mesh->Initialize(vs_blob, ps_blob, DX12::RasterizerManager::GetSolidDesc(), DX12::RootSignatureManager::Get());

		return true;
	}

	bool Scene3D::Finalize()
	{
		return true;
	}
	void Scene3D::Update()
	{
		//Camera::CameraManager::Update();
		m_mesh->Update();
		//DX12::ConstantBufferManager::UpdateCBuffer1(Camera::CameraManager::GetScene3DCamera()->GetView(), Camera::CameraManager::GetScene3DCamera()->GetProjection());

	}

	void Scene3D::Render()
	{
		DX12::RootSignatureManager::SetGraphicsRootSignature();
		DX12::ConstantBufferManager::SetCBuffer1();

		m_mesh->Render();
	}
	void Scene3D::RenderTex()
	{
	}

}