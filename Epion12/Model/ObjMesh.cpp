#include "../Epion12.h"
#include "ObjMesh.h"
#include "../DX12/ViewPort.h"
#include "../DX12/Device.h"
#include "../DX12/CommandList.h"

namespace
{
}

namespace epion::Model
{
	ObjMesh::ObjMesh()
		:Model()
	{
		m_pipeline_state = nullptr;
		m_pipeline_desc = {};
	}


	ObjMesh::~ObjMesh()
	{
	}
	bool ObjMesh::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
		m_is_update = true;

		m_vertex->Initialize(sizeof(SquareVertex), sizeof(SquareVertex) * 4);

		unsigned short indices[] = { 0,1,2, 2,1,3 };

		m_index->Initialize(sizeof(indices));

		unsigned short* mappedIdx = nullptr;
		m_index->GetBuffer()->Map(0, nullptr, (void**)&mappedIdx);
		std::copy(std::begin(indices), std::end(indices), mappedIdx);
		m_index->GetBuffer()->Unmap(0, nullptr);


		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);


		m_pipeline_desc = {};
		m_pipeline_desc.pRootSignature = nullptr;
		m_pipeline_desc.VS.pShaderBytecode = vs_blob->GetBufferPointer();
		m_pipeline_desc.VS.BytecodeLength = vs_blob->GetBufferSize();
		m_pipeline_desc.PS.pShaderBytecode = ps_blob->GetBufferPointer();
		m_pipeline_desc.PS.BytecodeLength = ps_blob->GetBufferSize();

		m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;//���g��0xffffffff

		m_pipeline_desc.BlendState.AlphaToCoverageEnable = false;
		m_pipeline_desc.BlendState.IndependentBlendEnable = false;



		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {};

		//�ЂƂ܂����Z���Z�⃿�u�����f�B���O�͎g�p���Ȃ�
		renderTargetBlendDesc.BlendEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		//�ЂƂ܂��_�����Z�͎g�p���Ȃ�
		renderTargetBlendDesc.LogicOpEnable = false;

		m_pipeline_desc.BlendState.RenderTarget[0] = renderTargetBlendDesc;

		m_pipeline_desc.RasterizerState = r_desc;

		m_pipeline_desc.DepthStencilState.DepthEnable = false;
		m_pipeline_desc.DepthStencilState.StencilEnable = false;

		m_pipeline_desc.InputLayout.pInputElementDescs = m_shader_reflection->GetInputLayout().data();//���C�A�E�g�擪�A�h���X
		m_pipeline_desc.InputLayout.NumElements = m_shader_reflection->GetInputLayout().size();//���C�A�E�g�z��

		m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;//�X�g���b�v���̃J�b�g�Ȃ�
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;//�O�p�`�ō\��

		m_pipeline_desc.NumRenderTargets = 1;//���͂P�̂�
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//0�`1�ɐ��K�����ꂽRGBA

		m_pipeline_desc.SampleDesc.Count = 1;//�T���v�����O��1�s�N�Z���ɂ��P
		m_pipeline_desc.SampleDesc.Quality = 0;//�N�I���e�B�͍Œ�

		m_pipeline_desc.pRootSignature = root_sig.Get();
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));

		return true;
	}
	bool ObjMesh::Finalize()
	{
		return true;
	}


}