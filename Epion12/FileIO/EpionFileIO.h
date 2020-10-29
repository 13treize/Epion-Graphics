#pragma once

namespace epion::FileIO
{
	void Input(std::string_view file);
	void InputJson(std::string_view file, std::string_view name, std::vector<std::string>& data);

	template<class T>
		void InputJson(std::string_view file, std::string_view name, T& data)
	{
		std::ifstream	ifs(file, std::ios::in);
		std::stringstream	stream;
		stream << ifs.rdbuf();
		cereal::JSONInputArchive	i_archive(stream);
		i_archive(cereal::make_nvp(name.data(), data));
		ifs.close();
	}

}