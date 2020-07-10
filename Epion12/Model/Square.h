#pragma once
#include"Model.h"
namespace epion::Model
{

	class Square final :public Model
	{
	public:
		Square();
		~Square();
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, D3D12_BLEND_DESC& b_desc, com_ptr<ID3D12RootSignature>& root_sig);
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3DBlob>& gs_blob, D3D12_RASTERIZER_DESC& r_desc, D3D12_BLEND_DESC& b_desc, com_ptr<ID3D12RootSignature>& root_sig);
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3DBlob>& hs_blob, com_ptr<ID3DBlob>& ds_blob,com_ptr<ID3DBlob>& gs_blob, D3D12_RASTERIZER_DESC& r_desc, D3D12_BLEND_DESC& b_desc, com_ptr<ID3D12RootSignature>& root_sig);

		bool Finalize();
		void Update(const Math::FVector2& d_xy, const Math::FVector2& d_wh);
		void Render();
	private:
		com_ptr<ID3D12PipelineState> m_pipeline_state;
	};
}
