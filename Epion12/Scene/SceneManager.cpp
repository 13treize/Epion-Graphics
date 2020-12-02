#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"SceneDefault.h"
#include	"Scene2D.h"
#include	"Scene3D.h"
#include	"SceneNoise.h"
#include	"SceneDemoProcedural.h"
#include	"SceneSimpleLighting.h"
#include	"SceneNodeEditor.h"

namespace
{
}
namespace	epion
{
	std::unique_ptr<Scene>	SceneManager::m_scene = {};
	std::unique_ptr<Scene>	SceneManager::m_next_scene = std::make_unique<SceneProcedural>();

	void	SceneManager::Update()
	{
		m_scene->Update();
	}

	void	SceneManager::Render(int frame_count)
	{
		m_scene->Render(frame_count);
	}
	bool SceneManager::Release()
	{
		m_scene->Finalize();
		return true;
	}

	//std::unique_ptr<Texture>& SceneManager::GetTexData()
	//{
	//	return m_scene->m_tex;
	//}

	void	SceneManager::ChangeScene()
	{
		if (m_next_scene)
		{
			if (m_scene)
			{
				m_scene->Finalize();
			}
			m_scene = std::move(m_next_scene);
			m_scene->Initialize();
		}
	}
}