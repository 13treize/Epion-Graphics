#pragma once
#include"Model.h"
namespace epion::Model
{
	class ObjMesh final :public Model
	{
	public:
		ObjMesh();
		~ObjMesh();
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig);
		bool Finalize();

	private:
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_pipeline_desc;
		com_ptr<ID3D12PipelineState> m_pipeline_state;

	};
}