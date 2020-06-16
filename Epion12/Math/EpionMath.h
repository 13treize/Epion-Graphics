#pragma	once
//#include	"cereal/cereal.hpp"

#include	"EpionVector2.h"
#include	"EpionVector3.h"
#include	"EpionVector4.h"

#include	"EpionRandom.h"

namespace	epion::Math
{
	template	<class	T>
	constexpr	T	pi = static_cast<T>(3.14159265358979323846);

	using	FVector2 = Vector2<float>;
	using	FVector3 = Vector3<float>;
	using	FVector4 = Vector4<float>;


}

#include	"EpionMatrix.h"
