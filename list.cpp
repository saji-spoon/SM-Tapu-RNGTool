#include"list.hpp"

void saveFile(const std::vector<RandData>& rd)
{
	std::ofstream ofs("./lists/list.csv");
        
	ofs << "Consumed,Tick,VPlace,IV,Nature,Sychro,Blink1,Blink2\n";

        for(size_t i=0; i<rd.size(); ++i)
        {
		ofs << i << "," << rd[i] << "\n";
        }
}

void saveFile(const std::vector<PokeStatus>& pkst)
{
	std::ofstream ofs("./lists/indivList.csv");
        
	
	ofs << "Consumed,H,A,B,C,D,S,Nature\n";

	for (size_t i=0; i<pkst.size(); ++i)
	{
		ofs << i << "," << pkst[i] << "\n";
	}


	
}

std::vector<RandData> getRandDataList(uint32_t seed, int searchN)
{	
        std::vector<RandData> rd(searchN);

        sfmt_t sfmt;
        
        sfmt_init_gen_rand(&sfmt, seed);

        //416 frame advances when the game starts.
        for(int i=0; i<417; ++i)
        {
                sfmt_genrand_uint64(&sfmt);
        }
        

        for(int i=0; i<searchN; ++i)
        {
                uint64_t result = sfmt_genrand_uint64(&sfmt);
		rd[i].raw = result;
                rd[i].tick = result % 17;
                rd[i].vp = result % 6;
                rd[i].iv = result % 32;
                rd[i].nature = result % 25;
		rd[i].synchro = result % 100;
		rd[i].blink1 = result % 128;
		rd[i].blink2 = result % 3;
        }

	return rd;
}

std::vector<PokeStatus> getPokeStatusList(const std::vector<RandData>& rd, int searchN)
{
	std::vector<PokeStatus> pkst(searchN);

        for(int i=0; i<searchN; ++i)
        {
                //fprintf(indivFp, "%d,", i);
                int state = 0;
                for(int j=0; i+j < searchN; ++j)
                {
                        switch(state)
                        {
                                case 0: case 1: case 2:
                                if(pkst[i].iv[rd[i+j].vp] != 31)
                                {
                                        pkst[i].iv[rd[i+j].vp] = 31;
                                        ++state;
                                }
                                break;
                                case 3:case 4: case 5:
                                for(int h=0; h<6; ++h)
                                {
                                        if(pkst[i].iv[h] == -1)
                                        {
                                                pkst[i].iv[h] = rd[i+j].iv;
                                                ++state;
                                                break;
                                        }
                                        
                                }
                                break;
                                case 6:
                                for(int h=0; h<6; ++h)
                                {
                                        pkst[i].iv[h];//fprintf(indivFp, "%d,", pkst[i].iv[h]);
                                }
                                pkst[i].nature = rd[i+j].nature; //fprintf(indivFp, "N/A"/*, rd[i+j].nature*/);
                                ++state;
                                break;
                        }
                        
                        if(state==7)
                        {
                                break;
                        }
                }
                //fprintf(indivFp, "\n");
        }
	return pkst;
	
}
