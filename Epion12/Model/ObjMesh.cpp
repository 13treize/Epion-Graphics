#include "../Epion12.h"
#include "ObjMesh.h"
#include "ObjLoader.h"

#include "../DX12/ViewPort.h"
#include "../DX12/Device.h"
#include "../DX12/CommandList.h"
#include "../DX12/ConstantBufferManager.h"

namespace
{
}
#undef	min
#undef	max

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

		std::vector<Math::FVector3>	positions;
		std::vector<Math::FVector3>	normals;
		std::vector<Math::FVector2>	uvs;
		std::vector<Math::FVector4>	color;

		std::wstring	file_path = String::StringConverter::GetFilePath(file_name);


		while (fin)
		{
			fin >> command;	//ˆê•¶Žš‚¸‚Â‚Ì“Ç‚Ýž‚Ý‚Í’x‚¢‚ç‚µ‚¢

			if (command == L"v")
			{
				float	x, y, z;
				fin >> x >> y >> z;

				positions.push_back(Math::FVector3(x, y, z));
				fin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//“Ç‚ÝŽÌ‚Ä‚é
			}
			else	if (command == L"vt")
			{
				float u, v;
				fin >> u >> v;
				uvs.push_back(Math::FVector2(u, flipping_v_coordinates ? 1.0f - v : v));
				fin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//“Ç‚ÝŽÌ‚Ä‚é
			}
			else	if (command == L"vn")
			{
				float	i, j, k;
				fin >> i >> j >> k;
				normals.push_back(Math::FVector3(i, j, k));
				fin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//“Ç‚ÝŽÌ‚Ä‚é
			}
			else	if (command == L"f")
			{
				for (unsigned int i = 0; i < 3; i++)
				{
					Model3DVertex	vertex;
					unsigned int	v, vt, vn;

					fin >> v;
					vertex.Position = positions[v - 1];
					if (L'/' == fin.peek())
					{
						fin.ignore();
						if (L'/' != fin.peek())
						{
							fin >> vt;
							vertex.UV = uvs[vt - 1];
						}
						if (L'/' == fin.peek())
						{
							fin.ignore();
							fin >> vn;
							vertex.Normal = normals[vn - 1];
						}
					}
					vertices.push_back(vertex);
					indices.push_back(index++);
				}
				fin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//“Ç‚ÝŽÌ‚Ä‚é
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
				fin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//“Ç‚ÝŽÌ‚Ä‚é
			}
		}
		fin.close();

		//auto	iterator_ = subsets.rbegin();
		//iterator_->index_count = static_cast<unsigned int>(indices.size() - iterator_->index_start);
		//for (iterator_ = subsets.rbegin() + 1; iterator_ != subsets.rend(); ++iterator_)
		//{
		//	iterator_->index_count = (iterator_ - 1)->index_start - iterator_->index_start;
		//}
		for (auto& vert : vertices)
		{
			vert.Color =Math::FVector4(0.0f,0.0f, 0.0f, 0.0f);
		}
		mtl_filenames[0] = String::StringConverter::SetFilePath(mtl_filenames[0].c_str(), file_name.c_str());
	}

	ObjMesh::ObjMesh()
		:Model3D()
	{
		m_pipeline_state = nullptr;
		m_pipeline_desc = {};
	}


	ObjMesh::~ObjMesh()
	{
	}
	bool ObjMesh::Initialize(const std::wstring& file_name, com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, D3D12_BLEND_DESC& b_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);

		m_pipeline_desc = {};
		m_pipeline_desc.VS = { vs_blob->GetBufferPointer(), vs_blob->GetBufferSize() };
		m_pipeline_desc.PS = { ps_blob->GetBufferPointer(), ps_blob->GetBufferSize() };

		m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

		m_pipeline_desc.BlendState = b_desc;
		m_pipeline_desc.RasterizerState = r_desc;

		m_pipeline_desc.DepthStencilState.DepthEnable = false;
		m_pipeline_desc.DepthStencilState.StencilEnable = false;

		m_pipeline_desc.InputLayout = { m_shader_reflection->GetInputLayout().data(), static_cast<UINT>(m_shader_reflection->GetInputLayout().size()) };

		m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		m_pipeline_desc.NumRenderTargets = 1;
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		m_pipeline_desc.SampleDesc = { 1,0 };

		m_pipeline_desc.pRootSignature = root_sig.Get();
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));

		m_obj_loader = std::make_unique<ObjLoader>();
		m_obj_loader->Load(file_name);
		
		vertex_size = m_obj_loader->vertices.size();
		m_vertex_resource = std::make_unique<DX12::ResourceBuffer<Model3DVertex>>();
		m_vertex_resource->Initialize(DX12::Device::Get(), sizeof(Model3DVertex), false);
		m_vertex_resource->CopyResource(m_obj_loader->vertices);
		m_vertex_buffer_view = { m_vertex_resource->GetGPUVirtualAddress() ,static_cast<UINT>(sizeof(Model3DVertex) * vertex_size),sizeof(Model3DVertex) };

		index_size = m_obj_loader->indices.size();
		m_index_resource = std::make_unique<DX12::ResourceBuffer<unsigned short>>();
		m_index_resource->Initialize(DX12::Device::Get(), index_size, false);
		m_index_resource->CopyResource(m_obj_loader->indices);
		m_index_buffer_view = { m_index_resource->GetGPUVirtualAddress(), static_cast<UINT>(sizeof(unsigned short)*index_size),DXGI_FORMAT::DXGI_FORMAT_R16_UINT };

		return true;
	}
	bool ObjMesh::Finalize()
	{
		return true;
	}

	void ObjMesh::Update()
	{
		DirectX::XMMATRIX S, R, T;
		S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
		R = DirectX::XMMatrixRotationRollPitchYaw(m_angle.x * 0.01745f, m_angle.y * 0.01745f, m_angle.z * 0.01745f);
		T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
		m_world_matrix = S * R * T;
	}

	void ObjMesh::Render()
	{
		DX12::CommandList::GetCmd()->SetPipelineState(m_pipeline_state.Get());
		DX12::CommandList::GetCmd()->IASetVertexBuffers(0, 1, &m_vertex_buffer_view);
		DX12::CommandList::GetCmd()->IASetIndexBuffer(&m_index_buffer_view);
		DX12::CommandList::GetCmd()->DrawIndexedInstanced(m_index_resource->GetCount(),1, 0, 0, 0);

		//for (auto& material : m_obj_loader->materials)
		//{
		//	for (Subset& subset : m_obj_loader->subsets)
		//	{
		//		if (material.newmtl == subset.usemtl)
		//		{
		//			DX12::CommandList::GetCmd()->DrawIndexedInstanced(subset.index_count, subset.index_start,0,0,0);
		//		}
		//	}
		//}
	}

}