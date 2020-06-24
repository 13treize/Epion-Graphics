#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"

#include	"Scene2D.h"
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
	bool Scene2D::Initialize()
	{
		HRESULT hr;

		DX12::ConstantBufferManager::Initialize();

		D3D12_DESCRIPTOR_RANGE desc_range = {};//�e�N�X�`���ƒ萔�̂Q��
		desc_range.NumDescriptors = 1;//�萔�ЂƂ�
		desc_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;//��ʂ͒萔
		desc_range.BaseShaderRegister = 0;//0�ԃX���b�g����
		desc_range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		D3D12_ROOT_PARAMETER rootparam = {};
		rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootparam.DescriptorTable.pDescriptorRanges = &desc_range;//�f�X�N���v�^�����W�̃A�h���X
		rootparam.DescriptorTable.NumDescriptorRanges = 1;//�f�X�N���v�^�����W��
		rootparam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//�S�ẴV�F�[�_���猩����


		root.Initialize(rootparam);


		DX12::RasterizerManager::Initialize();

		DX12::ShaderManager::Compile(L"Epion12\\HLSL\\VS\\VertexShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		DX12::ShaderManager::Compile(L"Epion12\\HLSL\\PS\\PixelShader.hlsl", ps_blob, DX12::ShaderType::TYPE_PIXEL);
		DX12::ShaderManager::Compile(L"Epion12\\HLSL\\GS\\GeometryShader.hlsl", gs_blob, DX12::ShaderType::TYPE_GEOMETRY);
		DX12::ShaderManager::Compile(L"Epion12\\HLSL\\PS\\PixelShaderConst.hlsl", ps_blob2, DX12::ShaderType::TYPE_PIXEL);

		//aaaaa=DX12::ShaderManager::Compile(L"Epion12\\HLSL\\HS\\HullShader.hlsl", hs_blob, DX12::ShaderType::TYPE_HULL);
		//assert(aaaaa);
		//aaaaa=DX12::ShaderManager::Compile(L"Epion12\\HLSL\\DS\\DomainShader.hlsl", ds_blob, DX12::ShaderType::TYPE_DOMAIN);
		//assert(aaaaa);



		//m_square = std::make_unique<Model::Square>();
		//m_square->Initialize(vs_blob, ps_blob, gs_blob, DX12::RasterizerManager::GetSolidDesc());
	/*	m_plane= std::make_unique<Model::Plane>();
		m_plane->Initialize(vs_blob, ps_blob, DX12::RasterizerManager::GetSolidDesc());*/

		m_square = std::make_unique<Model::Square>();
		m_square->Initialize(vs_blob, ps_blob2, gs_blob, DX12::RasterizerManager::GetSolidDesc(), root.Get());

		return true;
	}	

	bool Scene2D::Finalize()
	{
		return true;
	}
	void Scene2D::Update()
	{

		m_square->Update(Math::FVector2(200, 200), Math::FVector2(200, 200));
		DX12::ConstantBufferManager::UpdateCBuffer0();
		//m_plane->Update(Math::FVector2(200, 200), Math::FVector2(200, 200));

	}

	void Scene2D::Render()
	{
		DX12::CommandList::GetPtr()->SetGraphicsRootSignature(root.Get().Get());
		DX12::ConstantBufferManager::SetCBuffer0();
		m_square->Render();
		//m_plane->Render();

	}
	void Scene2D::RenderTex()
	{
	}

}