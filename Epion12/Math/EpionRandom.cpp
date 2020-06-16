#pragma	warning(disable	:4244)
#pragma	warning(disable	:26451)

#include	"EpionRandom.h"


namespace
{
}

namespace	epion::Math
{
	std::random_device	Random::rd;	//ハードウェアエントロピー
	std::mt19937		Random::mt;	//メルセンヌツイスタ

	bool	Random::is_get(float	num_)
	{
		float	seed_num	=std::clamp(num_,	0.0f,	1.0f);
		mt.seed(rd());
		std::bernoulli_distribution	rand_bool(seed_num);
		return	rand_bool(mt);
	}


	float	Random::noise(int	param_)
	{
		int	set_param	=(param_	<<13)	^param_;
		//ここの値は素数ならなんでもいいはず
		float	retern_num	=(1	-((param_	*(param_	*param_	+ 15731 + 789221)	+ 1376312589)	&0x2ffffffff)	/107341824);
		return	retern_num;
	}
}