#pragma once
#include"Model.h"
namespace epion::Model
{
	struct	MtlTexture
	{
		//com_ptr<ID3D11ShaderResourceView>	shader_resource_view;
		std::wstring	file_name;
	};

	struct	ObjVertex
	{
		Math::FVector4	position;
		Math::FVector4	normal;
		Math::FVector2	uv;
	};

	struct	Subset
	{
		std::wstring	usemtl;
		unsigned	int	index_start;
		unsigned	int	index_count;
	};

	struct	Material
	{
		std::wstring			newmtl;
		Math::FVector3	Ka;
		Math::FVector3	Kd;
		Math::FVector3	Ks;

		unsigned	int	illum;
		MtlTexture	map_Kd;
		MtlTexture	map_bump;
	};

	class	ObjLoader	final
	{
	public:
		ObjLoader();
		~ObjLoader();

		void	Load(const std::wstring& file_name, bool	flipping_v_coordinates = true);

		std::vector<Material>			materials;
		std::vector<Subset>				subsets;
		std::vector<ObjVertex>			vertices;
		std::vector<unsigned	int>	indices;
		std::vector<std::wstring>		mtl_filenames;

	private:
		//std::vector<material>			materials;
		//std::vector<subset>				subsets;
		//std::vector<obj_vertex>			vertices;
		//std::vector<unsigned	int>	indices;
	};

	class ObjMesh final :public Model
	{
	public:
		ObjMesh();
		~ObjMesh();
		bool Initialize(const std::wstring& file_name,com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig);
		bool Finalize();
		void Update();
		void Render();
	private:
		std::unique_ptr<ObjLoader> m_obj_loader;
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_pipeline_desc;
		com_ptr<ID3D12PipelineState> m_pipeline_state;

		Math::FVector3		m_pos;
		Math::FVector3		m_scale;
		Math::FVector3		m_angle;
		DirectX::XMFLOAT4X4	m_world_matrix;

	};
}