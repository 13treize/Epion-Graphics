#pragma once
namespace epion::DX12
{
	class Rasterizer final
	{
	public:
		Rasterizer();
		~Rasterizer();

		bool Initialize(const D3D12_FILL_MODE fill);
		bool Finalize();

		D3D12_RASTERIZER_DESC& GetDesc();

	private:
		D3D12_RASTERIZER_DESC m_desc;
	};

	class RasterizerManager final
	{
	public:
		static bool Initialize();
		static bool Finalize();

		static D3D12_RASTERIZER_DESC& GetSolidDesc();
		static D3D12_RASTERIZER_DESC& GetWireDesc();

	private:
		static Rasterizer m_solid;
		static Rasterizer m_wire;
	};

}