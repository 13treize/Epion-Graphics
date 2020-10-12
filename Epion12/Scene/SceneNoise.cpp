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
	constexpr int DRAW_CALL_NUM = 12;
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
		//DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PSShader.hlsl", ps_blob[0], DX12::ShaderType::TYPE_PIXEL);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PS\\SceneNoiseDemo.hlsl", "PS0", ps_blob[0], DX12::ShaderType::TYPE_PIXEL);
		//DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PSShader.hlsl", "PS3", ps_blob[3], DX12::ShaderType::TYPE_PIXEL);

		unsigned int obj_cbuffer_index = 0;
		unsigned int mat_cbuffer_index = 0;

		for (int i = 0; i < DRAW_CALL_NUM; i++)
		{
			m_mesh[i] = std::make_unique<Model::Polygon>();
			m_mesh[i]->Initialize(vs_blob, ps_blob[0], DX12::RootSignatureManager::Get(), obj_cbuffer_index, mat_cbuffer_index);
			m_mesh[i]->SetPos(0.0, 0.0, 0.0);
			m_mesh[i]->SetScale(0.1f, 1.0f, 0.1f);
			m_mesh[i]->SetAngle(270.0f, 0.0f, 0.0f);
			obj_cbuffer_index++;
			mat_cbuffer_index++;
		}
		m_mesh[0]->SetPos(0.0f, 0.0f, 0.0f);
		m_mesh[1]->SetPos(1.0f, 0.0f, 0.0f);
		m_mesh[2]->SetPos(2.0f, 0.0f, 0.0f);
		m_mesh[3]->SetPos(3.0f, 0.0f, 0.0f);

		m_mesh[4]->SetPos(0.0f, 0.0f, 1.0f);
		m_mesh[5]->SetPos(1.0f, 0.0f, 1.0f);
		m_mesh[6]->SetPos(2.0f, 0.0f, 1.0f);
		m_mesh[7]->SetPos(3.0f, 0.0f, 1.0f);

		m_mesh[8]->SetPos(0.0f, 0.0f, 1.0f);
		m_mesh[9]->SetPos(1.0f, 0.0f, 1.0f);
		m_mesh[10]->SetPos(2.0f, 0.0f, 1.0f);
		m_mesh[11]->SetPos(3.0f, 0.0f, 1.0f);

		DX12::ConstantBufferManager::Build3D(3);

		return true;
	}
	bool SceneNoise::Finalize()
	{
		return true;
	}
	void SceneNoise::Update()
	{
		DX12::CBufferPassConstants data;

		data.LightDir = { 1.0,1.0,1.0,1.0 };
		data.LightColor = { 1.0,1.0,1.0,1.0 };
		data.AmbientColor = { 0.2,0.2,0.2,1.0 };

		Camera::CameraManager::Update();
		static float time = 0.0f;
		time += 0.1f;


		Math::FVector2 pos = { 0.0f,0.0f };
		DX12::ConstantBufferManager::UpdateCBuffer0(pos);
		DX12::ConstantBufferManager::UpdateCBuffer2(Camera::CameraManager::GetScene3DCamera()->GetMatView(), Camera::CameraManager::GetScene3DCamera()->GetMatProjection(), Camera::CameraManager::GetScene3DCamera()->GetPos(), data.LightColor, data.LightDir, data.AmbientColor);

		for (int i = 0; i < DRAW_CALL_NUM; i++)
		{
			m_mesh[i]->Update();
		}
	}
	void SceneNoise::Render(int frame_count)
	{
		DX12::RootSignatureManager::SetGraphicsRootSignature();
		DX12::CommandList::GetCmd()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		DX12::ConstantBufferManager::SetCBuffer0(0);
		DX12::ConstantBufferManager::SetCBuffer2(2);

		for (int i = 0; i < DRAW_CALL_NUM; i++)
		{
			Model::CBSetModelDraw(DX12::CommandList::GetCmd(), m_mesh[i]->GetState());
		}

	}
	void SceneNoise::RenderTex()
	{
	}
	void SceneNoise::UpdataGUI()
	{
	}

}