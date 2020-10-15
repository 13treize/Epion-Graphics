#pragma once
namespace	epion::Physics
{
	class	ColliderBase
	{
	public:
		ColliderBase() {}
		virtual ~ColliderBase() {}

	private:
	};

	class	Collider2D	final :public	ColliderBase
	{
	public:
		template<class	T>
		__forceinline	static	bool	SphereAndSphere(const	Math::Vector2<T>& p, const	Math::Vector2<T>& e, const	T	r1, const	T	r2 = 0);

		template<class	T>
		__forceinline	static	bool	AABB(const	Math::Vector2<T>& p, const	Math::Vector2<T>& e, const	T	p_r1, const	T	e_r1);

		template<class	T>
		__forceinline	static	bool	LineCircle(const	Math::Vector2<T>& a, const	Math::Vector2<T>& b, const	Math::Vector2<T>& p, const	T	dis);

	private:
	};

	class	Collider3D	final :public	ColliderBase
	{
	public:
		template<class	T>
		__forceinline	static	bool	SphereAndSphere(const	Math::Vector3<T>& p, const	Math::Vector3<T>& e, const	T	r1, const	T	r2 = 0);

		template<class	T>
		__forceinline	static	bool	AABB(const	Math::Vector3<T>& p, const	Math::Vector3<T>& e, const	T	p_r1, const	T	e_r1);

	private:
	};

	template<class	T>
	__forceinline	static	bool	Collider2D::SphereAndSphere(const	Math::Vector2<T>& p, const	Math::Vector2<T>& e, const	T	r1, const	T	r2)
	{
		Math::Vector2<T>	dis = { e.x - p.x, e.y - p.y };	//ìÒì_ä‘ÇÃãóó£ÇÃéZèo
		T	vec = dis.x * dis.x + dis.y * dis.y;
		T	radius = (r1 + r2) * (r1 + r2);	//îºåa
		if (vec < radius)
		{
			return	true;		//ìñÇΩÇ¡ÇΩÇÁtrue
		}
		return	false;
	}

	template<class	T>
	__forceinline	static	bool	Collider2D::AABB(const	Math::Vector2<T>& p, const	Math::Vector2<T>& e, const	T	p_r1, const	T	e_r1)
	{
		Math::Vector2<T>	p_min(p.x - p_r1, p.y - p_r1);
		Math::Vector2<T>	p_max(p.x + p_r1, p.y + p_r1);
		Math::Vector2<T>	e_min(e.x - e_r1, e.y - e_r1);
		Math::Vector2<T>	e_max(e.x + e_r1, e.y + e_r1);

		if (p_min.x > e_max.x)	return	false;
		if (p_max.x < e_min.x)	return	false;
		if (p_min.y > e_max.y)	return	false;
		if (p_max.y < e_min.y)	return	false;

		return	true;	//è’ìÀÇµÇƒÇ¢ÇÈ

	}

	template<class	T>
	__forceinline	static	bool	Collider2D::LineCircle(const	Math::Vector2<T>& a, const	Math::Vector2<T>& b, const	Math::Vector2<T>& p, const	T	dis)
	{
		Math::Vector2<T>	vecab = Math::Vector2<T>(b - a);
		Math::Vector2<T>	vecap = Math::Vector2<T>(p - a);
		Math::Vector2<T>	vecbp = Math::Vector2<T>(p - b);

		float	vecab_len = std::sqrt(std::powf(vecab.x, 2));
		float	vecap_len = std::sqrt(std::powf(vecap.x, 2));
		float	vecbp_len = std::sqrt(std::powf(vecbp.x, 2));

		Math::Vector2<T>	normalAB = vecab.normalize();

		float	len_ax = normalAB.inner(vecap);

		float	short_dis;
		if (len_ax < 0)
		{
			short_dis = vecap_len;
		}
		else	if (len_ax > vecab_len)
		{
			short_dis = vecbp_len;
		}
		else
		{
			short_dis = std::abs(normalAB.cross(vecap));
		}

		if (short_dis < dis / 2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/*
		3D
	*/

	//	é¿ëï
	template<class	T>
	__forceinline	static	bool	Collider3D::SphereAndSphere(const	Math::Vector3<T>& p, const	Math::Vector3<T>& e, const	T	r1, const	T	r2)
	{
		Math::Vector3<T>	distance(e.x - p.x, e.y - p.y, e.z - p.z);
		T	vector = distance.x * distance.x +
			distance.y * distance.y +
			distance.z * distance.z;
		T	radius = (r1 + r2) * (r1 + r2);	//îºåa
		if (vector < radius)
		{
			return	true;		//ìñÇΩÇ¡ÇΩÇÁtrue
		}
		else
		{
			return	false;
		}
	}

	template<class	T>
	__forceinline	static	bool	Collider3D::AABB(const	Math::Vector3<T>& p, const	Math::Vector3<T>& e, const	T	p_r1, const	T	e_r1)
	{
		Math::Vector3<T>	p_min(p.x - p_r1, p.y - p_r1, p.z - p_r1);
		Math::Vector3<T>	p_max(p.x + p_r1, p.y + p_r1, p.z + p_r1);
		Math::Vector3<T>	e_min(e.x - e_r1, e.y - e_r1, e.z - e_r1);
		Math::Vector3<T>	e_max(e.x + e_r1, e.y + e_r1, e.z + e_r1);

		if (p_min.x > e_max.x)	return	false;
		if (p_max.x < e_min.x)	return	false;
		if (p_min.y > e_max.y)	return	false;
		if (p_max.y < e_min.y)	return	false;
		if (p_min.z > e_max.z)	return	false;
		if (p_max.z < e_min.z)	return	false;

		return	true;	//è’ìÀÇµÇƒÇ¢ÇÈ
	}

}