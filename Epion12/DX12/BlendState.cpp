
#include	"../Epion12.h"
#include	"BlendState.h"

namespace epion::DX12
{

	D3D12_BLEND_DESC BlendStateManager::m_blend_desc;
	bool BlendStateManager::Initialize()
	{
		// レンダーターゲットのブレンド設定.
		D3D12_RENDER_TARGET_BLEND_DESC descRTBS = {
			false, false,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_LOGIC_OP_NOOP,
			D3D12_COLOR_WRITE_ENABLE_ALL
		};

		// ブレンドステートの設定.
		m_blend_desc.AlphaToCoverageEnable = false;
		m_blend_desc.IndependentBlendEnable = false;
		for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
		{
			m_blend_desc.RenderTarget[i] = descRTBS;
		}
		return true;
	}
	bool BlendStateManager::Finalize()
	{
		return true;
	}

	D3D12_BLEND_DESC& BlendStateManager::GetDesc()
	{
		return m_blend_desc;
	}

}