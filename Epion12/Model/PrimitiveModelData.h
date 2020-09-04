#pragma once
namespace epion::Model
{
	struct Model2DVertex
	{
		Math::FVector4 pos;
		Math::FVector2 uv;
	};

	struct Model3DVertex
	{
		Math::FVector3 Position;
		Math::FVector3 Normal;
		Math::FVector2 UV;
		Math::FVector4 Color;
	};
	struct	ObjVertex
	{
		Math::FVector4	position;
		Math::FVector4	normal;
		Math::FVector2	uv;
	};

	struct MeshData
	{
		std::vector<Model3DVertex> Vertices;
		std::vector<unsigned short> Indices;
	};

	struct CorePrimitive abstract
	{
		virtual ~CorePrimitive() {}
	};
	struct PrimitiveData final
	{
		struct Polygon :CorePrimitive
		{
			static constexpr unsigned int VERTEX_SIZE = 4;
			static constexpr unsigned int INDEX_SIZE = 6;

			static constexpr std::array<Model3DVertex, VERTEX_SIZE>  vertices =
			{
				{
					{ {	-1.0f,	-1.0f, 0.0f },	{ 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ {	-1.0f,	1.0f, 0.0f },	{ 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ {	1.0f,	-1.0f, 0.0f },	{ 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ {	1.0f,	1.0f, 0.0f },	{ 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 1.0f, 1.0f } }
				}
			};

			static constexpr std::array<unsigned short, INDEX_SIZE> indices = { 0,1,2, 2,1,3 };
		};

		struct CubeMesh :CorePrimitive
		{
			static constexpr unsigned int VERTEX_SIZE = 24;
			static constexpr unsigned int INDEX_SIZE = 36;
			static constexpr std::array<Model3DVertex, VERTEX_SIZE> vertices =
			{
				{
					{ {-0.5,-0.5f,-0.5f},{ 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f}, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ {-0.5, 0.5f,-0.5f},{ 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ { 0.5, 0.5f,-0.5f},{ 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ { 0.5,-0.5f,-0.5f},{ 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f}, { 1.0f, 0.0f, 1.0f, 1.0f } },
					{ { 0.5,-0.5f,-0.5f},{ 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f}, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ { 0.5, 0.5f,-0.5f},{ 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ { 0.5, 0.5f, 0.5f},{ 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ { 0.5,-0.5f, 0.5f},{ 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f}, { 1.0f, 0.0f, 1.0f, 1.0f } },
					{ {-0.5,-0.5f, 0.5f},{ 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f}, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ {-0.5, 0.5f, 0.5f},{ 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ {-0.5, 0.5f,-0.5f},{ 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ {-0.5,-0.5f,-0.5f},{ 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f}, { 1.0f, 0.0f, 1.0f, 1.0f } },
					{ { 0.5,-0.5f, 0.5f},{ 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f}, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ { 0.5, 0.5f, 0.5f},{ 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ {-0.5, 0.5f, 0.5f},{ 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ {-0.5,-0.5f, 0.5f},{ 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f}, { 1.0f, 0.0f, 1.0f, 1.0f } },
					{ {-0.5, 0.5f,-0.5f},{ 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f}, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ {-0.5, 0.5f, 0.5f},{ 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ { 0.5, 0.5f, 0.5f},{ 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ { 0.5, 0.5f,-0.5f},{ 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f}, { 1.0f, 0.0f, 1.0f, 1.0f } },
					{ {-0.5,-0.5f, 0.5f},{ 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f}, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ {-0.5,-0.5f,-0.5f},{ 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ { 0.5,-0.5f,-0.5f},{ 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ { 0.5,-0.5f, 0.5f},{ 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f}, { 1.0f, 0.0f, 1.0f, 1.0f } }
				}
			};
			static constexpr std::array<unsigned short, INDEX_SIZE> indices =
			{
				0, 1, 2, 2, 3,0,
				4, 5, 6, 6, 7,4,
				8, 9, 10, 10, 11, 8,
				12,13,14, 14,15,12,
				16,17,18, 18,19,16,
				20,21,22, 22,23,20
			};
		};

		struct Sphere
		{
			MeshData mesh;

			void CreateSphere(float radius, unsigned int sliceCount, unsigned int stackCount)
			{
				mesh.Vertices.clear();
				mesh.Indices.clear();
				unsigned int num_vertices = (sliceCount + 1) * (stackCount + 1);
				for (int y = 0; y < stackCount + 1; y++)
				{
					for (int x = 0; x < sliceCount + 1; x++)
					{
						Model3DVertex vertices;
						int index = y * (sliceCount + 1) + x;
						float h = 0.5f * cosf(y * Math::pi<float> / stackCount);
						float w = 0.5f * sinf(y * Math::pi<float> / stackCount);
						float rad_slices = x * Math::pi<float> * 2.0f / sliceCount;

						vertices.Position.x = w * sinf(rad_slices);
						vertices.Position.y = h;
						vertices.Position.z = w * cosf(rad_slices);

						vertices.Normal.x = vertices.Position.x * 2.0f;
						vertices.Normal.y = vertices.Position.y * 2.0f;
						vertices.Normal.z = vertices.Position.z * 2.0f;

						vertices.UV.x = 1.0f - (float)x / sliceCount;
						vertices.UV.y = (float)y / stackCount - 1.0f;
						vertices.Color = Math::FVector4(1.0f, 1.0f, 1.0f, 1.0f);
						mesh.Vertices.push_back(vertices);
					}
				}
				unsigned int num_indices = stackCount * sliceCount * 2 * 3;
				mesh.Indices.resize(num_indices);

				for (int y = 0; y < stackCount; y++)
				{
					for (int x = 0; x < sliceCount; x++)
					{
						int face = (y * sliceCount + x);
						int vertices_index = y * (sliceCount + 1) + x;
						mesh.Indices[face * 6] = vertices_index + 1;
						mesh.Indices[face * 6 + 1] = vertices_index;
						mesh.Indices[face * 6 + 2] = vertices_index + (sliceCount + 1);
						mesh.Indices[face * 6 + 3] = vertices_index + 1;
						mesh.Indices[face * 6 + 4] = vertices_index + (sliceCount + 1);
						mesh.Indices[face * 6 + 5] = vertices_index + (sliceCount + 1) + 1;
					}
				}
			}
		};
	};
}