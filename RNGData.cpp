#include"RNGData.hpp"

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
		case 25:
		return "シンクロ";
                default:
                return "N/A";
        }
}
std::ostream& operator<<(std::ostream& ofs, const RandData& rd)
{
	ofs << rd.tick << "," 
	<< intToVPlace(rd.vp) << "," 
	<< rd.iv << "," 
	<< intToNature(rd.nature) << "," 
	<< rd.synchro << ","
	<< rd.blink1 << "," 
	<< rd.blink2; 
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

