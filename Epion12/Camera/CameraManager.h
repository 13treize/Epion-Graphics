#pragma once
namespace	epion::Camera
{
	class	View	/*abstract*/
	{
	public:
		View();

		View(const Math::FVector3& p_, const Math::FVector3& t_, const Math::FVector3& u_,
			float fov_, float aspect_, float n_, float f_);

		virtual	~View() {};



		void SetView(const	Math::FVector3& p, const	Math::FVector3& t, const Math::FVector3& u);

		void SetProjection(float fov, float aspect, float n, float f);
		//�s��X�V
		void Activate();


		DirectX::XMMATRIX&	GetMatView();
		DirectX::XMMATRIX&	GetMatProjection();

		DirectX::XMFLOAT4X4& Get4x4View();
		DirectX::XMFLOAT4X4& Get4x4Projection();
		//get�֐�
		Math::FVector3& GetPos();
		Math::FVector3& GetTarget();
		Math::FVector3& GetUp();

		//set�֐�
		void	SetPos(Math::FVector3& pos_);
		void	SetTarget(Math::FVector3& target_);
		void	SetUp(Math::FVector3& up_);

	protected:
		DirectX::XMMATRIX	MatView;		//����ϊ��s��
		DirectX::XMMATRIX	MatProjection;	//���e�ϊ��s��
		DirectX::XMFLOAT4X4	F4x4View;		//����ϊ��s��
		DirectX::XMFLOAT4X4	F4x4Projection;	//���e�ϊ��s��
		Math::FVector3	pos;
		Math::FVector3	target;
		Math::FVector3	up;
		float fov;
		float aspect;
		float nearPlane;
		float farPlane;
	};

	class	BasicCamera	final : public	View
	{
	public:
		BasicCamera();

		BasicCamera(const	Math::FVector3& p_,
			const	Math::FVector3& t_,
			const	Math::FVector3& u_,
			float fov_,
			float aspect_,
			float n_,
			float f_);

		~BasicCamera() {};

	};

	//Node��PreviewCamera
	class	PreviewCamera	final : public	View
	{
	public:
		PreviewCamera();

		PreviewCamera(const	Math::FVector3& p_,
			const	Math::FVector3& t_,
			const	Math::FVector3& u_,
			float fov_,
			float aspect_,
			float n_,
			float f_);

		~PreviewCamera() {};
	};

	class	Scene3DCamera	final : public	View
	{
	public:
		Scene3DCamera();

		Scene3DCamera(
			const	Math::FVector3& p_,
			const	Math::FVector3& t_,
			const	Math::FVector3& u_,
			float fov_,
			float aspect_,
			float n_,
			float f_);

		~Scene3DCamera() {};
	};


	class	CameraManager	final
	{
	public:
		static	void	Init(const float aspect);
		static	void	Update();

		//get�֐�

		static std::unique_ptr<BasicCamera>& GetBasicCamera();
		static std::unique_ptr<PreviewCamera>& GetPreviewCamera();
		static std::unique_ptr<Scene3DCamera>& GetScene3DCamera();

	private:
		static	std::unique_ptr<BasicCamera>	m_basic_camera;
		static	std::unique_ptr<PreviewCamera>	m_preview_camera;
		static	std::unique_ptr<Scene3DCamera>	m_scene3d_camera;

	};
}