#pragma once
#include"Model.h"

namespace epion::Model
{
	class TestModel final :public Model
	{
		TestModel();
		~TestModel();
		bool init(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig);
		void update();
		void render();
	};
}