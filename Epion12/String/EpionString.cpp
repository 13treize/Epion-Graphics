#include	"../Epion12.h"

namespace
{
}

namespace	epion::String
{
	//char → wchar_t
	void	StringConverter::ToWchar(const char* str, wchar_t* ret, unsigned int	max_size)
	{
		::setlocale(LC_CTYPE, "jpn");
		size_t	s = 256;
		mbstowcs_s(&s, ret, max_size, str, _TRUNCATE);
	}

	//wchar_t → char
	void	StringConverter::ToChar(const wchar_t* str, char* ret, unsigned int	max_size)
	{
		::setlocale(LC_CTYPE, "jpn");
		size_t	s = 256;
		wcstombs_s(&s, ret, max_size, str, _TRUNCATE);
	}

	//string → wstring
	std::wstring	StringConverter::ToWstring(std::string_view str)
	{
		std::filesystem::path	get_str = str;
		return	get_str.wstring();
	}

	//wstring → string
	void	StringConverter::ToString(const std::wstring& str, std::string ret, unsigned int	max_size)
	{
		const	wchar_t* get_str = str.c_str();
		char				get_ret[256] = {};
		ToChar(get_str, get_ret, max_size);
		ret = get_ret;
	}

	//	引数からファイルパスを取得
	std::string	StringConverter::GetFilePath(const std::string& file_name)
	{
		std::filesystem::path	file_path = file_name;
		file_path.remove_filename();
		return	file_path.string();
	}

	std::wstring	StringConverter::GetFilePath(const std::wstring& file_name)
	{
		std::filesystem::path	file_path = file_name;
		file_path.remove_filename();
		return	file_path.wstring();
	}


	[[nodiscard]] std::wstring	StringConverter::SetFilePath(const	wchar_t* add_path_filename,	const	wchar_t* resource_filename)
	{
		std::filesystem::path	file_path = resource_filename;
		file_path.remove_filename();
		std::wstring	convert_file = file_path.wstring() + add_path_filename;
		return	convert_file;
	}

	//	引数の拡張子を取得
	std::string	StringConverter::GetExtension(const std::string& str_)
	{
		std::filesystem::path	file_extension = str_;
		auto	ext_str = file_extension.extension();
		return	ext_str.string();
	}

	std::string	StringConverter::ToString2(Math::FVector2& vec2, const std::string& str)
	{
		return	std::to_string(vec2.x) + str + std::to_string(vec2.y);
	}

	std::string	StringConverter::ToString2(float x, float y, const std::string& str)
	{
		return	std::to_string(x) + str + std::to_string(y);
	}

	std::string	StringConverter::ToString3(Math::FVector3& vec3, const std::string& str)
	{
		return	std::to_string(vec3.x) + str + std::to_string(vec3.y) + str + std::to_string(vec3.z);
	}

	std::string	StringConverter::ToString3(float x, float y, float z, const std::string& str)
	{
		return	std::to_string(x) + str + std::to_string(y) + str + std::to_string(z);
	}

	std::string	StringConverter::ToString4(Math::FVector4& vec4, const std::string&	str)
	{
		return	std::to_string(vec4.x) + str + std::to_string(vec4.y) + str + std::to_string(vec4.z) + str + std::to_string(vec4.w);
	}
	std::string	StringConverter::ToString4(float x, float y, float z, float w, const std::string&	str)
	{
		return	std::to_string(x) + str + std::to_string(y) + str + std::to_string(z) + str + std::to_string(w);
	}


	std::string	StringConverter::GetSpace(int num)
	{
		std::string		ret_str = "";
		for (int i = 0; i < num; i++)
		{
			ret_str += " ";
		}
		return ret_str;
	}

}

