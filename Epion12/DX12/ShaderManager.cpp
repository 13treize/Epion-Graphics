#include "../Epion12.h"
#include "ShaderManager.h"

//VS > HS > DS > GS > PS
namespace	epion::DX12
{
	bool ShaderCompile(const std::wstring& hlsl_name,
		const std::string& entry_point,
		const std::string& target,
		com_ptr<ID3DBlob>& shader_blob)
	{
		HRESULT	hr = S_OK;

		unsigned	int	flags = D3DCOMPILE_SKIP_OPTIMIZATION;
#ifdef	_DEBUG
		flags |= D3DCOMPILE_DEBUG;
#endif
		com_ptr<ID3DBlob>	error_blob = {};

		hr = D3DCompileFromFile(hlsl_name.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entry_point.c_str(),
			target.c_str(),
			flags,
			0,
			shader_blob.ReleaseAndGetAddressOf(),
			error_blob.GetAddressOf());

		if (FAILED(hr))
		{
			return	false;
		}
		if (error_blob)
		{
			return	false;
		}
		return	true;
	}


	bool ShaderResouceManager::Initialize()
	{
		return true;
	}
	bool ShaderResouceManager::Finalize()
	{
		return true;
	}

	bool ShaderResouceManager::Settings()
	{

		return true;
	}

	bool ShaderResouceManager::Compile(const std::wstring& hlsl_name, com_ptr<ID3DBlob>& shader_blob, ShaderType type)
	{
		switch (type)
		{
		case ShaderType::TYPE_VERTEX:	if (ShaderCompile(hlsl_name, "VS", "vs_5_1", shader_blob))	return true;	break;
		case ShaderType::TYPE_HULL:		if (ShaderCompile(hlsl_name, "HS", "hs_5_1", shader_blob))	return true;	break;
		case ShaderType::TYPE_DOMAIN:	if (ShaderCompile(hlsl_name, "DS", "ds_5_1", shader_blob))	return true;	break;
		case ShaderType::TYPE_GEOMETRY:	if (ShaderCompile(hlsl_name, "GS", "gs_5_1", shader_blob))	return true;	break;
		case ShaderType::TYPE_PIXEL:	if (ShaderCompile(hlsl_name, "PS", "ps_5_1", shader_blob))	return true;	break;
		default:	break;
		}
		return false;
	}
	bool ShaderResouceManager::Compile(const std::wstring& hlsl_name, const std::string& entry_point, com_ptr<ID3DBlob>& shader_blob, ShaderType type)
	{
		switch (type)
		{
		case ShaderType::TYPE_VERTEX:	if (ShaderCompile(hlsl_name, entry_point, "vs_5_1", shader_blob))	return true;	break;
		case ShaderType::TYPE_HULL:		if (ShaderCompile(hlsl_name, entry_point, "hs_5_1", shader_blob))	return true;	break;
		case ShaderType::TYPE_DOMAIN:	if (ShaderCompile(hlsl_name, entry_point, "ds_5_1", shader_blob))	return true;	break;
		case ShaderType::TYPE_GEOMETRY:	if (ShaderCompile(hlsl_name, entry_point, "gs_5_1", shader_blob))	return true;	break;
		case ShaderType::TYPE_PIXEL:	if (ShaderCompile(hlsl_name, entry_point, "ps_5_1", shader_blob))	return true;	break;
		default:	break;
		}
		return false;
	}




