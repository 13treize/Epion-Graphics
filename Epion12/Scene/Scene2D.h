#pragma once

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
		com_ptr<ID3DBlob> vs_blob;
		com_ptr<ID3DBlob> ps_blob;
		//std::unique_ptr<Model::Square> m_square;
		//std::unique_ptr<Model::Square> m_square2;
	};
}
