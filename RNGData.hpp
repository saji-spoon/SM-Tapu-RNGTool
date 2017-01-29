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

char intToVPlace(int vp)
{
        switch(vp)
        {
                case 0:
                return 'H';
                case 1:
                return 'A';
                case 2:
                return 'B';
                case 3:
                return 'C';
                case 4:
                return 'D';
                case 5:
                return 'S';
                default:
                return '-';
        }
}

std::string intToNature(int nature)
{
        switch(nature)
        {
                case 0:
                return "がんばりや";
                case 1:
                return "さみしがり";
                case 2:
                return "ゆうかん";
                case 3:
                return "いじっぱり";
                case 7:
                return "のんき";
                case 10:
                return "おくびょう";
		case 13:
		return "ようき";
                case 15:
                return "ひかえめ";
		case 17:
		return "れいせい";
		case 23:
		return "しんちょう";
                default:
                return "N/A";
        }
}
std::ostream& operator<<(std::ostream& ofs, const RandData& rd)
{
	ofs << rd.tick << "," << intToVPlace(rd.vp) << "," << rd.iv << "," << intToNature(rd.nature);
	return ofs;
};

std::ostream& operator<<(std::ostream& ofs, const PokeStatus& pkst)
{
	for(const auto iv : pkst.iv)
	{
		ofs << iv << ",";
	}

	ofs << intToNature(pkst.nature);

	return ofs;
};
