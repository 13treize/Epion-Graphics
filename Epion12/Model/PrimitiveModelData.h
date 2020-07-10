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
	struct PrimitiveData final
	{
		struct Polygon
		{
			static constexpr unsigned int SIZE = 6;
			static constexpr std::array<unsigned short, SIZE> indices = { 0,1,2, 2,1,3 };
		};
	};
}