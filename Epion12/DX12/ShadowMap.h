#pragma once

namespace epion::DX12
{
	class ShadowMap
	{
	public:
		ShadowMap();
		ShadowMap(const ShadowMap& rhs) = delete;
		ShadowMap& operator=(const ShadowMap& rhs) = delete;
		~ShadowMap() = default;

		bool Initialize(com_ptr<ID3D12Device>& device, const Math::Vector2<int>& screen_size);

		void CreateResource();

	private:
		D3D12_VIEWPORT m_viewport;
		D3D12_RECT m_rect;
		Math::Vector2<int> m_screen_size;
		std::array<D3D12_STATIC_SAMPLER_DESC, 7> m_samplers;
		com_ptr<ID3D12Resource> m_shadow_map;

	};
}