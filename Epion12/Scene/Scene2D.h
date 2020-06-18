#pragma once
#include	"../Model/Square.h"

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
		epion::com_ptr<ID3DBlob> ps_blob2;

		std::unique_ptr<Model::Square> m_square;
	};
}
