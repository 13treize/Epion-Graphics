#include "../Epion12.h"
#include "ObjLoader.h"

namespace epion::Model
{
	ObjLoader::ObjLoader()
	{
	}
	ObjLoader::~ObjLoader()
	{
	}
	void	ObjLoader::Load(const std::wstring& file_name, bool	flipping_v_coordinates)
	{
		std::wifstream	fin(file_name);
		std::wstring	command;

		unsigned	int			index = 0;

		std::vector<Math::FVector4>	positions;
		std::vector<Math::FVector4>	normals;
		std::vector<Math::FVector2>	uvs;

		std::wstring	file_path = StringConverter::get_file_path(file_name_);


		while (fin)
		{
			fin >> command;	//一文字ずつの読み込みは遅いらしい

			if (command == L"v")
			{
				float	x, y, z;
				fin >> x >> y >> z;

				positions.push_back(Math::FVector4(x, y, z, 1.0f));
				fin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//読み捨てる
			}
			else	if (command == L"vt")
			{
				float u, v;
				fin >> u >> v;
				uvs.push_back(Math::FVector2(u, flipping_v_coordinates ? 1.0f - v : v));
				fin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//読み捨てる
			}
			else	if (command == L"vn")
			{
				float	i, j, k;
				fin >> i >> j >> k;
				normals.push_back(Math::FVector4(i, j, k, 0));
				fin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//読み捨てる
			}
			else	if (command == L"f")
			{
				for (unsigned int i = 0; i < 3; i++)
				{
					ObjVertex	vertex;
					unsigned int	v, vt, vn;

					fin >> v;
					vertex.position = positions[v - 1];
					if (L'/' == fin.peek())
					{
						fin.ignore();
						if (L'/' != fin.peek())
						{
							fin >> vt;
							vertex.uv = uvs[vt - 1];
						}
						if (L'/' == fin.peek())
						{
							fin.ignore();
							fin >> vn;
							vertex.normal = normals[vn - 1];
						}
					}
					vertices.push_back(vertex);
					indices.push_back(index++);
				}
				fin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//読み捨てる
			}
			else	if (command == L"mtllib")
			{
				wchar_t	mtllib[256];
				fin >> mtllib;
				mtl_filenames.push_back(mtllib);
			}
			else	if (command == L"usemtl")
			{
				wchar_t	usemtl[MAX_PATH] = { 0 };
				fin >> usemtl;

				Subset	current_subset = {};
				current_subset.usemtl = usemtl;
				current_subset.index_start = static_cast<unsigned int>(indices.size());
				subsets.push_back(current_subset);
			}
			else
			{
				fin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//読み捨てる
			}
		}
		fin.close();
		//コピピペ

		auto	iterator_ = subsets.rbegin();
		iterator_->index_count = static_cast<unsigned int>(indices.size() - iterator_->index_start);
		for (iterator_ = subsets.rbegin() + 1; iterator_ != subsets.rend(); ++iterator_)
		{
			iterator_->index_count = (iterator_ - 1)->index_start - iterator_->index_start;
		}
		mtl_filenames[0] = set_file_path(mtl_filenames[0].c_str(), file_name_.c_str());

	}

}