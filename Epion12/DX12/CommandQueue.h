#pragma once
/**
 * @file CommandQueue.h
 * @brief CommandQueue�쐬
 * @author treize
 * @date 2020/02/18
 * @details
 �R�}���h�L���[�쐬�N���X
 <br>https://docs.microsoft.com/en-us/windows/win32/api/d3d12/nn-d3d12-id3d12device
 */

namespace epion::DX12
{
	class CommandQueue final
	{
	public:
		CommandQueue();
		~CommandQueue();
		bool Initialize(com_ptr<ID3D12Device>& device);
		bool Finalize();
		void Update(com_ptr<ID3D12GraphicsCommandList>& cmd_list);
		//get
		com_ptr<ID3D12CommandQueue>& GetPtr();

	private:
		com_ptr<ID3D12CommandQueue> m_cmd_queue;
	};


	struct CommandQueueFunction
	{
		/**
		* @fn
		* SwapChain�쐬�֐�
		* @brief �v�����
		* @param (������) �����̐���
		* @param (������) �����̐���
		* @return �߂�l�̐���
		* @sa �Q�Ƃ��ׂ��֐��������΃����N���\���
		* @detail �֐������Ŏ���,template�ŗ~�����^(1����4���擾)
		*/
		static bool CreateCommandQueue(com_ptr<ID3D12Device>& device, com_ptr<ID3D12CommandQueue>& queue);
	};


}