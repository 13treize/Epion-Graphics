#include "../Epion12.h"
#include "Model.h"


namespace epion::Model
{
	Model::Model()
	{
		m_is_update = true;
		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_vertex_resource= std::make_unique<DX12::ResourceBuffer<Model2DVertex>>();
		m_index_resource = std::make_unique<DX12::ResourceBuffer<unsigned short>>();
		m_pipeline_desc = {};

	}
	void Model::DefaultSetPipeLine(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
		m_pipeline_desc = {};
		m_pipeline_desc.pRootSignature = nullptr;
		m_pipeline_desc.VS.pShaderBytecode = vs_blob->GetBufferPointer();
		m_pipeline_desc.VS.BytecodeLength = vs_blob->GetBufferSize();
		m_pipeline_desc.PS.pShaderBytecode = ps_blob->GetBufferPointer();
		m_pipeline_desc.PS.BytecodeLength = ps_blob->GetBufferSize();

		m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

		m_pipeline_desc.BlendState.AlphaToCoverageEnable = false;
		m_pipeline_desc.BlendState.IndependentBlendEnable = false;

		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {};
		renderTargetBlendDesc.BlendEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		renderTargetBlendDesc.LogicOpEnable = false;

		m_pipeline_desc.BlendState.RenderTarget[0] = renderTargetBlendDesc;

		m_pipeline_desc.RasterizerState = r_desc;
		m_pipeline_desc.DepthStencilState.DepthEnable = false;
		m_pipeline_desc.DepthStencilState.StencilEnable = false;
		m_pipeline_desc.InputLayout.pInputElementDescs = m_shader_reflection->GetInputLayout().data();
		m_pipeline_desc.InputLayout.NumElements = static_cast<UINT>(m_shader_reflection->GetInputLayout().size());
		m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		m_pipeline_desc.NumRenderTargets = 1;
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

		m_pipeline_desc.SampleDesc.Count = 1;
		m_pipeline_desc.SampleDesc.Quality = 0;
		m_pipeline_desc.pRootSignature = root_sig.Get();
	}


	Model3D::Model3D()
	{
		m_is_update = true;
		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_index_resource = std::make_unique<DX12::ResourceBuffer<unsigned short>>();
		m_model_param = std::make_unique<ModelParam>();

		m_pos = {};
		m_angle = {};
		m_scale = {};

	}
	void Model3D::DefaultSetPipeLine(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
		m_pipeline_desc = {};
		m_pipeline_desc.pRootSignature = nullptr;
		m_pipeline_desc.VS.pShaderBytecode = vs_blob->GetBufferPointer();
		m_pipeline_desc.VS.BytecodeLength = vs_blob->GetBufferSize();
		m_pipeline_desc.PS.pShaderBytecode = ps_blob->GetBufferPointer();
		m_pipeline_desc.PS.BytecodeLength = ps_blob->GetBufferSize();

		m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

		m_pipeline_desc.BlendState.AlphaToCoverageEnable = false;
		m_pipeline_desc.BlendState.IndependentBlendEnable = false;

		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {};
		renderTargetBlendDesc.BlendEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		renderTargetBlendDesc.LogicOpEnable = false;

		m_pipeline_desc.BlendState.RenderTarget[0] = renderTargetBlendDesc;

		m_pipeline_desc.RasterizerState = r_desc;
		m_pipeline_desc.DepthStencilState.DepthEnable = false;
		m_pipeline_desc.DepthStencilState.StencilEnable = false;
		m_pipeline_desc.InputLayout.pInputElementDescs = m_shader_reflection->GetInputLayout().data();
		m_pipeline_desc.InputLayout.NumElements = static_cast<UINT>(m_shader_reflection->GetInputLayout().size());
		m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		m_pipeline_desc.NumRenderTargets = 1;
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

		m_pipeline_desc.SampleDesc.Count = 1;
		m_pipeline_desc.SampleDesc.Quality = 0;
		m_pipeline_desc.pRootSignature = root_sig.Get();
	}
	void Model3D::ResourceUpdate()
	{
		DirectX::XMMATRIX S, R, T;
		S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
		R = DirectX::XMMatrixRotationRollPitchYaw(m_angle.x * 0.01745f, m_angle.y * 0.01745f, m_angle.z * 0.01745f);
		T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
		m_model_param->WorldMatrix = S * R * T;
	}

	void Model3D::Draw(com_ptr<ID3D12GraphicsCommandList>& cmd)
	{
		//cmd->SetPipelineState(m_pipeline_state.Get());
		//cmd->IASetVertexBuffers(0, 1, &m_vertex_buffer_view);
		//cmd->IASetIndexBuffer(&m_index_buffer_view);
		//cmd->DrawIndexedInstanced(m_index_resource->GetCount(), 1, 0, 0, 0);
	}

	Math::FVector3& Model3D::GetPos()
	{
		return m_pos;
	}
	Math::FVector3& Model3D::GetAngle()
	{
		return m_angle;
	}
	Math::FVector3& Model3D::GetScale()
	{
		return m_scale;
	}
	std::unique_ptr<ModelParam>& Model3D::GetState()
	{
		return m_model_param;
	}

	void Model3D::SetPos(const float x, const float y, const float z)
	{
		m_pos = { x,y,z };
	}
	void Model3D::SetAngle(const float x, const float y, const float z)
	{
		m_angle = { x,y,z };
	}
	void Model3D::SetScale(const float x, const float y, const float z)
	{
		m_scale = { x,y,z };
	}

}