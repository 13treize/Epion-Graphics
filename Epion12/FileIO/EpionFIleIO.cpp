#include "../Epion12.h"
#include "EpionFileIO.h"

namespace epion::FileIO
{
	void EpionFileIO::Input(std::string_view file)
	{
		std::ifstream	ifs(file, std::ios::in);
		std::stringstream	stream;
	}
}