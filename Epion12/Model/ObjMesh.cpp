#include "../Epion12.h"
#include "ObjMesh.h"
#include "ObjLoader.h"

#include "../DX12/ViewPort.h"
#include "../DX12/Device.h"
#include "../DX12/CommandList.h"

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

		std::vector<Math::FVector4>	positions;
		std::vector<Math::FVector4>	normals;
		std::vector<Math::FVector2>	uvs;

		std::wstring	file_path = String::StringConverter::GetFilePath(file_name);


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
		mtl_filenames[0] = String::StringConverter::SetFilePath(mtl_filenames[0].c_str(), file_name.c_str());
	}

	ObjMesh::ObjMesh()
		:Model()
	{
		m_pipeline_state = nullptr;
		m_pipeline_desc = {};
	}


	ObjMesh::~ObjMesh()
	{
	}
	bool ObjMesh::Initialize(const std::wstring& file_name,com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
		m_is_update = true;

		m_obj_loader = std::make_unique<ObjLoader>();
		m_obj_loader->Load(file_name);

		m_vertex->Initialize(sizeof(ObjVertex), sizeof(ObjVertex) * 4);


		m_index->Initialize(sizeof(unsigned	int) * m_obj_loader->indices.size());

		unsigned short* mappedIdx = nullptr;
		m_index->GetBuffer()->Map(0, nullptr, (void**)&mappedIdx);
		//std::copy(std::begin(indices), std::end(indices), mappedIdx);
		m_index->GetBuffer()->Unmap(0, nullptr);


		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);


		m_pipeline_desc = {};
		m_pipeline_desc.pRootSignature = nullptr;
		m_pipeline_desc.VS.pShaderBytecode = vs_blob->GetBufferPointer();
		m_pipeline_desc.VS.BytecodeLength = vs_blob->GetBufferSize();
		m_pipeline_desc.PS.pShaderBytecode = ps_blob->GetBufferPointer();
		m_pipeline_desc.PS.BytecodeLength = ps_blob->GetBufferSize();

		m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;//中身は0xffffffff

		m_pipeline_desc.BlendState.AlphaToCoverageEnable = false;
		m_pipeline_desc.BlendState.IndependentBlendEnable = false;



		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {};

		//ひとまず加算や乗算やαブレンディングは使用しない
		renderTargetBlendDesc.BlendEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		//ひとまず論理演算は使用しない
		renderTargetBlendDesc.LogicOpEnable = false;

		m_pipeline_desc.BlendState.RenderTarget[0] = renderTargetBlendDesc;

		m_pipeline_desc.RasterizerState = r_desc;

		m_pipeline_desc.DepthStencilState.DepthEnable = false;
		m_pipeline_desc.DepthStencilState.StencilEnable = false;

		m_pipeline_desc.InputLayout.pInputElementDescs = m_shader_reflection->GetInputLayout().data();//レイアウト先頭アドレス
		m_pipeline_desc.InputLayout.NumElements = m_shader_reflection->GetInputLayout().size();//レイアウト配列数

		m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;//ストリップ時のカットなし
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;//三角形で構成

		m_pipeline_desc.NumRenderTargets = 1;//今は１つのみ
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//0～1に正規化されたRGBA

		m_pipeline_desc.SampleDesc.Count = 1;//サンプリングは1ピクセルにつき１
		m_pipeline_desc.SampleDesc.Quality = 0;//クオリティは最低

		m_pipeline_desc.pRootSignature = root_sig.Get();
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));

		return true;
	}
	bool ObjMesh::Finalize()
	{
		return true;
	}

	void ObjMesh::Render()
	{
		DX12::CommandList::GetPtr()->SetPipelineState(m_pipeline_state.Get());
		DX12::CommandList::GetPtr()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DX12::CommandList::GetPtr()->IASetVertexBuffers(0, 1, &m_vertex->GetView());
		DX12::CommandList::GetPtr()->IASetIndexBuffer(&m_index->GetView());
		for (auto& material : m_obj_loader->materials)
		{
			for (Subset& subset : m_obj_loader->subsets)
			{
				if (material.newmtl == subset.usemtl)
				{
					DX12::CommandList::GetPtr()->DrawIndexedInstanced(subset.index_count, subset.index_start,0,0,0);
				}
			}
		}
	}

}