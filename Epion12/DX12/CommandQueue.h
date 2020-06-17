#pragma once
/**
 * @file CommandQueue.h
 * @brief CommandQueue作成
 * @author treize
 * @date 2020/02/18
 * @details
 コマンドキュー作成クラス
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
		* SwapChain作成関数
		* @brief 要約説明
		* @param (引数名) 引数の説明
		* @param (引数名) 引数の説明
		* @return 戻り値の説明
		* @sa 参照すべき関数を書けばリンクが貼れる
		* @detail 関数内部で実装,templateで欲しい型(1から4を取得)
		*/
		static bool CreateCommandQueue(com_ptr<ID3D12Device>& device, com_ptr<ID3D12CommandQueue>& queue);
	};


}