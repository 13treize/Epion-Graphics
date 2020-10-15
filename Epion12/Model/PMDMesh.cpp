#include "../Epion12.h"
#include "../DX12/Buffer.h"
#include "PMDMesh.h"

namespace epion::Model
{
	PMDMesh::PMDMesh(std::string_view filepath)
	{
		std::ifstream	ifs("Epion12/Assets/Model/初音ミク.pmd", std::ios::in);
		//ifs.open("Epion12/Assets/Model/初音ミク.pmd", std::ios::in);
		//std::ifstream	ifs("Epion12/Assets/Model/初音ミク.pmd", std::ios::in);
		//std::stringstream	stream;
		//stream << ifs.rdbuf();
		//std::string signature = stream.str();

		//std::ifstream	ifs("Epion12/Assets/Model/初音ミク.pmd", std::ios::in);

		//PMDHeader h;
		//std::string buffer;
		//ifs.read(buffer.data(), 20);
		//h.name = buffer;
		//ifs.read(buffer.data(), 256);
		//h.comment = buffer;

		float d;

	}

}