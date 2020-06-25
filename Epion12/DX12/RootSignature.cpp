#include "../Epion12.h"
#include "RootSignature.h"
#include "Device.h"
#include "CommandList.h"

namespace epion::DX12
{
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