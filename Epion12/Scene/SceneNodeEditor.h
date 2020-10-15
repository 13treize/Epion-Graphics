#pragma once
#include	"../GUI/NodeWindow.h"
namespace	epion
{
	class SceneNodeEditor	final :public	Scene
	{
	public:
		bool	Initialize()	override;
		bool	Finalize()		override;
		void	Update()		override;
		void	Render(int frame_count)		override;
		void	RenderTex()		override;

	private:
		GUI::NodeWindow m_node_window;
		ImGuiWindowFlags m_window_flags;

	};
}
