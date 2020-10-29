#include "../Epion12.h"
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/polymorphic.hpp>

#include "EpionFileIO.h"

namespace epion::FileIO
{
	void Input(std::string_view file)
	{
		std::ifstream	ifs(file, std::ios::in);
		std::stringstream	stream;
	}

	void InputJson(std::string_view file, std::string_view name, std::vector<std::string>& data)
	{
		std::ifstream	ifs(file, std::ios::in);
		std::stringstream	stream;
		stream << ifs.rdbuf();
		cereal::JSONInputArchive	i_archive(stream);

		i_archive(cereal::make_nvp(name.data(), data));

		ifs.close();
	}

}