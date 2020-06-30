#pragma once
#include"Model.h"

namespace epion::Model
{
	struct StaticMeshVertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normal;
	};
	struct cbuffer
	{
		DirectX::XMFLOAT4X4 world_view_projection;
		DirectX::XMFLOAT4X4 world_inverse_transpose;
	};

	class StaticMesh final :public Model
	{
	public:
		StaticMesh();
		~StaticMesh();
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig);
		bool Finalize();
		void CBufferUpdate();
		void Update();
		void Render();

		DirectX::XMFLOAT4X4& GetWorldMatrix();

	private:
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_pipeline_desc;
		com_ptr<ID3D12PipelineState> m_pipeline_state;

		Math::FVector3		m_pos;
		Math::FVector3		m_scale;
		Math::FVector3		m_angle;
		DirectX::XMFLOAT4X4	m_world_matrix;

	};

}