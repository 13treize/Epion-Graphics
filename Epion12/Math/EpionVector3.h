#pragma	once
namespace	epion::Math
{
	//xyz
	template<	class	T>
	struct	Vector3	final
	{
		T	x;
		T	y;
		T	z;

		constexpr	Vector3(T	x	=0,	T	y	=0,	T	z	=0)	:x(x),	y(y),	z(z){}
		constexpr	Vector3(const	Vector3&	vec)	:	x(vec.x),	y(vec.y),		z(vec.z){}
		~Vector3()	=default;

		template<class Archive>
		void serialize(Archive & archive, Vector3<T>)
		{
			archive(CEREAL_NVP(x),
					CEREAL_NVP(y),
					CEREAL_NVP(z));
		};

		//	+
		Vector3	operator+(const	Vector3&	vec)	const
		{
			Vector3		n	=*this;
			return(n		+=vec);
		}
		Vector3&	operator+=(const	Vector3&	vec)
		{
			x	+=vec.x;
			y	+=vec.y;
			z	+=vec.z;
			return*this;
		}
		Vector3&	operator+=(const	T	value)
		{
			x	+=value;
			y	+=value;
			z	+=value;
			return	*this;
		}

		//	-
		Vector3	operator-(const	Vector3&	vec)	const
		{
			Vector3	n	=*this;
			return	n	-=vec;
		}
		Vector3&	operator-=(const	Vector3&	vec)
		{
			x	-=vec.x;
			y	-=vec.y;
			z	-=vec.z;
			return*this;
		}
		Vector3&	operator-=(const	T	value)
		{
			x		-=value;
			y		-=value;
			z		-=value;
			return	*this;
		}

		//	*
		Vector3	operator*(const	Vector3&	vec)const
		{
			return	Vector3(x	*vec.x,	y	*vec.y,	z	*vec.z);
		}
		Vector3	operator*(const	T	value)const
		{
			return	Vector3(x	*value,	y	*value,	z	*value);
		}
		Vector3&	operator*=(const	Vector3&	vec)
		{
			x	*=vec.x;
			y	*=vec.y;
			z	*=vec.z;
			return	*this;
		}
		Vector3&	operator*=(T	value)
		{
			x	*=value;
			y	*=value;
			z	*=value;
			return*this;
		}

		//	/
		Vector3	operator/(const	Vector3&	vec)const
		{
			return	Vector3(x	/vec.x,	y	/vec.y,	z	/vec.z);
		}
		Vector3	operator/(const	T	value)const
		{
			return	Vector3(x	/value,	y	/value,	z	/value);
		}
		Vector3&	operator/=(const	Vector3&	vec)
		{
			x	/=vec.x;
			y	/=vec.y;
			z	/=vec.z;
			return	*this;
		}
		Vector3&	operator/=(const	T	value)
		{
			x	/=value;
			y	/=value;
			z	/=value;
			return*this;
		}

		//etc...
		bool	operator==(const	Vector3&	vec)const
		{
			if(x	==vec.x	&&y	==vec.y	&&z	==vec.z)
			{
				return	true;
			};
			return	false;
		}
		bool	operator!=(const	Vector3&	vec)const
		{
			if(x	!=vec.x	||y	!=vec.y	||z	!=vec.z)
			{
				return	true;
			};
			return	false;
		}
		Vector3&	set_x(T	_x)
		{
			this->x	=_x;
			return	*this;
		}
		Vector3&	set_y(T	_y)
		{
			this->y	=_y;
			return	*this;
		}
		Vector3&	set_z(T	_z)
		{
			this->z	=_z;
			return	*this;
		}
		Vector3&	SetXYZ(T	_x,	T	_y,	T	_z)
		{
			this->x	=_x;
			this->y	=_y;
			this->z	=_z;
			return	*this;
		}
		T	get_length()	const
		{
			return	std::hypot(x,	y,	z);
		}
		Vector3&	normalize()
		{
			*this	/=get_length();
			return	*this;
		}
	};
}