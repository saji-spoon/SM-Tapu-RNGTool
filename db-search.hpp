#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<algorithm>
#include<memory>
#include<iterator>
#include<cassert>
#include"util.hpp"
#include"SFMTUtil.hpp"
#include"tickSeed.hpp"

std::vector<TickSeed> searchDB(const std::vector<uint64_t>& ticks);
