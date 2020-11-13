#pragma once
/**
 * @file EpionString.h
 * @brief �����񑀍�
 * @author treize
 * @date 2020/06/25
 * @details ��{�I�ɂ͓��{�ꂪ����̃N�\
 */

namespace	epion::String
{
	class	StringConverter
	{
	public:
		//char �� wchar_t
		static	void ToWchar(const char* str, wchar_t* ret, unsigned int	max_size = 256);

		//wchar_t �� char
		static void ToChar(const wchar_t* str, char* ret, unsigned int	max_size = 256);

		//string �� wstring
		static	std::wstring	ToWstring(const std::string& str);

		//wstring �� string
		static void ToString(const std::wstring& str, std::string ret, unsigned int	max_size = 256);

		//	��������t�@�C���p�X���擾
		static	std::string		GetFilePath(const std::string& file_name);
		static	std::wstring	GetFilePath(const std::wstring& file_name);


		//	�����̊g���q���擾
		static	std::string	GetExtension(const std::string& str_);

		//std::to_string FVector2
		static	std::string		ToString2(Math::FVector2& vec2, const std::string& str = ",");
		static	std::string		ToString2(float x, float y, const std::string& str = ",");

		static	std::string		ToString3(Math::FVector3& vec3, const std::string& str = ",");
		static	std::string		ToString3(float x, float y, float z, const std::string& str = ",");

		//std::to_string FVector4
		static	std::string		ToString4(Math::FVector4& vec4, const std::string& str = ",");
		static	std::string		ToString4(float x, float y, float z, float w, const std::string& str = ",");

		static	std::string	GetSpace(int num);

		[[nodiscard]] static std::wstring	SetFilePath(const	wchar_t* add_path_filename,	const	wchar_t* resource_filename);
	};
}

