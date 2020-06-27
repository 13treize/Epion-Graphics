#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"
#include	"../DX12/ViewPort.h"
#include	"../Camera/CameraManager.h"
#include	"Scene3D.h"

namespace
{
}
namespace epion
{
	bool Scene3D::Initialize()
	{
		Camera::CameraManager::Init(DX12::ViewPort::GetAspect());
		return true;
	}

	bool Scene3D::Finalize()
	{
		return true;
	}
	void Scene3D::Update()
	{
		Camera::CameraManager::Update();
	}

	void Scene3D::Render()
	{
	}
	void Scene3D::RenderTex()
	{
	}

}