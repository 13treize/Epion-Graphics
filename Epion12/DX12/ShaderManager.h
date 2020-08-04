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

	bool	ShaderCompile(const std::wstring& hlsl_name, const std::string& entry_point, const std::string& target, com_ptr<ID3DBlob>& shader_blob);

	class ShaderResouceManager final
	{
	public:
		static bool	Initialize();
		static bool	Finalize();
		static bool Settings();
		static bool Compile(const std::wstring& hlsl_name, com_ptr<ID3DBlob>& shader_blob, ShaderType type);
		static bool Compile(const std::wstring& hlsl_name, const std::string& entry_point,com_ptr<ID3DBlob>& shader_blob, ShaderType type);
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
