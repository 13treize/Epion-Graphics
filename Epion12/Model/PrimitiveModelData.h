#pragma once
namespace epion::Model
{
	struct Model3DVertex
	{
		epion::Math::FVector3 Position;
		epion::Math::FVector3 Normal;
		epion::Math::FVector2 UV;
		epion::Math::FVector4 Color;
	};
	struct PrimitiveData final
	{
		struct Polygon
		{
			static constexpr std::array<unsigned short, 6> indices = { 0,1,2, 2,1,3 };
		};
	};
}