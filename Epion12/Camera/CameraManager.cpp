#include	"../Epion12.h"
#include	"CameraManager.h"

namespace
{
	epion::Math::FVector3	pos = { 0.0f,	0.0f, 10.0f };
	epion::Math::FVector3	target = { 0.0f,	0.0f,	0.0f };
	epion::Math::FVector3	up = { 0.0f,	1.0f,	0.0f };

}

namespace	epion::Camera
{
	View::View()
	{
	}

	View::View(const Math::FVector3& p, const Math::FVector3& t, const Math::FVector3& u, float fov_, float aspect_, float n_, float f_)
		:pos(p), target(t), up(u),
		fov(fov_), aspect(aspect_), nearPlane(n_), farPlane(f_)
	{
	}

	void	View::SetView(const	Math::FVector3& p, const	Math::FVector3& t, const	Math::FVector3& u)
	{
		pos = p;
		target = t;
		up = u;
	}

	void	View::SetProjection(float	fov_, float	aspect_, float	n, float	f)
	{
		fov = fov_;
		aspect = aspect_;
		nearPlane = n;
		farPlane = f;
	}

	void	View::Activate()
	{
		DirectX::XMMATRIX	mv, mp;

		DirectX::XMVECTOR	eye = {}, focus = {}, up_ = {};
		eye = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f);
		focus = DirectX::XMVectorSet(target.x, target.y, target.z, 1.0f);
		up_ = DirectX::XMVectorSet(up.x, up.y, up.z, 0.0f);

		mv = DirectX::XMMatrixLookAtLH(eye, focus, up_);
		DirectX::XMStoreFloat4x4(&matView, mv);

		mp = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearPlane, farPlane);
		DirectX::XMStoreFloat4x4(&matProjection, mp);
	}

	//	getä÷êî
	Math::FVector3& View::GetPos()
	{
		return	pos;
	}

	Math::FVector3& View::GetTarget()
	{
		return	target;
	}

	Math::FVector3& View::GetUp()
	{
		return	up;
	}


	//	setä÷êî
	void	View::SetPos(Math::FVector3& pos_)
	{
		pos = pos_;
	}

	void	View::SetTarget(Math::FVector3& target_)
	{
		target = target_;
	}

	void	View::SetUp(Math::FVector3& up_)
	{
		up = up_;
	}

	BasicCamera::BasicCamera()
	{
	}
	BasicCamera::BasicCamera(const Math::FVector3& p_, const Math::FVector3& t_, const Math::FVector3& u_,
		float fov_, float aspect_, float n_, float f_) :View(p_, t_, u_, fov_, aspect_, n_, f_)
	{
	}

	PreviewCamera::PreviewCamera()
	{
	}

	PreviewCamera::PreviewCamera(const Math::FVector3& p_, const Math::FVector3& t_, const Math::FVector3& u_,
		float fov_, float aspect_, float n_, float f_) :View(p_, t_, u_, fov_, aspect_, n_, f_)
	{
	}

	Scene3DCamera::Scene3DCamera()
	{
	}

	Scene3DCamera::Scene3DCamera(const Math::FVector3& p_, const Math::FVector3& t_, const Math::FVector3& u_,
		float fov_, float aspect_, float n_, float f_) :View(p_, t_, u_, fov_, aspect_, n_, f_)
	{
	}

	std::unique_ptr<BasicCamera>	CameraManager::m_basic_camera;
	std::unique_ptr<PreviewCamera>	CameraManager::m_preview_camera;
	std::unique_ptr<Scene3DCamera>	CameraManager::m_scene3d_camera;

	void	CameraManager::Init(const float aspect)
	{
		//ÉJÉÅÉâèâä˙âª

		epion::Math::FVector3	pos = { 0.0f,	-7.0f, 5.0f };

		m_basic_camera = std::make_unique<BasicCamera>(
			Math::FVector3(0.0f, 0.0f, 10.0f),
			target,
			up,
			Math::pi<float> / 8.0f,
			aspect,
			0.1f,
			1000.0f);

		m_preview_camera = std::make_unique<PreviewCamera>(
			Math::FVector3(0.0f, 0.0f, 10.0f),
			Math::FVector3(0.0f, 1.0f, 0.0f),
			up,
			Math::pi<float> / 8.0f,
			400.0f / 400.0f,
			0.1f,
			1000.0f);

		m_scene3d_camera = std::make_unique<Scene3DCamera>(
			Math::FVector3(0.0f, -6.0f, 5.0f),
			Math::FVector3(0.0f, 0.0f, 0.0f),
			up,
			Math::pi<float> / 8.0f,
			aspect,
			0.1f,
			1000.0f);


	}

	void	CameraManager::Update()
	{
		m_basic_camera->Activate();
		m_preview_camera->Activate();
		m_scene3d_camera->Activate();
	}

	std::unique_ptr<BasicCamera>& CameraManager::GetBasicCamera()
	{
		return m_basic_camera;
	}
	std::unique_ptr<PreviewCamera>& CameraManager::GetPreviewCamera()
	{
		return m_preview_camera;
	}
	std::unique_ptr<Scene3DCamera>& CameraManager::GetScene3DCamera()
	{
		return m_scene3d_camera;
	}
}