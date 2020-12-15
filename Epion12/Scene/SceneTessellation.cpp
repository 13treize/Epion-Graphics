#include	"../Epion12.h"

#include	"SceneManager.h"
#include	"SceneTessellation.h"

#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"
#include	"../Camera/CameraManager.h"
#include	"../DX12/ShaderManager.h"
#include	"../DX12/RootSignature.h"
#include	"../DX12/DescriptorHeap.h"


namespace
{
	constexpr int DRAW_CALL_NUM = 1;
}
namespace epion
{
	bool SceneTessellation::Initialize()
	{
		return true;
	}
	bool SceneTessellation::Finalize()
	{
		return true;
	}
	void SceneTessellation::Update()
	{
	}
	void SceneTessellation::Render(int frame_count)
	{
	}
	void SceneTessellation::RenderTex()
	{
	}
}