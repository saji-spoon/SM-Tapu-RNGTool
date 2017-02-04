#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include<string>
#include<iostream>
#include"util.hpp"
#include"tickSeed.hpp"

off_t fileSize(char* filename)
{
        struct stat st;
        stat(filename, &st);
        return st.st_size;
}

int main(int argc,char *argv[])
{       
	for (int i=0; i<289; ++i)
	{
		FILE* frp;
		std::string filename = dbFilename(i);
		frp = fopen(filename.c_str(), "rb");
		if(frp == NULL) 
		{
			perror("file error(frp)");
			continue;
		}
		std::cout << "Sorting " << filename << "...\n";

		char tmpFilename[30];
		strncpy(tmpFilename, filename.c_str(), 29);
		off_t size = fileSize(tmpFilename) / sizeof(TickSeed);

		//針、Seedの組み合わせ
		TickSeed* ts = (TickSeed*)malloc(sizeof(TickSeed)*size);
		uint32_t tsIdx = 0;

		//計測
		clock_t start = clock();

		tsIdx = fread((void*)ts, sizeof(TickSeed), size, frp);
		      
		qsort(ts, tsIdx, sizeof(TickSeed), tsComp);
		
		clock_t end = clock();
		
		printf("sort:%lf[s]\n", 1.0*(end-start)/CLOCKS_PER_SEC);
		
		fclose(frp);
		
		FILE* fwp;
		fwp = fopen(filename.c_str(), "wb");
		if(fwp == NULL) 
		{
			perror("file error(fwp)");
			exit(EXIT_FAILURE);
		}

		for (int i=0; i<tsIdx; ++i)
		{
			fwrite(&(ts[i].seed), sizeof(uint32_t), 1, fwp); 
		}
		

		fclose(fwp);
		free(ts);
	}


        return 0;
}

