#pragma once
#include<cstdint>
#include<ostream>
#include<string>

struct PokeStatus 
{	
        int iv[6] = {-1,-1,-1,-1,-1,-1};
        int nature = -1;
};

struct RandData
{
        int tick; //0-16
        int vp; //0-5
        int iv; //0-31
        int nature; //0-25
};

char intToVPlace(int vp);
std::string intToNature(int nature);
std::ostream& operator<<(std::ostream& ofs, const RandData& rd);
std::ostream& operator<<(std::ostream& ofs, const PokeStatus& pkst);
