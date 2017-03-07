#pragma once
#include<vector>
#include<string.h>
extern "C"{
#include"SFMT/SFMT.h"
}
#include"RNGData.hpp"
#include<iostream>
#include<fstream>
#include<sstream>

void saveFile(const std::vector<RandData>& rd);
void saveFile(const std::vector<PokeStatus>& pkst);
std::vector<RandData> getRandDataList(uint32_t seed, int searchN);
std::vector<PokeStatus> getPokeStatusList(const std::vector<RandData>& rd, int searchN);
