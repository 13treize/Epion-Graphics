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

		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\VSShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PSShader.hlsl", ps_blob, DX12::ShaderType::TYPE_PIXEL);

		DX12::RootSignatureManager::Build();
		DX12::BlendStateManager::Initialize();
		DX12::RasterizerManager::Initialize();
		Camera::CameraManager::Init(DX12::ViewPort::GetAspect());
		Camera::CameraManager::Update();

		m_mesh[0] = std::make_unique < Model::Polygon >();
		m_mesh[0]->Initialize(vs_blob, ps_blob, DX12::RasterizerManager::GetSolidDesc(), DX12::BlendStateManager::GetDesc(), DX12::RootSignatureManager::Get());
		m_mesh[0]->SetScale(1.0f, 1.0f, 1.0f);

		m_mesh[1] = std::make_unique < Model::Polygon >();
		m_mesh[1]->Initialize(vs_blob, ps_blob, DX12::RasterizerManager::GetSolidDesc(), DX12::BlendStateManager::GetDesc(), DX12::RootSignatureManager::Get());
		m_mesh[1]->SetScale(1.0f, 1.0f, 1.0f);

		DX12::ConstantBufferManager::Initialize();
		// ³íI—¹.
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
		m_mesh[0]->SetPos(1.0, 0.0, 0.0);
		m_mesh[1]->SetPos(-1.0, 0.0, 0.0);

		m_mesh[0]->Update();
		m_mesh[1]->Update();

		Math::FVector2 pos = { 0.0f,0.0f };
		DX12::ConstantBufferManager::UpdateCBuffer0(pos);

	}
	void SceneTest::Render()
	{
		DX12::RootSignatureManager::SetGraphicsRootSignature();
		DX12::ConstantBufferManager::SetCBuffer0();
		DX12::ConstantBufferManager::UpdateCBuffer1(m_mesh[0]->GetWorldMaxrix(), Camera::CameraManager::GetScene3DCamera()->GetMatView(), Camera::CameraManager::GetScene3DCamera()->GetMatProjection());
		DX12::ConstantBufferManager::SetCBuffer1();
		m_mesh[0]->Render();

		//DX12::RootSignatureManager::SetGraphicsRootSignature();
		//DX12::ConstantBufferManager::SetCBuffer0();
		DX12::ConstantBufferManager::UpdateCBuffer1(m_mesh[1]->GetWorldMaxrix(), Camera::CameraManager::GetScene3DCamera()->GetMatView(), Camera::CameraManager::GetScene3DCamera()->GetMatProjection());
		DX12::ConstantBufferManager::SetCBuffer1();
		m_mesh[1]->Render();

	}
	void SceneTest::RenderTex()
	{
	}
}