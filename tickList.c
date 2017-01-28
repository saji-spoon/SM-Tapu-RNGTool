#include<stdio.h>
#include<stdlib.h>
#include"SFMT/SFMT.h"
#include"util.h"


int main(int argc, char* argv[])
{
        if(argc < 2 || strlen(argv[1]) < 8)
        {
                printf("Usage: %s 1234FEDC\n", argv[0]);
                printf("Seed(32 bit) is required.\n");
                return 1;

        }

        sfmt_t sfmt;

        uint32_t seed;
        
        sscanf(argv[1], "%x", &seed);
        printf("%x, %u\n", seed, seed);

        sfmt_init_gen_rand(&sfmt, seed);

        //416 frame advances when the game starts.
        for(int i=0; i<417; ++i)
        {
                sfmt_genrand_uint64(&sfmt);
        }

        for(int i=0; i<100; ++i)
        {
                uint64_t result = sfmt_genrand_uint64(&sfmt);
                printf("%c", numtoR17(result%17));
        }

        printf("\n");


        return 0;
}
