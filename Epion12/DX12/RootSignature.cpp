#include "../Epion12.h"
#include "RootSignature.h"
#include "Device.h"
#include "CommandList.h"

namespace epion::DX12
{
	com_ptr<ID3D12RootSignature> RootSignatureManager::m_root_signature;

	void RootSignatureManager::Build()
	{
		D3D12_DESCRIPTOR_RANGE desc_range[3] = {};
		desc_range[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		desc_range[0].NumDescriptors = 1;
		desc_range[0].BaseShaderRegister = 0;
		desc_range[0].RegisterSpace = 0;
		desc_range[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		desc_range[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		desc_range[1].NumDescriptors = 1;
		desc_range[1].BaseShaderRegister = 1;
		desc_range[1].RegisterSpace = 0;
		desc_range[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		desc_range[2].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		desc_range[2].NumDescriptors = 1;
		desc_range[2].BaseShaderRegister = 2;
		desc_range[2].RegisterSpace = 0;
		desc_range[2].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		D3D12_ROOT_PARAMETER root_param[3] = {};
		root_param[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		root_param[0].DescriptorTable.pDescriptorRanges = &desc_range[0];
		root_param[0].DescriptorTable.NumDescriptorRanges = 1;
		root_param[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

		root_param[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		root_param[1].DescriptorTable.pDescriptorRanges = &desc_range[1];
		root_param[1].DescriptorTable.NumDescriptorRanges = 1;
		root_param[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

		root_param[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		root_param[2].DescriptorTable.pDescriptorRanges = &desc_range[2];
		root_param[2].DescriptorTable.NumDescriptorRanges = 1;
		root_param[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

		com_ptr<ID3DBlob> root_sig_blob;
		com_ptr<ID3DBlob> error_blob;
		D3D12_ROOT_SIGNATURE_DESC root_sig_desc = {};

		root_sig_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		root_sig_desc.pParameters = root_param;//ルートパラメータの先頭アドレス
		root_sig_desc.NumParameters = 3;//ルートパラメータ数
		D3D12SerializeRootSignature(&root_sig_desc, D3D_ROOT_SIGNATURE_VERSION_1_0, &root_sig_blob, &error_blob);
		DX12::Device::Get()->CreateRootSignature(0, root_sig_blob->GetBufferPointer(), root_sig_blob->GetBufferSize(), IID_PPV_ARGS(&m_root_signature));

	}

	void RootSignatureManager::SetGraphicsRootSignature()
	{
		DX12::CommandList::GetPtr()->SetGraphicsRootSignature(m_root_signature.Get());
	}

	com_ptr<ID3D12RootSignature>& RootSignatureManager::Get()
	{
		return m_root_signature;
	}

	RootSignature::RootSignature()
	{
	}
	RootSignature::~RootSignature()
	{
	}

	bool RootSignature::Initialize()
	{
		com_ptr<ID3DBlob> root_sig_blob;
		com_ptr<ID3DBlob> error_blob;
		D3D12_ROOT_SIGNATURE_DESC root_sig_desc = {};

		root_sig_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		D3D12SerializeRootSignature(&root_sig_desc, D3D_ROOT_SIGNATURE_VERSION_1_0, &root_sig_blob, &error_blob);
		DX12::Device::Get()->CreateRootSignature(0, root_sig_blob->GetBufferPointer(), root_sig_blob->GetBufferSize(), IID_PPV_ARGS(&m_root_signature));
		return true;

	}
	bool RootSignature::Initialize(D3D12_ROOT_PARAMETER& desc)
	{
		com_ptr<ID3DBlob> root_sig_blob;
		com_ptr<ID3DBlob> error_blob;
		D3D12_ROOT_SIGNATURE_DESC root_sig_desc = {};

		root_sig_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		root_sig_desc.pParameters = &desc;//ルートパラメータの先頭アドレス
		root_sig_desc.NumParameters = 1;//ルートパラメータ数
		D3D12SerializeRootSignature(&root_sig_desc, D3D_ROOT_SIGNATURE_VERSION_1_0, &root_sig_blob, &error_blob);
		DX12::Device::Get()->CreateRootSignature(0, root_sig_blob->GetBufferPointer(), root_sig_blob->GetBufferSize(), IID_PPV_ARGS(&m_root_signature));
		return true;
	}


	com_ptr<ID3D12RootSignature>& RootSignature::Get()
	{
		return m_root_signature;
	}

}