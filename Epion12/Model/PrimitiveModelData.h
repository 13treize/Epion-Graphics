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

			static constexpr std::array<Model3DVertex, VERTEX_SIZE> vertices =
			{
				{
					{ {	-1.0f,	-1.0f, 0.0f },	{ 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ {	1.0f,	-1.0f, 0.0f },	{ 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ {	1.0f,	1.0f, 0.0f },	{ 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ {	-1.0f,	1.0f, 0.0f },	{ 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 1.0f, 1.0f } }
				}
			};

			static constexpr std::array<unsigned short, INDEX_SIZE> indices = { 0,1,2, 0,2,3 };
		};

		struct CubeMesh :CorePrimitive
		{
			static constexpr unsigned int VERTEX_SIZE = 24;
			static constexpr unsigned int INDEX_SIZE = 36;
			static constexpr std::array<Model3DVertex, VERTEX_SIZE> vertices =
			{
				{

					{ {-1.0f,	-1.0f,	-1.0f},{ 0.0f, 0.0f,-1.0f },{ 0.0f, 1.0f}, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ {-1.0f,	 1.0f,	-1.0f},{ 0.0f, 0.0f,-1.0f },{ 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ { 1.0f,	 1.0f,	-1.0f},{ 0.0f, 0.0f,-1.0f },{ 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ { 1.0f,	-1.0f,	-1.0f},{ 0.0f, 0.0f,-1.0f },{ 1.0f, 1.0f}, { 1.0f, 0.0f, 1.0f, 1.0f } },

					{ {-1.0f,	-1.0f,	 1.0f},{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f}, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ { 1.0f,	-1.0f,	 1.0f},{ 0.0f, 0.0f, 1.0f },{ 0.0f, 1.0f}, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ { 1.0f,	 1.0f,	 1.0f},{ 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f}, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ {-1.0f,	 1.0f,	 1.0f},{ 0.0f, 0.0f, 1.0f },{ 1.0f, 0.0f}, { 1.0f, 0.0f, 1.0f, 1.0f } },

					{ {-1.0f,	 1.0f,	-1.0f},{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f}, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ {-1.0f,	 1.0f,	+1.0f},{ 0.0f, 1.0f, 0.0f },{ 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ { 1.0f,	 1.0f,	+1.0f},{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ { 1.0f,	 1.0f,	-1.0f},{ 0.0f, 1.0f, 0.0f },{ 1.0f, 1.0f}, { 1.0f, 0.0f, 1.0f, 1.0f } },

					{ {-1.0f,	-1.0f,	-1.0f},{ 0.0f,-1.0f, 0.0f },{ 1.0f, 1.0f}, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ { 1.0f,	-1.0f,	-1.0f},{ 0.0f,-1.0f, 0.0f },{ 0.0f, 1.0f}, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ { 1.0f,	-1.0f,	 1.0f},{ 0.0f,-1.0f, 0.0f },{ 0.0f, 0.0f}, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ {-1.0f,	-1.0f,	 1.0f},{ 0.0f,-1.0f, 0.0f },{ 1.0f, 0.0f}, { 1.0f, 0.0f, 1.0f, 1.0f } },

					{ {-1.0f,	-1.0f,	 1.0f},{-1.0f, 0.0f, 0.0f },{ 0.0f, 1.0f}, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ {-1.0f,	 1.0f,	 1.0f},{-1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ {-1.0f,	 1.0f,	-1.0f},{-1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ {-1.0f,	-1.0f,	-1.0f},{-1.0f, 0.0f, 0.0f },{ 1.0f, 1.0f}, { 1.0f, 0.0f, 1.0f, 1.0f } },

					{ { 1.0f,	-1.0f,	-1.0f},{ 1.0f, 0.0f, 0.0f },{ 0.0f, 1.0f}, { 1.0f, 0.0f, 0.0f, 1.0f } },
					{ { 1.0f,	 1.0f,	-1.0f},{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f, 1.0f } },
					{ { 1.0f,	 1.0f,	 1.0f},{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f, 1.0f } },
					{ { 1.0f,	-1.0f,	 1.0f},{ 1.0f, 0.0f, 0.0f },{ 1.0f, 1.0f}, { 1.0f, 0.0f, 1.0f, 1.0f } },

				}
			};
			static constexpr std::array<unsigned short, INDEX_SIZE> indices =
			{
				0,1,2,		0,2,3,
				4,5,6,		4,6,7,
				8,9,10,		8,10,11,
				12,13,14,	12,14,15,
				16,17,18,	16,18,19,
				20,21,22,	20,22,23,
			};
		};

		struct Sphere
		{
			MeshData mesh;

			void CreateSphere(float radius, unsigned int sliceCount, unsigned int stackCount)
			{
				mesh.Vertices.clear();
				mesh.Indices.clear();
				Model3DVertex topVertex;
				topVertex.Position = { 0.0f, radius, 0.0f };
				topVertex.Normal = { 0.0f, 1.0f, 0.0f };
				topVertex.UV = { 0.0f, 0.0f };
				topVertex.Color = { 0.0f, 0.0f,0.0f, 0.0f };

				Model3DVertex bottomVertex;
				topVertex.Position = { 0.0f,-radius, 0.0f };
				topVertex.Normal = { 0.0f,-1.0f, 0.0f };
				topVertex.UV = { 0.0f, 1.0f };
				topVertex.Color = { 0.0f, 0.0f,0.0f, 0.0f };
				mesh.Vertices.push_back(topVertex);

				float phiStep = Math::pi<float> / static_cast<float>(stackCount);
				float thetaStep = 2.0f * Math::pi<float>/ static_cast<float>(sliceCount);

				for (unsigned int i = 1; i < stackCount; ++i)
				{
					float phi = i * phiStep;

					for (unsigned int j = 0; j <= sliceCount; ++j)
					{
						float theta = j * thetaStep;

						Model3DVertex v;
						v.Position.x = radius * sinf(phi) * cosf(theta);
						v.Position.y = radius * cosf(phi);
						v.Position.z = radius * sinf(phi) * sinf(theta);

						v.Normal = v.Position.normalize();

						v.UV.x = theta / Math::pi<float>;
						v.UV.y = phi / Math::pi<float>;
						v.Color = { 0.0f, 0.0f,0.0f, 0.0f };
						mesh.Vertices.push_back(v);
					}
				}

				mesh.Vertices.push_back(bottomVertex);


				for (unsigned int i = 1; i <= sliceCount; ++i)
				{
					mesh.Indices.push_back(0);
					mesh.Indices.push_back(i + 1);
					mesh.Indices.push_back(i);
				}

				unsigned int baseIndex = 1;
				unsigned int ringVertexCount = sliceCount + 1;
				for (unsigned int i = 0; i < stackCount - 2; ++i)
				{
					for (unsigned int j = 0; j < sliceCount; ++j)
					{
						mesh.Indices.push_back(baseIndex + i * ringVertexCount + j);
						mesh.Indices.push_back(baseIndex + i * ringVertexCount + j + 1);
						mesh.Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
						mesh.Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
						mesh.Indices.push_back(baseIndex + i * ringVertexCount + j + 1);
						mesh.Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
					}
				}

				unsigned int southPoleIndex = static_cast<unsigned int>(mesh.Vertices.size() - 1);

				baseIndex = southPoleIndex - ringVertexCount;

				for (unsigned int i = 0; i < sliceCount; ++i)
				{
					mesh.Indices.push_back(southPoleIndex);
					mesh.Indices.push_back(baseIndex + i);
					mesh.Indices.push_back(baseIndex + i + 1);
				}
			}
		};
	};
}