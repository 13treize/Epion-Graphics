#pragma once
#include	"../DX12/ShaderManager.h"
#include	"../DX12/Buffer.h"
#include	"../DX12/ConstantBufferManager.h"
#include "PrimitiveModelData.h"

namespace epion::Model
{
	template <class T>
	concept IsPrimitive =std::is_base_of<CorePrimitive, T>::value;
	struct ModelParam
	{
		unsigned int ObjCBIndex;
		unsigned int MatCBIndex;
		unsigned int IndexCount;
		D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
		D3D12_INDEX_BUFFER_VIEW IndexBufferView;
		com_ptr<ID3D12PipelineState> PipeLineState;
		DirectX::XMMATRIX WorldMatrix;
	};
	class ModelCore abstract
	{
	public:
		ModelCore();
		virtual ~ModelCore() {}
		void DefaultSetPipeLine(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3D12RootSignature>& root_sig);
	protected:
		bool m_is_update;
		std::unique_ptr<DX12::ShaderReflection> m_shader_reflection;
		std::unique_ptr<DX12::ResourceBuffer<Model2DVertex>> m_vertex_resource;
		std::unique_ptr<DX12::ResourceBuffer<unsigned short>> m_index_resource;

		com_ptr<ID3DBlob> m_error_blob;
		D3D12_VERTEX_BUFFER_VIEW m_vertex_buffer_view;
		D3D12_INDEX_BUFFER_VIEW m_index_buffer_view;
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_pipeline_desc;
	};

	class Model3D abstract
	{
	public:
		Model3D();
		virtual ~Model3D() {}
		void DefaultSetPipeLine(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob,com_ptr<ID3D12RootSignature>& root_sig);
		void ResourceUpdate();
		void Draw(com_ptr<ID3D12GraphicsCommandList>& cmd);
		Math::FVector3& GetPos();
		Math::FVector3& GetAngle();
		Math::FVector3& GetScale();
		void SetPos(const float x, const float y, const float z);
		void SetAngle(const float x, const float y, const float z);
		void SetScale(const float x, const float y, const float z);

		std::unique_ptr<ModelParam>& GetState();
	protected:
		bool m_is_update;
		std::unique_ptr<DX12::ShaderReflection> m_shader_reflection;
		std::unique_ptr<DX12::ResourceBuffer<Model3DVertex>> m_vertex_resource;
		std::unique_ptr<DX12::ResourceBuffer<unsigned short>> m_index_resource;
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_pipeline_desc;

		std::unique_ptr<ModelParam> m_model_param;
		com_ptr<ID3DBlob> m_error_blob;
		Math::FVector3 m_pos;
		Math::FVector3 m_angle;
		Math::FVector3 m_scale;

		template<IsPrimitive T, class D,class M>
		void PrimitiveBufferSet(com_ptr<D>& device);

		bool ShaderSet(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob);
	};
	template<IsPrimitive T,class D, class M>
	void Model3D::PrimitiveBufferSet(com_ptr<D>& device)
	{
		m_vertex_resource = std::make_unique<DX12::ResourceBuffer<M>>();
		m_vertex_resource->Initialize(device, sizeof(M), false);
		m_vertex_resource->CopyResource<T::VERTEX_SIZE>(T::vertices);
		m_model_param->VertexBufferView = { m_vertex_resource->GetGPUVirtualAddress() ,sizeof(M) *T::VERTEX_SIZE,sizeof(M) };
		m_index_resource = std::make_unique<DX12::ResourceBuffer<unsigned short>>();
		m_index_resource->Initialize(device, T::INDEX_SIZE, false);
		m_index_resource->CopyResource<T::INDEX_SIZE>(T::indices);
		m_model_param->IndexBufferView = { m_index_resource->GetGPUVirtualAddress(), T::INDEX_SIZE * sizeof(unsigned short),DXGI_FORMAT::DXGI_FORMAT_R16_UINT };
		m_model_param->IndexCount = m_index_resource->GetCount();
	}


	static void ModelParamDraw(com_ptr<ID3D12GraphicsCommandList>& cmd,std::unique_ptr<ModelParam>& param)
	{
		cmd->SetPipelineState(param->PipeLineState.Get());
		cmd->IASetVertexBuffers(0, 1, &param->VertexBufferView);
		cmd->IASetIndexBuffer(&param->IndexBufferView);
		cmd->DrawIndexedInstanced(param->IndexCount, 1, 0, 0, 0);
	}

	static void CBSetModelDraw(com_ptr<ID3D12GraphicsCommandList>& cmd, std::unique_ptr<ModelParam>& param)
	{
		DX12::ConstantBufferManager::UpdateCBuffer1(param->WorldMatrix, param->ObjCBIndex);
		DX12::ConstantBufferManager::SetCBuffer1(param->ObjCBIndex);
		ModelParamDraw(cmd, param);
	}
	template <class T>
	concept Drawable = requires (T & x)
	{
		x.Draw();
	};
	template<class T>
	void ModelDraw(std::unique_ptr<T>& model, com_ptr<ID3D12GraphicsCommandList>& cmd)
	{
		model->Draw(cmd);
	}
}