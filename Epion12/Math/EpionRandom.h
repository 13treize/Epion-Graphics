#pragma	once
#include	<random>
namespace	epion::Math
{
	//ただの乱数クラス
	class	Random	final
	{
	public:
		//指定した範囲の間の乱数を返す
		template<class	T>
		__forceinline	static	T	get_num(T	min_, T	max_);

		//指定した確率(0.0f～1.0f)のtrueを返す
		__forceinline	static	bool	is_get(float	num_);

		//vectorの中身に入っている数値(確率)に応じて、配列の添え字(要素数)を返す
		template<class	T>
		__forceinline	static	int	discrete_get(const	std::vector<T>&	data);



		//noise関数
		float	noise(int	param_);

		/*
			https://cpprefjp.github.io/reference/random/piecewise_constant_distribution.html
		*/
		class	Piecewice
		{
		public:
		};

	private:
		static	std::random_device	rd;	//ハードウェアエントロピー
		static	std::mt19937		mt;	//メルセンヌツイスタ

		//一応
		//static	std::knuth_b				knu;		//KnuthのリオーダーアルゴリズムB
		//static	std::default_random_engine	def_rd;		//妥協乱数
		//static	std::mt19937_64				mt_64;
		//static	std::ranlux24				ra_24;		//RANKUX法
		//static	std::ranlux48				ra_48;
		//static	std::minstd_rand			minstd;		//MINSTD最小標準
		//static	std::minstd_rand0			minstd_0;
	};
}//	namespace epion::Math


//実装
template<class	T>
__forceinline	static	T	epion::Math::Random::get_num(T	min_, T	max_)
{
	mt.seed(rd());
	std::uniform_int_distribution<T>	rand_num(min_, max_);
	return	rand_num(mt);
}
template<>
__forceinline	static	float	epion::Math::Random::get_num<float>(float	min_, float	max_)
{
	mt.seed(rd());
	std::uniform_real_distribution<float>	rand_num(min_, max_);
	return	rand_num(mt);
}
template<>
__forceinline	static	double	epion::Math::Random::get_num<double>(double	min_, double	max_)
{
	mt.seed(rd());
	std::uniform_real_distribution<double>	rand_num(min_, max_);
	return	rand_num(mt);
}


template<class	T>
__forceinline	static	int	epion::Math::Random::discrete_get(const	std::vector<T>&	data)
{
	mt.seed(rd());
	std::discrete_distribution<int>	dist(data.begin(), data.end());
	return	dist(mt);
};
