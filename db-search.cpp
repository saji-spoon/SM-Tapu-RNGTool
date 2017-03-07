#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<algorithm>
#include<memory>
#include"util.hpp"
#include"SFMTUtil.hpp"
#include"tickSeed.hpp"

int main(int argc,char *argv[])
{       
        if(argc < 2 || strlen(argv[1]) != 8)
        {
                printf("Usage: %s 0BEEFBAG\n", argv[0]);
                printf("8 ticks(clock hands) are required.\n");
                return 1;

        }
	std::vector<uint64_t> ticks;
	
	for(size_t i=0; i<strlen(argv[1]); ++i)
	{
		ticks.push_back(HepttoNum(argv[1][i]));
	}

	std::string filename = "./db/";
	filename += argv[1][0];
	filename += argv[1][1];
	filename += ".bin";

	std::cout << filename << "\n";

        std::unique_ptr<FILE, decltype(&fclose)> fp(fopen(filename.c_str(), "rb"), fclose);
        if(!fp) 
        {
		perror("file error(fp)");
		exit(EXIT_FAILURE);
	}
        
        off_t size = fileSize(filename.c_str()) / sizeof(uint32_t);

        //seedのみファイルから読み込む
        std::unique_ptr<uint32_t, decltype(&free)> sds((uint32_t*)malloc(sizeof(uint32_t)*size), free); 
        if(!sds) 
        {
		perror("memory error(sds)");
		exit(EXIT_FAILURE);
	}
        //計測
        clock_t start = clock();

        uint32_t readSize = fread((void*)sds.get(), sizeof(uint32_t), size, fp.get()); 

	std::cout << "readSize:" << readSize <<"\n";

	std::vector<uint32_t> seeds(sds.get(), sds.get()+readSize);
 
	clock_t end = clock();

        printf("read:%lf[s]\n", 1.0*(end-start)/CLOCKS_PER_SEC);

        start = clock();
        
	std::vector<uint64_t> first8Ticks;
	
	std::copy(ticks.begin(), ticks.begin()+8, std::back_inserter(first8Ticks));

        uint32_t key = tickToTickkey(first8Ticks);

	//search for seed matches input clockhands as key 
	auto it = std::lower_bound(seeds.begin(), seeds.end(), key, [](const uint32_t e, const uint32_t val){return seedToTickkey(e)<val;});
	bool found = (seedToTickkey(*it)==key);
	
        end = clock();
        printf("search:%lf[s]\n\n", 1.0*(end-start)/CLOCKS_PER_SEC);

        if(!found)
        {
                printf("Not found.\n");
                return 0;
        }
        else
        {
		for( ; it!=seeds.end(); ++it)
		{
			if(seedToTickkey(*it) != key) break;
			std::cout << tickToStr(seedToTick(*it, 10)) << ":" << std::hex << *it << std::dec << "\n";
		}
        }

        return 0;
}

