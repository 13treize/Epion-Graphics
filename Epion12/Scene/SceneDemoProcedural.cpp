#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"SceneDemoProcedural.h"

#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"
#include	"../DX12/ViewPort.h"
#include	"../Camera/CameraManager.h"
#include	"../DX12/ShaderManager.h"
#include	"../DX12/RootSignature.h"
#include	"../DX12/DescriptorHeap.h"


namespace
{
	constexpr int DRAW_CALL_NUM = 1;
}
namespace epion
{
	bool SceneProcedural::Initialize()
	{
		HRESULT hr = S_OK;

		DX12::RootSignatureManager::Build();
		Camera::CameraManager::Init(DX12::ViewPort::GetAspect());
		Camera::CameraManager::Update();

		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\VSShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		//DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PSShader.hlsl", ps_blob[0], DX12::ShaderType::TYPE_PIXEL);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PSShader.hlsl", "PS0", ps_blob[0], DX12::ShaderType::TYPE_PIXEL);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PSShader.hlsl", "PS1", ps_blob[1], DX12::ShaderType::TYPE_PIXEL);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PSShader.hlsl", "PS2", ps_blob[2], DX12::ShaderType::TYPE_PIXEL);
		//DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PSShader.hlsl", "PS3", ps_blob[3], DX12::ShaderType::TYPE_PIXEL);

		unsigned int obj_cbuffer_index = 0;
		unsigned int mat_cbuffer_index = 0;

		m_mesh[0] = std::make_unique<Model::Polygon>();
		m_mesh[0]->Initialize(vs_blob, ps_blob[0], DX12::RootSignatureManager::Get(), obj_cbuffer_index, mat_cbuffer_index);
		m_mesh[0]->SetPos(0.0f, -1.0f, 0.0f);
		m_mesh[0]->SetScale(5.0f, 5.0f, 1.0f);
		m_mesh[0]->SetAngle(270.0f, 0.0f, 0.0f);
		obj_cbuffer_index++;
		mat_cbuffer_index++;
		for (int i = 0; i < DRAW_CALL_NUM ; i++)
		{
			m_cube[i] = std::make_unique<Model::CubeMesh>();
			m_cube[i]->Initialize(vs_blob, ps_blob[1], DX12::RootSignatureManager::Get(), obj_cbuffer_index, mat_cbuffer_index);
			m_cube[i]->SetPos(0.0, 0.0, 0.0);
			m_cube[i]->SetScale(0.5f, 0.5f, 0.5f);
			m_cube[i]->SetAngle(0.0f, 0.0f, 0.0f);
			obj_cbuffer_index++;
			mat_cbuffer_index++;

		}

		DX12::ConstantBufferManager::Build3D(4);

		data.LightDir = { 1.0,1.0,1.0,1.0 };
		data.LightColor = { 1.0,1.0,1.0,1.0 };
		data.AmbientColor = { 0.2,0.2,0.2,1.0 };

		return true;
	}
	bool SceneProcedural::Finalize()
	{
		return true;
	}
	void SceneProcedural::Update()
	{
	ImGui::Begin("test ", nullptr, 0);
	if (ImGui::TreeNode("model"))
	{
		auto pos = data.LightDir;
		auto scale = data.LightColor;
		auto angle = data.AmbientColor;
		ImGui::Text("dir");
		ImGui::InputFloat("  x", &pos.x, 0.01f, 100.0f, "%.2f");
		ImGui::InputFloat("  y", &pos.y, 0.01f, 100.0f, "%.2f");
		ImGui::InputFloat("  z", &pos.z, 0.01f, 100.0f, "%.2f");
		ImGui::Text("color");
		ImGui::InputFloat("  x ", &scale.x, 0.01f, 100.0f, "%.2f");
		ImGui::InputFloat("  y ", &scale.y, 0.01f, 100.0f, "%.2f");
		ImGui::InputFloat("  z ", &scale.z, 0.01f, 100.0f, "%.2f");
		ImGui::Text("ambent");
		ImGui::InputFloat("  x  ", &angle.x, 0.01f, 100.0f, "%.2f");
		ImGui::InputFloat("  y  ", &angle.y, 0.01f, 100.0f, "%.2f");
		ImGui::InputFloat("  z  ", &angle.z, 0.01f, 100.0f, "%.2f");
		data.LightDir = pos;
		data.LightColor = scale;
		data.AmbientColor = angle;

		ImGui::TreePop();
	}
	ImGui::End();
		Camera::CameraManager::Update();
		static float time = 0.0f;
		time += 0.1f;


		Math::FVector2 pos = { 0.0f,0.0f };
		DX12::ConstantBufferManager::UpdateCBuffer0(pos);
		DX12::ConstantBufferManager::UpdateCBuffer2(Camera::CameraManager::GetScene3DCamera()->GetMatView(), Camera::CameraManager::GetScene3DCamera()->GetMatProjection(), Camera::CameraManager::GetScene3DCamera()->GetPos(), data.LightColor, data.LightDir, data.AmbientColor);
		//Math::FVector4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
		//Math::FVector3 FresnelR0 = { 0.01f, 0.01f, 0.01f };
		//float Roughness = 0.25f;
		//DX12::ConstantBufferManager::UpdateCBuffer3(DiffuseAlbedo,FresnelR0,Roughness,0);
		for (int i = 0; i < DRAW_CALL_NUM; i++)
		{
			m_cube[i]->SetAngle(0.0f,time, 0.0f);
			m_cube[i]->Update();
			//m_mesh[i]->SetAngle(0.0f, time, 0.0f);
			m_mesh[i]->Update();


		}
	}
	void SceneProcedural::Render(int frame_count)
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

		//for (int i = 0; i < DRAW_CALL_NUM; i++)
		//{
		Model::CBSetModelDraw(DX12::CommandList::GetCmd(), m_mesh[0]->GetState());

		Model::CBSetModelDraw(DX12::CommandList::GetCmd(), m_cube[0]->GetState());
		//}
	}
	void SceneProcedural::RenderTex()
	{
	}
}