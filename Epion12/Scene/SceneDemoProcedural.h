#pragma once
#include	"../DX12/Buffer.h"
#include	"../Model/ObjMesh.h"
#include	"../Model/StaticMesh.h"
#include	"../DX12/ConstantBufferManager.h"

namespace	epion
{
	class	SceneProcedural	final :public	Scene
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
		std::array<com_ptr<ID3DBlob>,60> ps_blob;
		std::array<std::unique_ptr<Model::Polygon>,60> m_mesh;
		std::array<std::unique_ptr<Model::CubeMesh>, 10> m_cube;

		DX12::CBufferPassConstants data;
	};
}
