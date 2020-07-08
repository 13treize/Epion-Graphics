#include	<wincodec.h>
#include "../Epion12.h"
#include "Texture.h"


namespace epion::DX12
{
	bool TextureFileIO::LoadTexture(const std::wstring&	load_texture, DirectX::TexMetadata& metadata, DirectX::ScratchImage& image)
	{
		HRESULT	hr = S_OK;
		hr = LoadFromWICFile(load_texture.c_str(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &metadata, image);
		if (FAILED(hr))	return false;
		//hr = CreateShaderResourceView(Device::GetDevice().Get(),
		//	m_image.GetImages(),
		//	m_image.GetImageCount(),
		//	m_metadata,
		//	srv.GetAddressOf());
		//if (FAILED(hr))	return false;
		return true;
	}

	bool TextureFileIO::SaveTexture(const std::string& name, com_ptr<ID3D12Resource>& texture)
	{
		HRESULT hr = {};
		//出力画像
		DirectX::ScratchImage output_image = {};
		GUID guid;

		std::filesystem::path	file_extension = name;
		//ファイル拡張子を取得
		auto	ext_str = file_extension.extension();

		//png
		if (ext_str == ".png")
			guid = GUID_ContainerFormatPng;
		//jpg
		else if (ext_str == ".jpg")
		{
			guid = GUID_ContainerFormatJpeg;
		}
		//読み込み失敗
		else
		{
			return false;
		}
		//hr = DirectX::CaptureTexture(Device::GetDevice().Get(), Device::GetContext().Get(), texture.Get(), output_image);
		//if (FAILED(hr)) return false;
		//hr = DirectX::SaveToWICFile(*output_image.GetImages(), 0, guid, String::StringConverter::ToWstring(name).c_str());
		//if (FAILED(hr)) return false;
		return true;
	}

	bool TextureFileIO::SaveTexture(const std::string& name, const std::string& ext, com_ptr<ID3D12Resource>& texture)
	{
		//HRESULT hr = {};
		//DirectX::ScratchImage output_image = {};//出力画像
		//GUID guid;
		//Extension extension = ExtensionGet(ext);

		//switch (extension)
		//{
		//case Extension::PNG:	guid = GUID_ContainerFormatPng;		break;
		//case Extension::JPG:	guid = GUID_ContainerFormatJpeg;	break;
		//}
		//std::string tex = name + ext;
		//hr = DirectX::CaptureTexture(Device::GetDevice().Get(), Device::GetContext().Get(), texture.Get(), output_image);
		//if (FAILED(hr)) return false;
		//hr = DirectX::SaveToWICFile(*output_image.GetImages(), 0, guid, String::StringConverter::ToWstring(tex).c_str());
		//if (FAILED(hr)) return false;
		return true;
	}
	Extension TextureFileIO::ExtensionGet(const std::string& extension)
	{
		if (extension == ".png")return Extension::PNG;
		else if (extension == ".jpg")return Extension::JPG;

		return Extension::NONE;
	}
}