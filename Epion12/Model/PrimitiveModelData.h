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
				MeshData mesh_data;

				Model3DVertex topVertex;
				topVertex.Position = Math::FVector3(0.0f, +radius, 0.0f);
				topVertex.Normal = Math::FVector3(0.0f, 1.0f, 0.0f);
				topVertex.UV = Math::FVector2(0.0f, 0.0f);
				topVertex.Color = Math::FVector4(0.0f, 0.0f, 0.0f, 0.0f);

				Model3DVertex bottomVertex;
				topVertex.Position = Math::FVector3(0.0f, -radius, 0.0f);
				topVertex.Normal = Math::FVector3(0.0f, -1.0f, 0.0f);
				topVertex.UV = Math::FVector2(0.0f, 1.0f);
				topVertex.Color = Math::FVector4(0.0f, 0.0f, 0.0f, 0.0f);

				mesh_data.Vertices.push_back(topVertex);

				float phiStep = Math::pi<float> / stackCount;
				float thetaStep = 2.0f * Math::pi<float> / sliceCount;

				// Compute vertices for each stack ring (do not count the poles as rings).
				for (unsigned short i = 1; i <= stackCount - 1; ++i)
				{
					float phi = i * phiStep;

					// Vertices of ring.
					for (unsigned short j = 0; j <= sliceCount; ++j)
					{
						float theta = j * thetaStep;

						Math::FVector3 p;
						Model3DVertex v;

						// spherical to cartesian
						v.Position.x = radius * sinf(phi) * cosf(theta);
						v.Position.y = radius * cosf(phi);
						v.Position.z = radius * sinf(phi) * sinf(theta);

						p = v.Position;
						v.Normal = p.normalize();

						v.UV.x = theta / (Math::pi<float> * 2.0f);
						v.UV.y = phi / Math::pi<float>;
						v.Color = Math::FVector4(0.0f, 0.0f, 0.0f, 0.0f);

						mesh_data.Vertices.push_back(v);
					}
				}

				mesh_data.Vertices.push_back(bottomVertex);

				for (unsigned short i = 1; i <= sliceCount; ++i)
				{
					mesh_data.Indices.push_back(0);
					mesh_data.Indices.push_back(i + 1);
					mesh_data.Indices.push_back(i);
				}

				unsigned short baseIndex = 1;
				unsigned short ringVertexCount = sliceCount + 1;
				for (unsigned short i = 0; i < stackCount - 2; ++i)
				{
					for (unsigned short j = 0; j < sliceCount; ++j)
					{
						mesh_data.Indices.push_back(baseIndex + i * ringVertexCount + j);
						mesh_data.Indices.push_back(baseIndex + i * ringVertexCount + j + 1);
						mesh_data.Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

						mesh_data.Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
						mesh_data.Indices.push_back(baseIndex + i * ringVertexCount + j + 1);
						mesh_data.Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
					}
				}

				unsigned short southPoleIndex = (unsigned short)mesh_data.Vertices.size() - 1;

				baseIndex = southPoleIndex - ringVertexCount;

				for (unsigned short i = 0; i < sliceCount; ++i)
				{
					mesh_data.Indices.push_back(southPoleIndex);
					mesh_data.Indices.push_back(baseIndex + i);
					mesh_data.Indices.push_back(baseIndex + i + 1);
				}

				mesh = mesh_data;
			}
		};
	};
}