#pragma once
#include	"../DX12/ShaderManager.h"
#include	"../DX12/Buffer.h"
namespace epion::Model
{
	struct PlaneVertex
	{
		Math::FVector4 pos;
		Math::FVector2 uv;
	};

	class Plane final
	{
	public:
		Plane();
		~Plane();
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, const D3D12_RASTERIZER_DESC& r_desc);

		bool Finalize();
		void Update(const Math::FVector2& d_xy, const Math::FVector2& d_wh);
		void Render();
	private:
		bool m_is_update;
		std::unique_ptr<DX12::ShaderReflection> m_shader_reflection;
		std::unique_ptr<DX12::VertexBuffer> m_vertex;
		com_ptr<ID3D12RootSignature> m_root_signature;
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_pipeline_desc;
		com_ptr<ID3D12PipelineState> m_pipeline_state;
		com_ptr<ID3DBlob> m_error_blob;
	};
}
