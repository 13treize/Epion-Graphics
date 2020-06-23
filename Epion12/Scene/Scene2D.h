#pragma once
#include	"../DX12/Buffer.h"
#include	"../Model/Square.h"
#include	"../Model/Plane.h"

namespace	epion
{
	class	 Scene2D	final :public	Scene
	{
	public:
		bool	Initialize()	override;
		bool	Finalize() 		override;
		void	Update()		override;
		void	Render()		override;
		void	RenderTex()		override;

	private:
		epion::com_ptr<ID3DBlob> vs_blob;
		epion::com_ptr<ID3DBlob> ps_blob;
		epion::com_ptr<ID3DBlob> hs_blob;
		epion::com_ptr<ID3DBlob> ds_blob;
		epion::com_ptr<ID3DBlob> gs_blob;

		epion::com_ptr<ID3DBlob> ps_blob2;

		std::unique_ptr<Model::Square> m_square;
		std::unique_ptr<Model::Plane> m_plane;
		std::unique_ptr<DX12::ConstantBuffer> m_cbuffer;

	};
}
