#pragma once
namespace	epion::DX12
{
	enum class ShaderType :unsigned char
	{
		TYPE_VERTEX,
		TYPE_HULL,
		TYPE_DOMAIN,
		TYPE_GEOMETRY,
		TYPE_PIXEL,
	};

	bool	ShaderCompile(std::wstring_view hlsl_name, std::string_view entry_point, std::string_view target, com_ptr<ID3DBlob>& shader_blob);

	class ShaderResouceManager final
	{
	public:
		static bool	Initialize();
		static bool	Finalize();
		static bool Settings();
		static bool Compile(std::wstring_view hlsl_name, com_ptr<ID3DBlob>& shader_blob, ShaderType type);
		static bool Compile(std::wstring_view hlsl_name, std::string_view entry_point,com_ptr<ID3DBlob>& shader_blob, ShaderType type);
	private:

	};
	class	ShaderReflection final
	{
	public:
		void ReflectionInputLayout(com_ptr<ID3DBlob>& shader_blob);
		std::vector<D3D12_INPUT_ELEMENT_DESC>& GetInputLayout();
	private:
		com_ptr<ID3D12ShaderReflection>	m_reflection;
		std::vector<D3D12_INPUT_ELEMENT_DESC>	m_layout;

		const DXGI_FORMAT GetDXGIFormat(const D3D_REGISTER_COMPONENT_TYPE type, const byte mask);
		const unsigned int	GetVertexBufferSlot(const std::string& semantic_name);
	};

}
