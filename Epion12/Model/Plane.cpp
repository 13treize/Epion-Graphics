#include "../Epion12.h"
#include "Plane.h"
#include "../DX12/ViewPort.h"
#include "../DX12/Device.h"
#include "../DX12/CommandList.h"

namespace
{
}

namespace epion::Model
{
	Plane::Plane()
	{
		m_is_update = true;
		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_vertex = std::make_unique<DX12::VertexBuffer>();
		//m_index = std::make_unique<DX12::IndexBuffer>();
		m_pipeline_state = nullptr;
		m_root_signature = nullptr;
		m_pipeline_desc = {};
	}

	Plane::~Plane()
	{
	}
	bool Plane::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, const D3D12_RASTERIZER_DESC& r_desc)
	{
		HRESULT hr = S_OK;

		m_is_update = true;

		m_vertex->Initialize(sizeof(PlaneVertex), sizeof(PlaneVertex) * 4);

		unsigned short indices[] = { 0,1,2, 2,1,3 };

		//m_index->Initialize(sizeof(indices));

		//unsigned short* mappedIdx = nullptr;
		//m_index->GetBuffer()->Map(0, nullptr, (void**)&mappedIdx);
		//std::copy(std::begin(indices), std::end(indices), mappedIdx);
		//m_index->GetBuffer()->Unmap(0, nullptr);


		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);


		m_pipeline_desc = {};
		m_pipeline_desc.pRootSignature = nullptr;
		m_pipeline_desc.VS.pShaderBytecode = vs_blob->GetBufferPointer();
		m_pipeline_desc.VS.BytecodeLength = vs_blob->GetBufferSize();
		m_pipeline_desc.PS.pShaderBytecode = ps_blob->GetBufferPointer();
		m_pipeline_desc.PS.BytecodeLength = ps_blob->GetBufferSize();

		m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;//中身は0xffffffff

		m_pipeline_desc.BlendState.AlphaToCoverageEnable = false;
		m_pipeline_desc.BlendState.IndependentBlendEnable = false;



		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {};

		//ひとまず加算や乗算やαブレンディングは使用しない
		renderTargetBlendDesc.BlendEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		//ひとまず論理演算は使用しない
		renderTargetBlendDesc.LogicOpEnable = false;

		m_pipeline_desc.BlendState.RenderTarget[0] = renderTargetBlendDesc;


		m_pipeline_desc.RasterizerState = r_desc;

		m_pipeline_desc.DepthStencilState.DepthEnable = false;
		m_pipeline_desc.DepthStencilState.StencilEnable = false;

		m_pipeline_desc.InputLayout.pInputElementDescs = m_shader_reflection->GetInputLayout().data();//レイアウト先頭アドレス
		m_pipeline_desc.InputLayout.NumElements = m_shader_reflection->GetInputLayout().size();//レイアウト配列数

		m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;//ストリップ時のカットなし
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;//三角形で構成

		m_pipeline_desc.NumRenderTargets = 1;//今は１つのみ
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//0〜1に正規化されたRGBA

		m_pipeline_desc.SampleDesc.Count = 1;//サンプリングは1ピクセルにつき１
		m_pipeline_desc.SampleDesc.Quality = 0;//クオリティは最低

		D3D12_ROOT_SIGNATURE_DESC root_sig_desc = {};
		root_sig_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		com_ptr<ID3DBlob> root_sig_blob;
		D3D12SerializeRootSignature(&root_sig_desc, D3D_ROOT_SIGNATURE_VERSION_1_0, &root_sig_blob, &m_error_blob);

		DX12::Device::Get()->CreateRootSignature(0, root_sig_blob->GetBufferPointer(), root_sig_blob->GetBufferSize(), IID_PPV_ARGS(&m_root_signature));

		m_root_signature = nullptr;
		D3D12_DESCRIPTOR_RANGE descTblRange[1] = {};//テクスチャと定数の２つ
		descTblRange[0].NumDescriptors = 1;//定数ひとつ
		descTblRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;//種別は定数
		descTblRange[0].BaseShaderRegister = 0;//0番スロットから
		descTblRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		D3D12_ROOT_PARAMETER rootparam = {};
		rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootparam.DescriptorTable.pDescriptorRanges = &descTblRange[0];//デスクリプタレンジのアドレス
		rootparam.DescriptorTable.NumDescriptorRanges = 1;//デスクリプタレンジ数
		rootparam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//全てのシェーダから見える

		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
		rootSignatureDesc.pParameters = &rootparam;//ルートパラメータの先頭アドレス
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		ID3DBlob* rootSigBlob = nullptr;
		hr = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &m_error_blob);
		if (FAILED(hr))
		{
			return	false;
		}

		hr = DX12::Device::Get()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&m_root_signature));
		//rootSigBlob->Release();
		if (FAILED(hr))
		{
			return	false;
		}

		m_pipeline_desc.pRootSignature = m_root_signature.Get();
		hr = DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));

		if (FAILED(hr))
		{
			return	false;
		}

		return true;
	}
	bool Plane::Finalize()
	{
		return true;
	}
	void Plane::Update(const Math::FVector2& d_xy, const Math::FVector2& d_wh)
	{
		if (m_is_update)
		{
			std::valarray<float>	arr_x =
			{
				d_xy.x,				//left-top
				d_xy.x + d_wh.x,	//right-top
				d_xy.x,				//left-bottom
				d_xy.x + d_wh.x,	//right-bottom
			};

			std::valarray<float>	arr_y =
			{
				d_xy.y,				//left-top
				d_xy.y,				//right-top
				d_xy.y + d_wh.y,	//left-bottom
				d_xy.y + d_wh.y,	//right-bottom
			};
			std::array<PlaneVertex, 4> vertices;

			arr_x = 2.0f * arr_x / static_cast<float>(DX12::ViewPort::GetScreenSize().x) - 1.0f;
			arr_y = 1.0f - 2.0f * arr_y / static_cast<float>(DX12::ViewPort::GetScreenSize().y);

			I_FOR(4)
			{
				vertices[i].pos.x = arr_x[i];
				vertices[i].pos.y = arr_y[i];
				vertices[i].pos.z = 0.0f;
				vertices[i].pos.w = 1.0f;
			}
			vertices[0].uv = { 0.0f,1.0f };
			vertices[1].uv = { 0.0f,0.0f };
			vertices[2].uv = { 1.0f,1.0f };
			vertices[3].uv = { 1.0f,0.0f };
			PlaneVertex* vertMap = nullptr;
			m_vertex->GetBuffer()->Map(0, nullptr, (void**)&vertMap);
			std::copy(vertices.begin(), vertices.end(), vertMap);
			m_vertex->GetBuffer()->Unmap(0, nullptr);
		}
		m_is_update = false;
	}
	void Plane::Render()
	{
		DX12::CommandList::GetCmd()->SetPipelineState(m_pipeline_state.Get());
		DX12::CommandList::GetCmd()->SetGraphicsRootSignature(m_root_signature.Get());

		DX12::CommandList::GetCmd()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DX12::CommandList::GetCmd()->IASetVertexBuffers(0, 1, &m_vertex->GetView());
		//DX12::CommandList::GetCmd()->IASetIndexBuffer(&m_index->GetView());
		DX12::CommandList::GetCmd()->DrawIndexedInstanced(6, 1, 0, 0, 0);
	}
}