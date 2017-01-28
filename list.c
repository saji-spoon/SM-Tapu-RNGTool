#include<stdio.h>
#include<stdlib.h>
#include"SFMT/SFMT.h"
#include"util.h"

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

typedef struct RandData_
{
        int tick; //0-16
        int vp; //0-5
        int iv; //0-31
        int nature; //0-25
} RandData;

int main(int argc, char* argv[])
{
        if(argc < 2 || strlen(argv[1]) < 8)
        {
                printf("Usage: %s 1234FEDC\n", argv[0]);
                printf("Seed(32 bit) is required.\n");
                return 1;
        }

        const int SEARCH_SIZE = 1000;

        RandData rd[SEARCH_SIZE];

        sfmt_t sfmt;

        uint32_t seed;
        
        sscanf(argv[1], "%x", &seed);
        

        sfmt_init_gen_rand(&sfmt, seed);

        //416 frame advances when the game starts.
        for(int i=0; i<417; ++i)
        {
                sfmt_genrand_uint64(&sfmt);
        }
        
        FILE* listFp;
        if((listFp = fopen("./lists/list.csv", "w"))==NULL)
        {
                perror("list file:");
                exit(EXIT_FAILURE);
        }
        
        fprintf(listFp, "Consumed, Tick, VPlace, IV, Nature\n");
        for(int i=0; i<SEARCH_SIZE; ++i)
        {
                uint64_t result = sfmt_genrand_uint64(&sfmt);
                rd[i].tick = result % 17;
                rd[i].vp = result % 6;
                rd[i].iv = result % 32;
                rd[i].nature = result % 25;

                fprintf(listFp, "%d,%d,%c,%d,%d\n", i, rd[i].tick, intToVPlace(rd[i].vp), rd[i].iv, rd[i].nature);

        }

        FILE* indivFp;
        if((indivFp = fopen("./lists/indivList.csv", "w"))==NULL)
        {
                perror("indivList file:");
                exit(EXIT_FAILURE);
        }

        fprintf(indivFp, "Consumed,H,A,B,C,D,S,Nature\n");
        for(int i=0; i<SEARCH_SIZE; ++i)
        {
                fprintf(indivFp, "%d,", i);
                int iv[6] = {-1, -1, -1, -1, -1, -1};
                int state = 0;
                for(int j=0; i+j < SEARCH_SIZE; ++j)
                {
                        switch(state)
                        {
                                case 0: case 1: case 2:
                                if(iv[rd[i+j].vp] != 31)
                                {
                                        iv[rd[i+j].vp] = 31;
                                        ++state;
                                }
                                break;
                                case 3:case 4: case 5:
                                for(int h=0; h<6; ++h)
                                {
                                        if(iv[h] == -1)
                                        {
                                                iv[h] = rd[i+j].iv;
                                                ++state;
                                                break;
                                        }
                                        
                                }
                                break;
                                case 6:
                                for(int h=0; h<6; ++h)
                                {
                                        fprintf(indivFp, "%d,", iv[h]);
                                }
                                fprintf(indivFp, "N/A"/*, rd[i+j].nature*/);
                                ++state;
                                break;
                                
                        }
                        


                        if(state==7)
                        {
                                break;
                        }
                }
                fprintf(indivFp, "\n");
        }
        
        printf("Lists created. See ./lists/\n");



        return 0;
}
