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

	epion::com_ptr<ID3D12DescriptorHeap>       m_pCbvHeap;
	epion::com_ptr<ID3D12Resource>             m_pConstantBuffer;
	UINT8* m_pCbvDataBegin;
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

		m_mesh = std::make_unique < Model::Polygon >();
		m_mesh->Initialize(vs_blob, ps_blob, DX12::RasterizerManager::GetSolidDesc(), DX12::BlendStateManager::GetDesc(), DX12::RootSignatureManager::Get());

		// 定数バッファ用ディスクリプターヒープを生成.
		{
			D3D12_DESCRIPTOR_HEAP_DESC desc = {};
			desc.NumDescriptors = 1;
			desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

			hr = DX12::Device::Get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_pCbvHeap));
		}

		// 定数バッファを生成.
		{
			// ヒーププロパティの設定.
			D3D12_HEAP_PROPERTIES prop = {};
			prop.Type = D3D12_HEAP_TYPE_UPLOAD;
			prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			prop.CreationNodeMask = 1;
			prop.VisibleNodeMask = 1;

			// リソースの設定.
			D3D12_RESOURCE_DESC desc = {};
			desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			desc.Alignment = 0;
			desc.Width = sizeof(ResConstantBuffer);
			desc.Height = 1;
			desc.DepthOrArraySize = 1;
			desc.MipLevels = 1;
			desc.Format = DXGI_FORMAT_UNKNOWN;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			desc.Flags = D3D12_RESOURCE_FLAG_NONE;

			// リソースを生成.
			hr = DX12::Device::Get()->CreateCommittedResource(
				&prop,
				D3D12_HEAP_FLAG_NONE,
				&desc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&m_pConstantBuffer));

			// 定数バッファビューの設定.
			D3D12_CONSTANT_BUFFER_VIEW_DESC bufferDesc = {};
			bufferDesc.BufferLocation = m_pConstantBuffer->GetGPUVirtualAddress();
			bufferDesc.SizeInBytes = sizeof(ResConstantBuffer);

			// 定数バッファビューを生成.
			DX12::Device::Get()->CreateConstantBufferView(&bufferDesc, m_pCbvHeap->GetCPUDescriptorHandleForHeapStart());

			// マップする. アプリケーション終了まで Unmap しない.
			hr = m_pConstantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_pCbvDataBegin));
		}

		// 正常終了.
		return true;
	}
	bool SceneTest::Finalize()
	{
		return true;
	}
	void SceneTest::Update()
	{
		ImGui::Begin("test ", nullptr, 0);
		if (ImGui::TreeNode("model"))
		{
			auto pos = m_mesh->GetPos();
			auto scale = m_mesh->GetScale();
			auto angle = m_mesh->GetAngle();

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

			m_mesh->SetPos(pos.x, pos.y, pos.z);
			m_mesh->SetScale(scale.x, scale.y, scale.z);
			m_mesh->SetAngle(angle.x, angle.y, angle.z);

			ImGui::TreePop();
		}
		//m_mesh->SetAngle(45.0f, 0.0f, 0.0f);

		ImGui::End();
		Camera::CameraManager::Update();
		m_mesh->Update();
		m_ConstantBufferData.World = m_mesh->GetWorldMaxrix();
		m_ConstantBufferData.View = Camera::CameraManager::GetScene3DCamera()->GetMatView();
		m_ConstantBufferData.Proj = Camera::CameraManager::GetScene3DCamera()->GetMatProjection();
		memcpy(m_pCbvDataBegin, &m_ConstantBufferData, sizeof(m_ConstantBufferData));
	}
	void SceneTest::Render()
	{
		DX12::RootSignatureManager::SetGraphicsRootSignature();

		ID3D12DescriptorHeap* pp_heaps[] = { m_pCbvHeap.Get() };
		DX12::CommandList::GetPtr()->SetDescriptorHeaps(1, pp_heaps);
		DX12::CommandList::GetPtr()->SetGraphicsRootDescriptorTable(0, m_pCbvHeap->GetGPUDescriptorHandleForHeapStart());
		m_mesh->Render();
	}
	void SceneTest::RenderTex()
	{
	}
}