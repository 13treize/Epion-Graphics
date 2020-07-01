#include "../Epion12.h"
#include "TestModel.h"

#include "../DX12/ViewPort.h"
#include "../DX12/Device.h"
#include "../DX12/CommandList.h"
#include "../DX12/ConstantBufferManager.h"


namespace
{
	struct Vertex
	{
		epion::Math::FVector3 Position;     //!< 位置座標です.
		epion::Math::FVector3 Normal;       //!< 法線ベクトルです.
		epion::Math::FVector2 TexCoord;     //!< テクスチャ座標です.
		epion::Math::FVector4 Color;        //!< 頂点カラーです.
	};

}

namespace epion::Model
{
	TestModel::TestModel()
	{
	}
	TestModel::~TestModel()
	{
	}
	bool TestModel::init(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
	//	Vertex vertices[] = {
	//{ {  0.0f,  1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
	//{ {  1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
	//{ { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
	//	};


	//	m_vertex->Initialize(sizeof(Vertex), sizeof(Vertex) * vertices.size());

	//	m_index->Initialize(sizeof(unsigned	int) * indices.size());
	//	unsigned short* mappedIdx = nullptr;
	//	m_index->GetBuffer()->Map(0, nullptr, (void**)&mappedIdx);
	//	std::copy(indices.begin(), indices.end(), mappedIdx);
	//	m_index->GetBuffer()->Unmap(0, nullptr);


	//	m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
	//	m_shader_reflection->ReflectionInputLayout(vs_blob);


	//	m_pipeline_desc = {};
	//	m_pipeline_desc.pRootSignature = nullptr;
	//	m_pipeline_desc.VS.pShaderBytecode = vs_blob->GetBufferPointer();
	//	m_pipeline_desc.VS.BytecodeLength = vs_blob->GetBufferSize();
	//	m_pipeline_desc.PS.pShaderBytecode = ps_blob->GetBufferPointer();
	//	m_pipeline_desc.PS.BytecodeLength = ps_blob->GetBufferSize();

	//	m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;//中身は0xffffffff

	//	m_pipeline_desc.BlendState.AlphaToCoverageEnable = false;
	//	m_pipeline_desc.BlendState.IndependentBlendEnable = false;



	//	D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {};

	//	//ひとまず加算や乗算やαブレンディングは使用しない
	//	renderTargetBlendDesc.BlendEnable = false;
	//	renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	//	//ひとまず論理演算は使用しない
	//	renderTargetBlendDesc.LogicOpEnable = false;

	//	m_pipeline_desc.BlendState.RenderTarget[0] = renderTargetBlendDesc;

	//	m_pipeline_desc.RasterizerState = r_desc;

	//	m_pipeline_desc.DepthStencilState.DepthEnable = false;
	//	m_pipeline_desc.DepthStencilState.StencilEnable = false;

	//	m_pipeline_desc.InputLayout.pInputElementDescs = m_shader_reflection->GetInputLayout().data();//レイアウト先頭アドレス
	//	m_pipeline_desc.InputLayout.NumElements = m_shader_reflection->GetInputLayout().size();//レイアウト配列数

	//	m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;//ストリップ時のカットなし
	//	m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;//三角形で構成

	//	m_pipeline_desc.NumRenderTargets = 1;//今は１つのみ
	//	m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//0～1に正規化されたRGBA

	//	m_pipeline_desc.SampleDesc.Count = 1;//サンプリングは1ピクセルにつき１
	//	m_pipeline_desc.SampleDesc.Quality = 0;//クオリティは最低

	//	m_pipeline_desc.pRootSignature = root_sig.Get();
	//	HRESULT hr = DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));

		return true;
	}
	void TestModel::update()
	{
	}
	void TestModel::render()
	{
	}

}