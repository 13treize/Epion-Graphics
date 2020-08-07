#pragma once
namespace	epion
{
	class	Scene	abstract
	{
	public:
		virtual	~Scene() {};

		virtual bool	Initialize() = 0;
		virtual bool	Finalize() = 0;
		virtual	void	Update() = 0;
		virtual	void	Render(int frame_count) = 0;
		virtual	void	RenderTex() = 0;
	protected:
		//std::unique_ptr<Texture> m_tex;
	};

	class SceneManager	final
	{
	public:
		static void Update();
		static void Render(int frame_count);
		static bool Release();

		//static std::unique_ptr<Texture>& GetTexData();

		template<class T, class ...Args>
		static void SetNextScene(Args ...args);

		static void ChangeScene();

	private:
		static std::unique_ptr<Scene> m_scene;
		static std::unique_ptr<Scene> m_next_scene;
	};


	template<class	T, class	...Args>
	inline	void	SceneManager::SetNextScene(Args ...args)
	{
		if (!m_next_scene)
		{
			m_next_scene = std::make_unique<T>(args...);
		}
	}
}