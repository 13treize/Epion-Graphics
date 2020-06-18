#include "../Epion12.h"
#include "Model.h"


namespace epion::Model
{
	Model::Model()
	{
		m_is_update = true;
		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_vertex = std::make_unique<DX12::VertexBuffer>();
		m_index = std::make_unique<DX12::IndexBuffer>();
	}
}