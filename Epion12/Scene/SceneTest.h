#pragma once
#include	"../DX12/Buffer.h"
#include	"../Model/ObjMesh.h"
#include	"../Model/StaticMesh.h"

namespace	epion
{
	const int NUM_FRAME_RESOUCE = 3;
	class	SceneTest	final :public	Scene
	{
	public:
		bool	Initialize()	override;
		bool	Finalize() 		override;
		void	Update()		override;
		void	Render(int frame_count)		override;
		void	RenderTex()		override;

	private:
		int m_num_frame_resources;

		com_ptr<ID3DBlob> vs_blob;
		com_ptr<ID3DBlob> ps_blob[2];

		std::unique_ptr<Model::ObjMesh> m_plane;
		std::unique_ptr<Model::Polygon> m_mesh;
		std::unique_ptr<Model::Polygon> m_mesh2;

	};
}
