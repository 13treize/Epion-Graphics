#pragma once
#include	"../DX12/ShaderManager.h"
#include	"../DX12/Buffer.h"
namespace epion::Model
{
	class Model abstract
	{
	public:
		Model();
		virtual ~Model() {}
		void DefaultSetPipeLine(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig);
	protected:
		bool m_is_update;
		std::unique_ptr<DX12::ShaderReflection> m_shader_reflection;
		std::unique_ptr<DX12::VertexBuffer> m_vertex;
		std::unique_ptr<DX12::IndexBuffer> m_index;
		com_ptr<ID3DBlob> m_error_blob;
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_pipeline_desc;

	};
}