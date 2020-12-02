#include	"../Epion12.h"
#include	"ShadowMap.h"


namespace
{
}

namespace epion::DX12
{
	ShadowMap::ShadowMap()
	{
	}

	bool ShadowMap::Initialize(com_ptr<ID3D12Device>& device, const Math::Vector2<int>& screen_size)
	{
		return true;
	}
	void ShadowMap::CreateResource()
	{
		//D3D12_RESOURCE_DESC texDesc = {};
		//texDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		//texDesc.Alignment = 0;
		//texDesc.Width = mWidth;
		//texDesc.Height = mHeight;
		//texDesc.DepthOrArraySize = 1;
		//texDesc.MipLevels = 1;
		//texDesc.Format = mFormat;
		//texDesc.SampleDesc.Count = 1;
		//texDesc.SampleDesc.Quality = 0;
		//texDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		//texDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		//D3D12_CLEAR_VALUE optClear;
		//optClear.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		//optClear.DepthStencil.Depth = 1.0f;
		//optClear.DepthStencil.Stencil = 0;

		//ThrowIfFailed(md3dDevice->CreateCommittedResource(
		//	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		//	D3D12_HEAP_FLAG_NONE,
		//	&texDesc,
		//	D3D12_RESOURCE_STATE_GENERIC_READ,
		//	&optClear,
		//	IID_PPV_ARGS(&mShadowMap)));

	}

}