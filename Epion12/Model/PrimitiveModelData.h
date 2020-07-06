#pragma once
namespace epion::Model
{
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
			static constexpr std::array<unsigned short, 6> indices = { 0,1,2, 2,1,3 };
		};
	};
}