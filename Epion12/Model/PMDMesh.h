#pragma once
#include"Model.h"

namespace epion::Model
{
	struct PMDHeader
	{
		float version;
		std::string name;
		std::string comment;
	};

	class PMDMesh final :public Model3D
	{
	public:
		PMDMesh(std::string_view filepath);

	private:
	};
}