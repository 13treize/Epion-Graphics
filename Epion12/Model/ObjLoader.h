#pragma once
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

		void	Load(const std::wstring&	file_name, bool	flipping_v_coordinates = true);

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

}