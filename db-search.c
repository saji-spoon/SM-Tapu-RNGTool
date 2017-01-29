#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include"util.h"
#include"tickSeed.h"

off_t fileSize(char* filename)
{
        struct stat st;
        stat(filename, &st);
        return st.st_size;
}

int main(int argc,char *argv[])
{       
        if(argc < 2 || strlen(argv[1]) != 8)
        {
                printf("Usage: %s 0BEEFBAG\n", argv[0]);
                printf("8 ticks(clock hands) are required.\n");
                return 1;

        }

        char head2[3];
        head2[0] = argv[1][0];
        head2[1] = argv[1][1];
        head2[2] = '\0';
        char* tail6 = argv[1]+2;
        uint32_t headIdx = r17toUint32(head2);

        char filename[20];
        sprintf(filename, "./db/%s.bin", head2);
        printf("./db/%s.bin\n", head2);


        FILE* fp;
        fp = fopen(filename, "rb");
        if(fp == NULL) 
        {
		perror("file error(fp)");
		exit(EXIT_FAILURE);
	}
        
        off_t size = fileSize(filename) / sizeof(TickSeed);

        //針、Seedの組み合わせ
        TickSeed* ts = (TickSeed*)malloc(sizeof(TickSeed)*size);
        uint32_t tsIdx = 0;

        //計測
        clock_t start = clock();


        tsIdx = fread((void*)ts, sizeof(TickSeed), size, fp);
              
        clock_t end = clock();
        printf("read:%lf[s]\n", 1.0*(end-start)/CLOCKS_PER_SEC);

        start = clock();
        qsort(ts, tsIdx, sizeof(TickSeed), tsComp);
        
        TickSeed key;
        key.tick = r17toUint32(argv[1]+2);

        TickSeed* result = (TickSeed*)bsearch((void*)&key, (void*)ts, tsIdx, sizeof(TickSeed), tsComp);

        end = clock();
        printf("search:%lf[s]\n", 1.0*(end-start)/CLOCKS_PER_SEC);
        
        if(result == NULL)
        {
                printf("Not found.\n");
                return 0;
        }
        else
        {
                for(int i=0; i<5; ++i)
                {
                        char tmpStr[20];
                        if(result-2+i < ts || ts+tsIdx-1 < result-2+i) continue;
                        if(key.tick != (result-2+i)->tick) continue;
                        uint32toR17Str((result-2+i)->tick, tmpStr, 6);
                        printf("Result[%d]... %c%c%s:%x\n", i-2, argv[1][0], argv[1][1], tmpStr, (result-2+i)->seed);
                       
                }


        }

        printf("read:%u\n", tsIdx);
        return 0;
}

