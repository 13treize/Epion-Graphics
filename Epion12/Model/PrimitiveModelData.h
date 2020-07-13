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


	struct PrimitiveData final
	{
		struct Polygon
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

		struct CubeMesh
		{
			static constexpr unsigned int VERTEX_SIZE = 24;
			static constexpr unsigned int INDEX_SIZE = 36;
			static constexpr std::array<Model3DVertex, VERTEX_SIZE>  vertices =
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
	};
}