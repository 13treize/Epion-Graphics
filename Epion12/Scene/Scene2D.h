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
		std::unique_ptr<Model::Square> m_square;
	};
}
