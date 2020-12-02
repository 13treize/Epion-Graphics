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
		InputData<T>(name.data(),i_archive, data);
		//i_archive(cereal::make_nvp(name.data(), data));
		ifs.close();
	}

	//template <class... Args>
	//void OutputJson(std::string_view file)
	//{
	//	std::ofstream		ofs(path);
	//	std::stringstream	stream;


	//	{
	//		cereal::JSONOutputArchive	o_archive(stream);
	//		//o_archive(cereal::make_nvp("node_param", output_node_data.nodes));

	//		o_archive(cereal::make_nvp("node_param", node_base));
	//		o_archive(cereal::make_nvp("link_param", node_link));
	//	}
	//	ofs << stream.str();
	//	ofs.close();
	//}
	template<class T>
	void InputData(std::string_view name, cereal::JSONInputArchive& archive, T& data)
	{
		archive(cereal::make_nvp(name.data(), data));
	}

	//template<class T>
	//void Output(std::string_view name,const std::vector<T>& data)
	//{
	//	o_archive(cereal::make_nvp(name.data(), data));
	//}


	class FileIOManager final
	{
	public:

	private:

	};
}