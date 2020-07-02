#pragma once
namespace epion::DX12
{
	class BlendStateManager final
	{
	public:
		static bool Initialize();
		static bool Finalize();

		static D3D12_BLEND_DESC& GetDesc();
	private:
		static D3D12_BLEND_DESC m_blend_desc;

	};
}