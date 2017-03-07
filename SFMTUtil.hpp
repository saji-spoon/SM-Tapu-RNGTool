#pragma once
#include<stdint.h>
#include<iostream>
#include<vector>
#include<string>
#include"util.hpp"

extern "C"
{
#include"SFMT/SFMT.h"
}

std::vector<uint64_t> seedToTick(uint32_t seed, int num);

std::string tickToStr(const std::vector<uint64_t>& tick);

uint32_t tickToTickkey(const std::vector<uint64_t>& tick);

uint32_t seedToTickkey(uint32_t seed);

