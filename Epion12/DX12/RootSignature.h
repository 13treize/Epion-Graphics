#pragma once
namespace epion::DX12
{

	class RootSignature final
	{
	public:
		RootSignature();
		~RootSignature();

		bool Initialize();
		bool Initialize(D3D12_ROOT_PARAMETER& desc);

		com_ptr<ID3D12RootSignature>& Get();

	private:
		com_ptr<ID3D12RootSignature> m_root_signature;
	};


	class RootSignatureManager final
	{
	public:
		static void Build();
		static void SetGraphicsRootSignature();

		static com_ptr<ID3D12RootSignature>& Get();

	private:
		static com_ptr<ID3D12RootSignature> m_root_signature;

	};

}