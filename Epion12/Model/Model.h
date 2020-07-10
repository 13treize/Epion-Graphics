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
		std::unique_ptr<DX12::ResourceBuffer<unsigned short>> m_index_resource;

		com_ptr<ID3DBlob> m_error_blob;
		D3D12_INDEX_BUFFER_VIEW m_index_buffer_view;
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_pipeline_desc;
	};

	class Model3D abstract
	{
	public:
		Model3D();
		virtual ~Model3D() {}
		void DefaultSetPipeLine(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig);

		Math::FVector3& GetPos();
		Math::FVector3& GetAngle();
		Math::FVector3& GetScale();
		DirectX::XMMATRIX& GetWorldMaxrix();

		void SetPos(const float x, const float y, const float z);
		void SetAngle(const float x, const float y, const float z);
		void SetScale(const float x, const float y, const float z);


	protected:
		bool m_is_update;
		std::unique_ptr<DX12::ShaderReflection> m_shader_reflection;
		std::unique_ptr<DX12::VertexBuffer> m_vertex;
		std::unique_ptr<DX12::IndexBuffer> m_index;
		std::unique_ptr<DX12::ResourceBuffer<unsigned short>> m_index_resource;

		com_ptr<ID3DBlob> m_error_blob;
		D3D12_INDEX_BUFFER_VIEW m_index_buffer_view;
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_pipeline_desc;

		Math::FVector3 m_pos;
		Math::FVector3 m_angle;
		Math::FVector3 m_scale;
		DirectX::XMMATRIX m_world_matrix;
	};


}