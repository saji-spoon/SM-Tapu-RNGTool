#include"SFMTUtil.hpp"

std::vector<uint64_t> seedToTick(uint32_t seed, int num)
{
	sfmt_t sfmt;
	sfmt_init_gen_rand(&sfmt, seed);
	for(int i=0; i<417; ++i)
	{
		sfmt_genrand_uint64(&sfmt);
	}
	std::vector<uint64_t> rtn;
	for(int i=0; i<num; ++i)
	{
		rtn.push_back(sfmt_genrand_uint64(&sfmt)%17);
	}

	return rtn;
}

std::string tickToStr(const std::vector<uint64_t>& tick)
{
	std::string rtn = "";

	for(const auto& t : tick)
	{
		rtn += numtoR17(static_cast<int>(t));
	}

	return rtn;
}

uint32_t tickToTickkey(const std::vector<uint64_t>& tick)
{
	if(tick.size()!=8)
	{
		std::cerr << "tickToTickkeyError:8 tick \n";
		exit(EXIT_FAILURE);
	}

	uint32_t tickkey = 0;

	for(int i=0; i<6; ++i)
	{
		tickkey = tickkey * 17 + tick[i+2];
	}

	return tickkey;

}

uint32_t seedToTickkey(uint32_t seed)
{
	return tickToTickkey(seedToTick(seed, 8));
}
