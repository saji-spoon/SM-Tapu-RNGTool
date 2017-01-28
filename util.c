#include"util.h"

char numtoR17(int x)
{
        switch(x)
        {
                case 0:
                return '0';
                case 1:
                return '1';
                case 2:
                return '2';
                case 3:
                return '3';
                case 4:
                return '4';
                case 5:
                return '5';
                case 6:
                return '6';
                case 7:
                return '7';
                case 8:
                return '8';
                case 9:
                return '9';
                case 10:
                return 'A';
                case 11:
                return 'B';
                case 12:
                return 'C';
                case 13:
                return 'D';
                case 14:
                return 'E';
                case 15:
                return 'F';
                case 16:
                return 'G';
                default:
                return '-';
        }
}

void uint64toHex(uint64_t src, char* dst)
{
        uint32_t x[2];
        x[0] = src >>32;
        x[1] = 0xFFFFFFFFLL & src;

        sprintf(dst, "%08x%08x", x[0], x[1]);
}

void uint32toR17Str(uint32_t src, char dst[], int digit)
{
        int i;
        dst[digit] = '\0';
        for(i=0; src!=0 && i<digit;++i)
        {
                dst[digit-1-i] = numtoR17(src % 17);
                src /= 17;
        }

        for( ; i<digit; ++i)
        {
                dst[digit-1-i] = '0';
        }
}

uint32_t r17toNum(char c)
{

        if(isdigit(c))
        {
                return c - '0';
        }
        else if(isupper(c))
        {
                return (c - 'A') + 10U;
        }
        else if(islower(c))
        {
                return (c - 'a') + 10U;
        }
        else
        {
                printf("r17toNum:It's not Hept Number\n");
                return 0;
        }
}

uint32_t r17toUint32(char src[])
{
        const size_t length = strlen(src);
        
        if(length < 1) return 0;

        uint32_t rtnVal = 0;
        uint32_t rn = 1; //for base=17, digit=length calcuration
        for(int i=0; i<length-1; ++i)
        {
                rn *= 17;
        }
        //1文字ずつuint32_t化
        for(int i=0; i<length; ++i)
        {
                int num = r17toNum(src[i]);
                rtnVal += num * rn;
                rn /= 17;
        }

        return rtnVal;

}

