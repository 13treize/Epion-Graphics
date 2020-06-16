#pragma	once
namespace	epion::Math
{
	template<	class	T>
	struct	Vector2	final
	{
		T	x;
		T	y;
		constexpr	Vector2(T	x	=0,	T	y	=0)	:x(x),		y(y){}
		constexpr	Vector2(const	Vector2&	v)	:x(v.x),	y(v.y){}
		~Vector2()	=default;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(CEREAL_NVP(x),	CEREAL_NVP(y));
		};

		//	+
		Vector2	operator+(const	Vector2&	vec)const
		{
			return	Vector2(x	+vec.x,	y	+vec.y);
		}
		Vector2&	operator+=(const	Vector2&	vec)
		{
			x	+=vec.x;
			y	+=vec.y;
			return	*this;
		}
		Vector2&	operator+=(const	T	value)
		{
			x	+=value;
			y	+=value;
			return	*this;
		}

		//	-
		Vector2	operator-(const	Vector2&	vec)const
		{
			return	Vector2(x	-vec.x,	y	-vec.y);
		}
		Vector2&	operator-=(const	Vector2&	vec)
		{
			x	-=vec.x;
			y	-=vec.y;
			return	*this;
		}
		Vector2&	operator-=(const	T	value)
		{
			x	-=value;
			y	-=value;
			return	*this;
		}

		//	*
		Vector2	operator*(const	Vector2&	vec)const
		{
			return	Vector2(x	*vec.x,	y	*vec.y);
		}
		Vector2	operator*(const	T	value)const
		{
			return	Vector2(x	*value,	y	*value);
		}
		Vector2&	operator*=(const	Vector2&	vec)
		{
			x	*=vec.x;
			y	*=vec.y;
			return	*this;
		}
		Vector2&	operator*=(const	T	value)
		{
			x	*=value;
			y	*=value;
			return	*this;
		}

		//	/
		Vector2	operator/(const	Vector2&	vec)const
		{
			return	Vector2(x	/vec.x,	y	/vec.y);
		}
		Vector2	operator/(const	T	value)const
		{
			return	Vector2(x	/value,	y	/value);
		}
		Vector2&	operator/=(const	Vector2&	vec)
		{
			x	/=vec.x;
			y	/=vec.y;
			return	*this;
		}
		Vector2&	operator/=(const	T	value)
		{
			x	/=value;
			y	/=value;
			return	*this;
		}

		//etc...
		bool	operator==(const	Vector2&	vec)const
		{
			if(x	==vec.x	&&y	==vec.y)
			{
				return	true;
			};
			return	false;
		}
		bool	operator!=(const	Vector2&	vec)const
		{
			if(x	!=vec.x	||y	!=vec.y)
			{
				return	true;
			};
			return	false;
		}

		Vector2&	set_x(T	_x)
		{
			this->x		=_x;
			return	*this;
		}
		Vector2&	set_y(T	_y)
		{
			this->y		=_y;
			return	*this;
		}
		Vector2&	set_xy(T	_x,	T	_y)
		{
			this->x	=_x;
			this->y	=_y;
			return	*this;
		}

		T	get_length()const
		{
			return	std::hypot(x,	y);
		}
		Vector2&	normalize()
		{
			*this	/=get_length();
			return	*this;
		}

		T	inner(Vector2& v1)
		{
			return (x * v1.x + y * v1.y);
		}

		T	cross(Vector2& v1)
		{
			return(x * v1.y - v1.x * y);
		}
	};
}