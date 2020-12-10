#pragma	once

//	キャスト関連
#define	st_cast	static_cast
#define	r_cast	reinterpret_cast
#define	c_cast	const_cast
#define	d_cast	dynamic_cast

#define	sa_cast	safe_cast


#define	I_FOR(value_limit)	for(unsigned	char	i	=0;	i	<value_limit;	i++)

#define	TO_STRING(VariableName)	#VariableName

namespace	epion
{
	//シングルトン、クラステンプレート
	template<class	T>
	class	Singleton
	{
	public:
		static	T& GetInst()	noexcept
		{
			static	T	inst;
			return	inst;
		};
	private:
		void	operator	=(const	Singleton& obj) {}	//代入演算子禁止
		Singleton(const	Singleton& obj) {}				//コピーコンストラクタ禁止
	protected:
		Singleton() {}									//外部でのインスタンス作成は禁止
		virtual	~Singleton() {};
	};

	//n次元配列初期化(ただの配列のみ)
	template<	class	A, size_t	N, class	T>
	void	set_array_fill(A(&array)[N], const	T& val)
	{
		std::fill((T*)array, (T*)(array + N), val);
	}

	template<class	T>
	using	com_ptr = Microsoft::WRL::ComPtr<T>;

	//定数
	constexpr	int CHAR_SIZE = 256;

	class BaseClass abstract
	{
	public:
		BaseClass() {}
		virtual	~BaseClass() {}

		virtual bool	Initialize() = 0;
		virtual bool	Finalize() = 0;
		virtual void	Update() = 0;

	protected:
	};
}
