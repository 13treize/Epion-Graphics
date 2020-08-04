#pragma once
namespace epion::DX12
{
	class RootSignatureManager final
	{
	public:
		static void Build2D(D3D12_ROOT_PARAMETER_TYPE type);
		static void Build();
		static void SetGraphicsRootSignature();

		static com_ptr<ID3D12RootSignature>& Get();

	private:
		static com_ptr<ID3D12RootSignature> m_root_signature;

	};

}