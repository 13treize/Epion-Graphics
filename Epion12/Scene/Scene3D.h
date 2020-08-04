#pragma once
#include	"../DX12/Buffer.h"
#include	"../Model/ObjMesh.h"
#include	"../Model/StaticMesh.h"

namespace	epion
{
	class	 Scene3D	final :public	Scene
	{
	public:
		bool	Initialize()	override;
		bool	Finalize() 		override;
		void	Update()		override;
		void	Render(int frame_count)		override;
		void	RenderTex()		override;

	private:
		com_ptr<ID3DBlob> vs_blob;
		com_ptr<ID3DBlob> ps_blob;
	};
}
