#pragma once
#include	"../DX12/ShaderManager.h"
#include	"../DX12/Buffer.h"
namespace epion::Model
{
	class Model abstract
	{
	public:
		Model();
		virtual ~Model() {}

	protected:
		bool m_is_update;
		std::unique_ptr<DX12::ShaderReflection> m_shader_reflection;
		std::unique_ptr<DX12::VertexBuffer> m_vertex;
		std::unique_ptr<DX12::IndexBuffer> m_index;
		com_ptr<ID3DBlob> m_error_blob;

	};
}