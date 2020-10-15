#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"SceneDefault.h"
#include	"../DX12/ViewPort.h"
#include	"../Camera/CameraManager.h"
#include	"../Model/PMDMesh.h"
namespace epion
{
	bool SceneDefault::Initialize()
	{
		//Camera::CameraManager::Init(DX12::ViewPort::GetAspect());
		Model::PMDMesh m("../Assets/Model/èââπÉ~ÉN.pmd");
		return true;
	}
	bool SceneDefault::Finalize()
	{
		return true;
	}
	void SceneDefault::Update()
	{
	}
	void SceneDefault::Render(int frame_count)
	{
	}
	void SceneDefault::RenderTex()
	{
	}
}