#pragma once
#include	"../DX12/Buffer.h"
#include	"../Model/ObjMesh.h"
#include	"../Model/StaticMesh.h"

namespace	epion
{
	class	SceneTest	final :public	Scene
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

		//std::unique_ptr<Model::ObjMesh> m_plane;
		std::unique_ptr<Model::Polygon> m_mesh[2];

		std::unique_ptr<DX12::ConstantBuffer> m_cbuffer;

	};
}