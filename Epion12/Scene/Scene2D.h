#pragma once
#include	"../DX12/Buffer.h"
//#include	"../DX12/FrameResource.h"
#include	"../Model/Square.h"

namespace	epion
{
	class Scene2D	final :public	Scene
	{
	public:
		bool	Initialize()	override;
		bool	Finalize()		override;
		void	Update()		override;
		void	Render(int frame_count)		override;
		void	RenderTex()		override;

	private:
		epion::com_ptr<ID3DBlob> vs_blob;
		epion::com_ptr<ID3DBlob> ps_blob;
		epion::com_ptr<ID3DBlob> hs_blob;
		epion::com_ptr<ID3DBlob> ds_blob;
		epion::com_ptr<ID3DBlob> gs_blob;

		com_ptr<ID3DBlob> ps_blob2;
		std::array<com_ptr<ID3DBlob>, 48> m_ps_blob;
		std::array<std::unique_ptr<Model::Square>, 48> m_square;
	};
}