	void	ShaderReflection::ReflectionInputLayout(com_ptr<ID3DBlob>& shader_blob)
	{
		HRESULT	hr = S_OK;
		std::vector<D3D12_INPUT_ELEMENT_DESC>	layout = {};

		hr = D3DReflect(shader_blob->GetBufferPointer(),
			shader_blob->GetBufferSize(),
			IID_ID3D12ShaderReflection,
			(void**)m_reflection.ReleaseAndGetAddressOf());

		D3D12_SHADER_DESC	shaderdesc = {};
		m_reflection->GetDesc(&shaderdesc);

		for (unsigned int i = 0; i < shaderdesc.InputParameters; i++)
		{
			D3D12_SIGNATURE_PARAMETER_DESC signaturePrameterDesc = {};
			m_reflection->GetInputParameterDesc(i, &signaturePrameterDesc);

			D3D12_INPUT_ELEMENT_DESC	element_desc = {};
			element_desc.SemanticName = signaturePrameterDesc.SemanticName;
			element_desc.SemanticIndex = signaturePrameterDesc.SemanticIndex;
			element_desc.Format = GetDXGIFormat(signaturePrameterDesc.ComponentType, signaturePrameterDesc.Mask);
			element_desc.InputSlot = GetVertexBufferSlot(signaturePrameterDesc.SemanticName);
			element_desc.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
			element_desc.InputSlotClass = D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
			element_desc.InstanceDataStepRate = 0;

			m_layout.emplace_back(element_desc);
		}
		//return m_layout;
	}
	std::vector<D3D12_INPUT_ELEMENT_DESC>& ShaderReflection::GetInputLayout()
	{
		return m_layout;
	}

	const DXGI_FORMAT ShaderReflection::GetDXGIFormat(const D3D_REGISTER_COMPONENT_TYPE type, const byte mask)
	{
		switch (mask)
		{
		case 0xF:
			switch (type)
			{
			case D3D10_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
			case D3D10_REGISTER_COMPONENT_SINT32:	return DXGI_FORMAT_R32G32B32A32_SINT;
			case D3D10_REGISTER_COMPONENT_UINT32:	return DXGI_FORMAT_R32G32B32A32_UINT;
			case D3D10_REGISTER_COMPONENT_UNKNOWN:	return DXGI_FORMAT_UNKNOWN;
			}
		case 0x7:
			switch (type)
			{
			case D3D10_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32G32B32_FLOAT;
			case D3D10_REGISTER_COMPONENT_SINT32:	return DXGI_FORMAT_R32G32B32_SINT;
			case D3D10_REGISTER_COMPONENT_UINT32:	return DXGI_FORMAT_R32G32B32_UINT;
			case D3D10_REGISTER_COMPONENT_UNKNOWN:	return DXGI_FORMAT_UNKNOWN;
			}
		case 0x3:
			switch (type)
			{
			case D3D10_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32G32_FLOAT;
			case D3D10_REGISTER_COMPONENT_SINT32:	return DXGI_FORMAT_R32G32_SINT;
			case D3D10_REGISTER_COMPONENT_UINT32:	return DXGI_FORMAT_R32G32_UINT;
			case D3D10_REGISTER_COMPONENT_UNKNOWN:	return	DXGI_FORMAT_UNKNOWN;
			}
		case 0x1:
			switch (type)
			{
			case D3D10_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32_FLOAT;
			case D3D10_REGISTER_COMPONENT_SINT32:	return DXGI_FORMAT_R32_SINT;
			case D3D10_REGISTER_COMPONENT_UINT32:	return DXGI_FORMAT_R32_UINT;
			case D3D10_REGISTER_COMPONENT_UNKNOWN:	return DXGI_FORMAT_UNKNOWN;
			}
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}
	const unsigned int	ShaderReflection::GetVertexBufferSlot(const std::string& semantic_name)
	{
		int slot = 0;
		int under_score_num = 0;
		int digit = 0;

		// 先頭がアンダースコアでない場合スロット指定がないものとしてスロット0
		if (semantic_name[0] != '_') return slot;

		int nameSize = static_cast<int>(semantic_name.size());
		for (int i = 0; i < nameSize; i++)
		{
			// 2つ目のアンダースコアを確認する
			if (under_score_num >= 2) break;

			// アンダースコアかどうか
			if (semantic_name[i] == '_')
			{
				under_score_num++;
				continue;
			}

			// 数字かどうか
			if (semantic_name[i] >= '0' && semantic_name[i] <= '9')
			{
				slot *= 10;
				slot += semantic_name[i] - '0';
			}
		}

		return slot;
	}
}