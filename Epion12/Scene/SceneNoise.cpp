#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"SceneNoise.h"

#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"
#include	"../DX12/ViewPort.h"
#include	"../Camera/CameraManager.h"
#include	"../DX12/ShaderManager.h"
#include	"../DX12/RootSignature.h"
#include	"../DX12/DescriptorHeap.h"

namespace
{
	constexpr int DRAW_CALL_NUM = 8;
}

namespace epion
{
	bool SceneNoise::Initialize()
	{
		HRESULT hr = S_OK;
		DX12::RootSignatureManager::Build();
		Camera::CameraManager::Init(DX12::ViewPort::GetAspect());
		Camera::CameraManager::Update();

		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\VSShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		for (int i = 0; i < DRAW_CALL_NUM + 1; i++)
		{
			std::string ps = "PS" + std::to_string(i);
			DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PSShader.hlsl", ps, ps_blob[i], DX12::ShaderType::TYPE_PIXEL);
		}

		unsigned int obj_cbuffer_index = 0;
		unsigned int mat_cbuffer_index = 0;

		m_mesh[0] = std::make_unique<Model::Polygon>();
		m_mesh[0]->Initialize(vs_blob, ps_blob[0], DX12::RootSignatureManager::Get(), obj_cbuffer_index, mat_cbuffer_index);
		m_mesh[0]->SetPos(0.0f, -1.0f, 0.0f);
		m_mesh[0]->SetScale(5.0f, 5.0f, 1.0f);
		m_mesh[0]->SetAngle(270.0f, 0.0f, 0.0f);
		obj_cbuffer_index++;
		mat_cbuffer_index++;
		for (int i = 0; i < DRAW_CALL_NUM; i++)
		{
			m_cube[i] = std::make_unique<Model::CubeMesh>();
			m_cube[i]->Initialize(vs_blob, ps_blob[static_cast<size_t>(i + 1)], DX12::RootSignatureManager::Get(), obj_cbuffer_index, mat_cbuffer_index);
			m_cube[i]->SetPos(-4.0f + static_cast<float>(i), 0.0f, 0.0f);
			m_cube[i]->SetScale(0.3f, 0.3f, 0.3f);
			m_cube[i]->SetAngle(0.0f, 0.0f, 0.0f);
			obj_cbuffer_index++;
			mat_cbuffer_index++;

		}

		DX12::ConstantBufferManager::Build3D(4);

		data.LightDir = { 1.0f,1.0f,1.0f,1.0f };
		data.LightColor = { 1.0f,1.0f,1.0f,1.0f };
		data.AmbientColor = { 0.2f,0.2f,0.2f,1.0f };
		return true;
	}
	bool SceneNoise::Finalize()
	{
		return true;
	}
	void SceneNoise::Update()
	{
		Camera::CameraManager::Update();
		static float time = 0.0f;
		time += 0.1f;

		Math::FVector2 pos = { 0.0f,0.0f };
		DX12::ConstantBufferManager::UpdateCBuffer0(pos);
		DX12::ConstantBufferManager::UpdateCBuffer2(Camera::CameraManager::GetScene3DCamera()->GetMatView(), Camera::CameraManager::GetScene3DCamera()->GetMatProjection(), Camera::CameraManager::GetScene3DCamera()->GetPos(), data.LightColor, data.LightDir, data.AmbientColor);
		for (int i = 0; i < DRAW_CALL_NUM; i++)
		{
			m_cube[i]->SetAngle(0.0f, time, 0.0f);
			m_cube[i]->Update();
		}
		m_mesh[0]->Update();
	}
	void SceneNoise::Render(int frame_count)
	{
		DX12::RootSignatureManager::SetGraphicsRootSignature();
		DX12::CommandList::GetCmd()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		DX12::ConstantBufferManager::SetCBuffer0(0);
		DX12::ConstantBufferManager::SetCBuffer2(2);
		Math::FVector4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
		Math::FVector3 FresnelR0 = { 0.01f, 0.01f, 0.01f };
		float Roughness = 0.25f;
		DX12::ConstantBufferManager::UpdateCBuffer3(DiffuseAlbedo, FresnelR0, Roughness, m_mesh[0]->GetState()->MatCBIndex);
		DX12::ConstantBufferManager::SetCBuffer3(m_mesh[0]->GetState()->MatCBIndex);

		Model::CBSetModelDraw(DX12::CommandList::GetCmd(), m_mesh[0]->GetState());

		for (int i = 0; i < DRAW_CALL_NUM; i++)
		{
			Model::CBSetModelDraw(DX12::CommandList::GetCmd(), m_cube[i]->GetState());
		}
	}
	void SceneNoise::RenderTex()
	{
	}
	void SceneNoise::UpdataGUI()
	{
	}

}