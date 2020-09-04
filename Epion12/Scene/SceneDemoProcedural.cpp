#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"SceneDemoProcedural.h"

#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"
#include	"../DX12/ViewPort.h"
#include	"../Camera/CameraManager.h"
#include	"../DX12/ShaderManager.h"
#include	"../DX12/DX12State.h"
#include	"../DX12/RootSignature.h"
#include	"../DX12/DescriptorHeap.h"


namespace
{
	constexpr int DRAW_CALL_NUM = 2;
}
namespace epion
{
	bool SceneProcedural::Initialize()
	{
		HRESULT hr = S_OK;

		DX12::RootSignatureManager::Build();
		DX12::BlendStateManager::Initialize();
		DX12::RasterizerManager::Initialize();
		Camera::CameraManager::Init(DX12::ViewPort::GetAspect());
		Camera::CameraManager::Update();

		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\VSShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PSShader.hlsl", ps_blob[0], DX12::ShaderType::TYPE_PIXEL);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PSShader.hlsl", "PS2", ps_blob[1], DX12::ShaderType::TYPE_PIXEL);

		unsigned int cbuffer_index = 0;

		for (int i = 0; i < DRAW_CALL_NUM ; i++)
		{
			m_mesh[i] = std::make_unique <Model::Polygon>();
			m_mesh[i]->Initialize(vs_blob, ps_blob[0], DX12::RasterizerManager::GetSolidDesc(), DX12::BlendStateManager::GetDesc(), DX12::RootSignatureManager::Get(), cbuffer_index);
			m_mesh[i]->SetPos(-2.0+static_cast<float>(i*2.0), 0.0, 0.0);
			m_mesh[i]->SetScale(1.0f, 1.0f, 1.0f);
			m_mesh[i]->SetAngle(45.0f, 0.0f, 0.0f);
			cbuffer_index++;

		}
		DX12::ConstantBufferManager::Build3D(3);
		data.LightDir = { 0.0,1.0,0.0,1.0 };
		data.LightColor = { 0.2,0.2,0.2,1.0 };
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
			ImGui::Text("Pos");
			ImGui::InputFloat("  x", &pos.x, 0.01f, 100.0f, "%.2f");
			ImGui::InputFloat("  y", &pos.y, 0.01f, 100.0f, "%.2f");
			ImGui::InputFloat("  z", &pos.z, 0.01f, 100.0f, "%.2f");
			ImGui::Text("Scale");
			ImGui::InputFloat("  x ", &scale.x, 0.01f, 100.0f, "%.2f");
			ImGui::InputFloat("  y ", &scale.y, 0.01f, 100.0f, "%.2f");
			ImGui::InputFloat("  z ", &scale.z, 0.01f, 100.0f, "%.2f");
			ImGui::Text("Angle");
			ImGui::InputFloat("  x  ", &angle.x, 0.01f, 100.0f, "%.2f");
			ImGui::InputFloat("  y  ", &angle.y, 0.01f, 100.0f, "%.2f");
			ImGui::InputFloat("  z  ", &angle.z, 0.01f, 100.0f, "%.2f");
			data.LightDir = pos;
			data.LightColor = scale;
			data.AmbientColor = angle;

			ImGui::TreePop();
		}
		//m_mesh->SetAngle(45.0f, 0.0f, 0.0f);
		ImGui::End();
		Camera::CameraManager::Update();

		for (int i = 0; i < DRAW_CALL_NUM; i++)
		{
			m_mesh[i]->Update();
		}
		Math::FVector2 pos = { 0.0f,0.0f };
		DX12::ConstantBufferManager::UpdateCBuffer0(pos);

		DX12::ConstantBufferManager::UpdateCBuffer2(Camera::CameraManager::GetScene3DCamera()->GetMatView(), Camera::CameraManager::GetScene3DCamera()->GetMatProjection(), Camera::CameraManager::GetScene3DCamera()->GetPos(), data.LightColor, data.LightDir, data.AmbientColor);

	}
	void SceneProcedural::Render(int frame_count)
	{
		DX12::RootSignatureManager::SetGraphicsRootSignature();
		DX12::CommandList::GetCmd()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		DX12::ConstantBufferManager::SetCBuffer0(0);
		DX12::ConstantBufferManager::SetCBuffer2(2);

		for (int i = 0; i < DRAW_CALL_NUM; i++)
		{
			DX12::ConstantBufferManager::UpdateCBuffer1(m_mesh[i]->GetState()->WorldMatrix, m_mesh[i]->GetState()->ObjCBIndex);
			DX12::ConstantBufferManager::SetCBuffer1(m_mesh[i]->GetState()->ObjCBIndex);
			Model::ModelParamDraw(DX12::CommandList::GetCmd(), m_mesh[i]->GetState());
		}
	}
	void SceneProcedural::RenderTex()
	{
	}
}