#pragma once
#include<cassert>
namespace	epion::Math
{
	template<	class	T>
	struct	Vector4	final
	{
		T	x;
		T	y;
		T	z;
		T	w;

		constexpr	Vector4(T	x = 0.0f, T	y = 0.0f, T	z = 0.0f, T	w = 0.0f) :x(x), y(y), z(z), w(w) {}
		constexpr	Vector4(const	Vector4&	v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
		~Vector4() = default;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(	CEREAL_NVP(x),
						CEREAL_NVP(y),
						CEREAL_NVP(z),
						CEREAL_NVP(w));
		};

		const T	& operator[](std::size_t index) const&
		{
			if (!(index>=0	&&index<=3))
			{
				assert(0);
				return 0;
			}

			T* p = &x;
			return p[index];
		}
		T	& operator[](std::size_t index) &
		{
			T* p = &x;
			return p[index];
		}
		//float operator[](std::size_t index) const&&
		//{
		//	T* p = &x;
		//	return p[index];
		//}
		//	+
		Vector4	operator+(const	Vector4&	vec)	const
		{
			Vector4		n = *this;
			return(n += vec);
		}
		Vector4&	operator+=(const	Vector4&	vec)
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
			w += vec.w;
			return*this;
		}
		Vector4&	operator+=(const	T	value)
		{
			x += value;
			y += value;
			z += value;
			w += value;
			return	*this;
		}

		//	-
		Vector4	operator-(const	Vector4&	vec)	const
		{
			Vector4	n = *this;
			return	n -= vec;
		}

		Vector4&	operator-=(const	Vector4&	vec)
		{
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
			w -= vec.w;
			return*this;
		}

		Vector4&	operator-=(const	T	value)
		{
			x -= value;
			y -= value;
			z -= value;
			w -= value;
			return	*this;
		}

		//	*
		Vector4	operator*(const	Vector4&	vec)const
		{
			return	Vector4(x	*vec.x, y	*vec.y, z	*vec.z, w	*vec.w);
		}
		Vector4	operator*(const	T	value)const
		{
			return	Vector4(x	*value, y	*value, z	*value, w	*value);
		}
		Vector4&	operator*=(const	Vector4&	vec)
		{
			x *= vec.x;
			y *= vec.y;
			z *= vec.z;
			w *= vec.w;
			return	*this;
		}
		Vector4&	operator*=(T	value)
		{
			x *= value;
			y *= value;
			z *= value;
			w *= value;
			return	*this;
		}

		//	/
		Vector4	operator/(const	Vector4&	vec)const
		{
			return	Vector4(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
		}
		Vector4	operator/(const	T	value)const
		{
			return	Vector4(x / value, y / value, z / value, w / value);
		}
		Vector4&	operator/=(const	Vector4&	vec)
		{
			x /= vec.x;
			y /= vec.y;
			z /= vec.z;
			w /= vec.w;
			return	*this;
		}
		Vector4&	operator/=(const	T	value)
		{
			x /= value;
			y /= value;
			z /= value;
			w /= value;
			return*this;
		}

		//etc...
		bool	operator==(const	Vector4&	vec)const
		{
			if (x == vec.x	&&y == vec.y	&&z == vec.z &&w == vec.w)
			{
				return	true;
			};
			return	false;
		}
		bool	operator!=(const	Vector4&	vec)const
		{
			if (x != vec.x || y != vec.y || z != vec.z || w != vec.w)
			{
				return	true;
			};
			return	false;
		}
		Vector4&	set_x(T	_x)
		{
			this->x = _x;
			return	*this;
		}
		Vector4&	set_y(T	_y)
		{
			this->y = _y;
			return	*this;
		}
		Vector4&	set_z(T	_z)
		{
			this->z = _z;
			return	*this;
		}
		Vector4&	set_w(T	_w)
		{
			this->w = _w;
			return	*this;
		}
		Vector4&	set_xy(T	_x, T	_y)
		{
			this->x = _x;
			this->y = _y;
			return	*this;
		}

		Vector4&	SetXYZ(T	_x, T	_y, T	_z)
		{
			this->x = _x;
			this->y = _y;
			this->z = _z;
			return	*this;
		}
		T	get_length()	const
		{
			return	std::hypot(x, y, z);
		}
		Vector4&	normalize()
		{
			*this /= get_length();
			return	*this;
		}
	};
}