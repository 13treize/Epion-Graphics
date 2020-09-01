#pragma once
#include	"../DX12/Buffer.h"
#include	"../Model/Square.h"

namespace	epion
{
	class SceneNoise	final :public	Scene
	{
	public:
		bool	Initialize()	override;
		bool	Finalize() 		override;
		void	Update()		override;
		void	Render(int frame_count)	override;
		void	RenderTex()		override;

	private:
		void UpdataGUI();
		com_ptr<ID3DBlob> m_vs_blob;

		std::array<com_ptr<ID3DBlob>, 48> m_ps_blob;
		std::array<std::unique_ptr<Model::Square>, 48> m_square;
		std::array<Math::FVector4, 4> m_data;
	};
}