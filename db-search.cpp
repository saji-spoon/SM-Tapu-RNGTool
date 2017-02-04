#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include<string>
#include<algorithm>
#include"util.hpp"
#include"SFMTUtil.hpp"
#include"tickSeed.hpp"

off_t fileSize(char* filename)
{
        struct stat st;
        stat(filename, &st);
        return st.st_size;
}

struct TickEncode
{
	TickEncode()
	{}

	TickEncode(uint32_t v)
	:val(v)
	{
	}
	uint32_t val;
};

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

        FILE* fp;
        fp = fopen(filename.c_str(), "rb");
        if(fp == NULL) 
        {
		perror("file error(fp)");
		exit(EXIT_FAILURE);
	}
        
	char tmpFilename[30];
	strncpy(tmpFilename, filename.c_str(), 29);
        off_t size = fileSize(tmpFilename) / sizeof(uint32_t);

        //seedのみファイルから読み込む
        uint32_t* sds = (uint32_t*)malloc(sizeof(uint32_t)*size);
        uint32_t readSize = 0;

        //計測
        clock_t start = clock();

        readSize = fread((void*)sds, sizeof(uint32_t), size, fp); 

	std::cout << "readSize:" << readSize <<"\n";

	std::vector<uint32_t> seeds(sds, sds+readSize);
 
	clock_t end = clock();

        printf("read:%lf[s]\n", 1.0*(end-start)/CLOCKS_PER_SEC);

        start = clock();
        
        uint32_t key;
	std::vector<uint64_t> keyTick;
	for (int i=0; i<8; ++i)
	{
		keyTick.push_back(ticks[i]);
	}	

        key = tickToTickkey(keyTick);

        uint32_t* result = NULL;//(uint32_t*)bsearch((void*)&key, (void*)seeds, readSize, sizeof(uint32_t), seedComp);

	//auto findit = std::find_if(seeds.begin(), seeds.end(), [&key](const uint32_t& e){return seedToTickkey(e)==key;});
	//std::cout << "compare:" << seedToTickkey(*findit) << " " << key << "\n";

	auto it = std::lower_bound(seeds.begin(), seeds.end(), key, [](const uint32_t e, const uint32_t val){return seedToTickkey(e)<val;});
	
        end = clock();
        printf("search:%lf[s]\n\n", 1.0*(end-start)/CLOCKS_PER_SEC);

	bool found = (seedToTickkey(*it)==key);

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

        //printf("read:%u\n", tsIdx);
        return 0;
}

