#pragma once
#include"Model.h"
namespace epion::Model
{
	struct SquareVertex
	{
		Math::FVector4 pos;
		Math::FVector2 uv;
	};

	class Square final :public Model
	{
	public:
		Square();
		~Square();
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob);
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc);
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3DBlob>& gs_blob, D3D12_RASTERIZER_DESC& r_desc);
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3DBlob>& hs_blob, com_ptr<ID3DBlob>& ds_blob,com_ptr<ID3DBlob>& gs_blob, D3D12_RASTERIZER_DESC& r_desc);

		bool Finalize();
		void Update(const Math::FVector2& d_xy, const Math::FVector2& d_wh);
		void A();
		void Render();
	private:
		com_ptr<ID3D12RootSignature> m_root_signature;
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_pipeline_desc;
		com_ptr<ID3D12PipelineState> m_pipeline_state;
	};
}