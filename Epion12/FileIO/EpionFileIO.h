#pragma once
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/polymorphic.hpp>

namespace epion::FileIO
{
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

	class FileIOManager final
	{
	public:
		template<class T>
		static void InputJson(std::string_view file, std::string_view name, T& data);
		template<class T>
		static void OutputJson(std::string_view file, std::string_view name, T& data);
		template<class T, class U>
		static void OutputJson(std::string_view file, std::string_view name, T& data, std::string_view name2, U& data2);
		template<class T, class U>
		static void OutputJson(std::string_view file, std::string_view name, std::vector<T>& data, std::string_view name2, std::list<U>& data2);
		template<class T, class U>
		static void OutputJson(std::string_view file, std::string_view name, const std::vector<std::unique_ptr<T>>& data, std::string_view name2,const std::vector<U>& data2);
		template<class T, class U>
		static void OutputJson(std::string_view file, std::string_view name, std::vector<std::unique_ptr<T>>& data, std::string_view name2, std::list<U>& data2);

	private:
		template<class T>
		static void InputData(std::string_view name, cereal::JSONInputArchive& archive, T& data);
		template<class T>
		static void OutputData(std::string_view name, cereal::JSONOutputArchive& archive, T& data);
		template<class T>
		static void OutputData(std::string_view name, cereal::JSONOutputArchive& archive, const std::vector<T>& data);
		template<class T>
		static void OutputData(std::string_view name, cereal::JSONOutputArchive& archive, const std::vector<std::unique_ptr<T>>& data);
		template<class T>
		static void OutputData(std::string_view name, cereal::JSONOutputArchive& archive, std::list<T>& data);

	};

	template<class T>
	static void FileIOManager::InputJson(std::string_view file, std::string_view name, T& data)
	{
		std::ifstream	ifs(file, std::ios::in);
		std::stringstream	stream;
		stream << ifs.rdbuf();
		cereal::JSONInputArchive	i_archive(stream);
		InputData<T>(name.data(), i_archive, data);
		ifs.close();
	}

	template<class T>
	static void FileIOManager::OutputJson(std::string_view file, std::string_view name, T& data)
	{
		std::ofstream	ofs(file);
		std::stringstream	stream;
		{
			cereal::JSONOutputArchive	o_archive(stream);
			OutputData<T>(name, o_archive, data);
		}
		ofs << stream.str();
		ofs.close();
	}
	template<class T, class U>
	static void FileIOManager::OutputJson(std::string_view file, std::string_view name, T& data, std::string_view name2, U& data2)
	{
		std::ofstream	ofs(file);
		std::stringstream	stream;
		{
			cereal::JSONOutputArchive	o_archive(stream);
			OutputData<T>(name, o_archive, data);
			OutputData<U>(name2, o_archive, data2);
		}
		ofs << stream.str();
		ofs.close();
	}
	template<class T, class U>
	static void FileIOManager::OutputJson(std::string_view file, std::string_view name, std::vector<T>& data, std::string_view name2, std::list<U>& data2)
	{
		std::ofstream	ofs(file);
		std::stringstream	stream;
		{
			cereal::JSONOutputArchive	o_archive(stream);
			OutputData<T>(name, o_archive, data);
			OutputData<U>(name2, o_archive, data2);
		}
		ofs << stream.str();
		ofs.close();
	}
	template<class T, class U>
	static void FileIOManager::OutputJson(std::string_view file, std::string_view name, const std::vector<std::unique_ptr<T>>& data, std::string_view name2, const std::vector<U>& data2)
	{
		std::ofstream	ofs(file);
		std::stringstream	stream;
		{
			cereal::JSONOutputArchive	o_archive(stream);
			OutputData<T>(name.data(), o_archive, data);
			OutputData<U>(name2.data(), o_archive, data2);
		}
		ofs << stream.str();
		ofs.close();
	}
	template<class T, class U>
	static void FileIOManager::OutputJson(std::string_view file, std::string_view name, std::vector<std::unique_ptr<T>>& data, std::string_view name2, std::list<U>& data2)
	{
		std::ofstream	ofs(file);
		std::stringstream	stream;
		{
			cereal::JSONOutputArchive	o_archive(stream);
			OutputData<T>(name.data(), o_archive, data);
			OutputData<U>(name2.data(), o_archive, data2);
		}
		ofs << stream.str();
		ofs.close();
	}
	template<class T>
	static void FileIOManager::InputData(std::string_view name, cereal::JSONInputArchive& archive, T& data)
	{
		archive(cereal::make_nvp(name.data(), data));
	}

	template<class T>
	static void FileIOManager::OutputData(std::string_view name, cereal::JSONOutputArchive& archive, T& data)
	{
		archive(cereal::make_nvp(name.data(), data));
	}
	template<class T>
	static void FileIOManager::OutputData(std::string_view name, cereal::JSONOutputArchive& archive, const std::vector<T>& data)
	{
		archive(cereal::make_nvp(name.data(), data));
	}
	template<class T>
	static void FileIOManager::OutputData(std::string_view name, cereal::JSONOutputArchive& archive, const std::vector<std::unique_ptr<T>>& data)
	{
		archive(cereal::make_nvp(name.data(), data));
	}
	template<class T>
	static void FileIOManager::OutputData(std::string_view name, cereal::JSONOutputArchive& archive, std::list<T>& data)
	{
		archive(cereal::make_nvp(name.data(), data));
	}


}