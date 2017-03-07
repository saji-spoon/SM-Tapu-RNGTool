#include<stdio.h>
#include"SFMT/SFMT.h"
#include"util.h"

int main()
{
        sfmt_t sfmt;
        char str[30];
        const uint32_t SEEK_MAX = 0xB98AB4F4U; //0xFFFFFFFFFFFFFFFF        

        uint32_t seed;

        for(seed = 0xB98AB4F3U; seed < SEEK_MAX; ++seed)
        {
                sfmt_init_gen_rand(&sfmt, seed);

                //416 frame advances when the game starts.
                for(int i=0; i<417; ++i)
                {
                        sfmt_genrand_uint64(&sfmt);
                }

                for(int i=0; i<10; ++i)
                {
                        uint64_t result = sfmt_genrand_uint64(&sfmt);
                        uint64toHex(result, str);
                        printf("%c", numtoR17(result%17));
                }

                printf(",%u", seed);

                printf("\n");
        }


        return 0;
}
