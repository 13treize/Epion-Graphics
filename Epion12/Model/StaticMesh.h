#pragma once
#include"Model.h"

namespace epion::Model
{
	class Polygon final :public Model3D
	{
	public:
		Polygon();
		~Polygon();
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3D12RootSignature>& root_sig, unsigned int obj_cb_index, unsigned int mat_cb_index);
		bool Finalize();
		void Update();
		void Render();
	private:
	};
	class CubeMesh final :public Model3D
	{
	public:
		CubeMesh();
		~CubeMesh();
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3D12RootSignature>& root_sig, unsigned int obj_cb_index, unsigned int mat_cb_index);
		bool Finalize();
		void Update();
		void Render();
	private:
	};

	class SphereMesh final :public Model3D
	{
	public:
		SphereMesh();
		~SphereMesh();
		bool Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3D12RootSignature>& root_sig, unsigned int obj_cb_index, unsigned int mat_cb_index);
		bool Finalize();
		void Update();
		void Render();
	private:
	};

}