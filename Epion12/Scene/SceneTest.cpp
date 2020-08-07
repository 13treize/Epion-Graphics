#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"SceneTest.h"

#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"
#include	"../DX12/ViewPort.h"
#include	"../Camera/CameraManager.h"
#include	"../DX12/ShaderManager.h"
#include	"../DX12/BlendState.h"
#include	"../DX12/RasterizerManager.h"
#include	"../DX12/ConstantBufferManager.h"
#include	"../DX12/RootSignature.h"
#include	"../DX12/DescriptorHeap.h"


namespace
{
}
namespace epion
{
	bool SceneTest::Initialize()
	{
		HRESULT hr = S_OK;

		DX12::RootSignatureManager::Build();
		DX12::BlendStateManager::Initialize();
		DX12::RasterizerManager::Initialize();
		Camera::CameraManager::Init(DX12::ViewPort::GetAspect());
		Camera::CameraManager::Update();


		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\VSShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PSShader.hlsl", ps_blob[0], DX12::ShaderType::TYPE_PIXEL);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PSShader.hlsl","PS2", ps_blob[1], DX12::ShaderType::TYPE_PIXEL);


		m_mesh = std::make_unique <Model::Polygon>();
		m_mesh->Initialize(vs_blob, ps_blob[1], DX12::RasterizerManager::GetSolidDesc(), DX12::BlendStateManager::GetDesc(), DX12::RootSignatureManager::Get(),0);
		m_mesh->SetPos(-2.0, 0.0, 0.0);
		m_mesh->SetScale(1.0f, 1.0f, 1.0f);
		m_mesh->SetAngle(45.0f, 0.0f, 0.0f);


		m_mesh2 = std::make_unique <Model::Polygon>();
		m_mesh2->Initialize(vs_blob, ps_blob[0], DX12::RasterizerManager::GetSolidDesc(), DX12::BlendStateManager::GetDesc(), DX12::RootSignatureManager::Get(),1);
		m_mesh2->SetPos(2.0, 0.0, 0.0);
		m_mesh2->SetScale(1.0f, 1.0f, 1.0f);
		m_mesh2->SetAngle(45.0f, 0.0f, 0.0f);


		DX12::ConstantBufferManager::Initialize();

		return true;
	}
	bool SceneTest::Finalize()
	{
		return true;
	}
	void SceneTest::Update()
	{
		//ImGui::Begin("test ", nullptr, 0);
		//if (ImGui::TreeNode("model"))
		//{
		//	auto pos = m_mesh->GetPos();
		//	auto scale = m_mesh->GetScale();
		//	auto angle = m_mesh->GetAngle();
		//	ImGui::Text("Pos");
		//	ImGui::InputFloat("  x", &pos.x, 0.01f, 100.0f, "%.2f");
		//	ImGui::InputFloat("  y", &pos.y, 0.01f, 100.0f, "%.2f");
		//	ImGui::InputFloat("  z", &pos.z, 0.01f, 100.0f, "%.2f");
		//	ImGui::Text("Scale");
		//	ImGui::InputFloat("  x ", &scale.x, 0.01f, 100.0f, "%.2f");
		//	ImGui::InputFloat("  y ", &scale.y, 0.01f, 100.0f, "%.2f");
		//	ImGui::InputFloat("  z ", &scale.z, 0.01f, 100.0f, "%.2f");
		//	ImGui::Text("Angle");
		//	ImGui::InputFloat("  x  ", &angle.x, 0.01f, 100.0f, "%.2f");
		//	ImGui::InputFloat("  y  ", &angle.y, 0.01f, 100.0f, "%.2f");
		//	ImGui::InputFloat("  z  ", &angle.z, 0.01f, 100.0f, "%.2f");
		//	m_mesh->SetPos(pos.x, pos.y, pos.z);
		//	m_mesh->SetScale(scale.x, scale.y, scale.z);
		//	m_mesh->SetAngle(angle.x, angle.y, angle.z);
		//	ImGui::TreePop();
		//}
		////m_mesh->SetAngle(45.0f, 0.0f, 0.0f);
		//ImGui::End();
		Camera::CameraManager::Update();


		m_mesh->Update();
		m_mesh2->Update();

		Math::FVector2 pos = { 0.0f,0.0f };
		DX12::ConstantBufferManager::UpdateCBuffer0(pos);
		Math::FVector4 col, dir, am;
		col = { 0.6,0.6,0.6,1.0 };
		dir = { 0.0,1.0,0.0,1.0 };
		am = { 1.0,0.2,0.2,1.0 };
		DX12::ConstantBufferManager::UpdateCBuffer2(Camera::CameraManager::GetScene3DCamera()->GetMatView(), Camera::CameraManager::GetScene3DCamera()->GetMatProjection(), Camera::CameraManager::GetScene3DCamera()->GetPos(), col, dir, am);

	}
	void SceneTest::Render(int frame_count)
	{
		DX12::RootSignatureManager::SetGraphicsRootSignature();
		DX12::CommandList::GetCmd()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		DX12::ConstantBufferManager::SetCBuffer2(2);
		DX12::ConstantBufferManager::SetCBuffer0(0);

		DX12::ConstantBufferManager::UpdateCBuffer1(m_mesh->GetWorldMaxrix());
		DX12::ConstantBufferManager::SetCBuffer1(1, m_mesh->GetCBIndex());
		m_mesh->Render();

		DX12::ConstantBufferManager::UpdateCBuffer1(m_mesh2->GetWorldMaxrix());
		DX12::ConstantBufferManager::SetCBuffer1(1, m_mesh2->GetCBIndex());
		m_mesh2->Render();
	}
	void SceneTest::RenderTex()
	{
	}
}