#pragma once
namespace epion::DX12
{
	class Texture
	{
	public:


	private:
		DirectX::TexMetadata	m_metadata = {};
		DirectX::ScratchImage	m_image = {};
		com_ptr<ID3D12Resource> m_tex;
	};

	enum class Extension :unsigned char
	{
		PNG,
		JPG,
		//TGA,
		//BMP,
		NONE,
	};

	//TextureExport
	class	TextureFileIO	final
	{
	public:
		static bool LoadTexture(const std::wstring& load_texture, DirectX::TexMetadata& metadata, DirectX::ScratchImage& image);
		static bool SaveTexture(const std::string& name, com_ptr<ID3D12Resource>& texture);
		static bool SaveTexture(const std::string& name, const std::string& extension, com_ptr<ID3D12Resource>& texture);
	private:
		//enum class‚É‚·‚é
		static Extension ExtensionGet(const std::string& extension);
	};

}