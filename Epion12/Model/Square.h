#pragma once
#include"Model.h"
namespace epion::Model
{

	class Square final :public ModelCore
	{
	public:
		Square();
		~Square();
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3D12RootSignature>& root_sig);
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3DBlob>& gs_blob, com_ptr<ID3D12RootSignature>& root_sig);
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3DBlob>& hs_blob, com_ptr<ID3DBlob>& ds_blob,com_ptr<ID3DBlob>& gs_blob, com_ptr<ID3D12RootSignature>& root_sig);

		bool Finalize();
		void Update(const Math::FVector2& d_xy, const Math::FVector2& d_wh, const Math::FVector2& sc_size);
		void Render();
	private:
		com_ptr<ID3D12PipelineState> m_pipeline_state;
	};
}
