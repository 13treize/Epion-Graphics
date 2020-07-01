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
	epion::DX12::RootSignature root;

}
namespace epion
{
	bool Scene3D::Initialize()
	{
		//Camera::CameraManager::Init(DX12::ViewPort::GetAspect());
		DX12::ConstantBufferManager::Initialize();
		D3D12_DESCRIPTOR_RANGE desc_range = {};
		desc_range.NumDescriptors = 1;//定数ひとつ
		desc_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;//種別は定数
		desc_range.BaseShaderRegister = 0;//1番スロットから
		desc_range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		D3D12_ROOT_PARAMETER rootparam = {};
		rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootparam.DescriptorTable.pDescriptorRanges = &desc_range;//デスクリプタレンジのアドレス
		rootparam.DescriptorTable.NumDescriptorRanges = 1;//デスクリプタレンジ数
		rootparam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//全てのシェーダから見える

		root.Initialize(rootparam);
		DX12::RasterizerManager::Initialize();

		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\VS\\ObjVertexShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PS\\ObjPixelShader.hlsl", ps_blob, DX12::ShaderType::TYPE_PIXEL);

		m_mesh= std::make_unique<Model::StaticMesh>();
		m_mesh->Initialize(vs_blob, ps_blob, DX12::RasterizerManager::GetSolidDesc(), root.Get());

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
		DX12::ConstantBufferManager::UpdateCBuffer1(Camera::CameraManager::GetScene3DCamera()->GetView(), Camera::CameraManager::GetScene3DCamera()->GetProjection());

	}

	void Scene3D::Render()
	{
		DX12::CommandList::GetPtr()->SetGraphicsRootSignature(root.Get().Get());
		DX12::ConstantBufferManager::SetCBuffer1();

		m_mesh->Render();
	}
	void Scene3D::RenderTex()
	{
	}

}