#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"SceneDefault.h"
#include	"Scene2D.h"

namespace
{
}
namespace	epion
{
	std::unique_ptr<Scene>	SceneManager::m_scene = {};
	std::unique_ptr<Scene>	SceneManager::m_next_scene = std::make_unique<Scene2D>();

	void	SceneManager::Update()
	{
		m_scene->Update();
	}

	void	SceneManager::Render()
	{
		m_scene->Render();
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