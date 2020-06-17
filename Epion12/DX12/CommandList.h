#pragma once

/**
 * @file CommandList.h
 * @brief CommandList�쐬
 * @author treize
 * @date 2020/02/21
 * @details
 �R�}���h���X�g�쐬�N���X�A
 <br>11�Ō���devicecontext�̈��
 <br>https://docs.microsoft.com/en-us/windows/win32/api/d3d12/nn-d3d12-id3d12graphicscommandlist
 */
namespace epion::DX12
{
	class CommandList final
	{
	public:
		CommandList();
		~CommandList();
		static bool Initialize(com_ptr<ID3D12CommandAllocator>& cmd_alloc);
		bool Finalize();
		//get
		static com_ptr<ID3D12GraphicsCommandList>& GetPtr();
	private:
		static com_ptr<ID3D12GraphicsCommandList> m_cmd_list;
	};
}