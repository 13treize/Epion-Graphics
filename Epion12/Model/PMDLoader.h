#pragma once

namespace epion::Model
{
	struct PMDHeader
	{
		float version;
		std::string name;
		std::string comment;
	};

	struct PMDVertex
	{
		Math::FVector3 position;
		Math::FVector3 normal;
		Math::FVector3 uv;
		Math::Vector2<uint16_t> bone_index;
		uint8_t bone_weight;
		bool edge_invisible;
	};

	struct PMDMaterial
	{
	public:
		Math::FVector4 diffuse;
		float power;
		Math::FVector3 specular;
		Math::FVector3 ambient;
		uint8_t toon_index;
		uint8_t edge_flag;
		uint32_t index_count;
		std::string texture_filename;
		std::string sphere_filename;
	};

	class PMDLoader final
	{
	public:
		void HeaderLoad();
		void VertexLoad();


	private:
		std::unique_ptr<std::ifstream>	ifs;
	};
}