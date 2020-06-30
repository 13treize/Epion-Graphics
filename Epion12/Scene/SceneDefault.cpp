#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"SceneDefault.h"
#include	"../DX12/ViewPort.h"
#include	"../Camera/CameraManager.h"

namespace epion
{
	bool SceneDefault::Initialize()
	{
		//Camera::CameraManager::Init(DX12::ViewPort::GetAspect());
		return true;
	}
	bool SceneDefault::Finalize()
	{
		return true;
	}
	void SceneDefault::Update()
	{
	}
	void SceneDefault::Render()
	{
	}
	void SceneDefault::RenderTex()
	{
	}
}