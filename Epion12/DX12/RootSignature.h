#pragma once
namespace epion::DX12
{
	class RootSignature final
	{
	public:
		RootSignature();
		~RootSignature();

		bool Initialize(D3D12_ROOT_PARAMETER& desc);

		com_ptr<ID3D12RootSignature>& Get();

	private:
		com_ptr<ID3D12RootSignature> m_root_signature;

	};
}