#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"SFMT/SFMT.h"
#include"util.h"
#include"tickSeed.h"

/*
「検索用バイナリファイル出力」
起動後（416消費後）の8個の針の並びと初期Seedの組み合わせをファイルへ分割して書き込む。
針の並びの最初の2個がXXとなる針,初期SeedペアはXX.binというファイルに保存される。
残りの針の並び6個を17進数と見て32bit符号なし整数型にエンコードしTickSeed構造体にSeedとのペアで格納、バイナリファイルとして書き込む。
例：(針、Seed)=(0BEEFBAG, 0xB98AB4F3)について、TickSeed構造体に(tick=21124352, seed=3112875251)として格納し0B.binへバイナリで書き込み
全ファイル書き込み終了後、各ファイルに書き込まれたTickSeed構造体の数を標準出力へ出力する
*/

int main()
{
        sfmt_t sfmt;
        const uint32_t SEEK_START = 0x00000000;         //出力開始Seed
        const uint32_t SEEK_MAX = 0xFFFFFFFFU;          //出力最大seed 
        uint32_t seed;
        
        //進捗表示用
        const uint32_t split = 256U;
        const uint32_t unit = (SEEK_MAX - SEEK_START)/split;
        int per = 0;
        
        //針、Seedの組み合わせ保存ファイル
        //fp[x] は ファイルhept(x).bin 例：fp[112]は6A.bin
        FILE* fp[289];
        char fileID[4]; 
        char filename[20];
        for(int i=0; i<289; ++i)
        {
                uint32toR17Str(i, fileID, 2);
                sprintf(filename, "./db/%s.bin", fileID);                
                if((fp[i] = fopen(filename, "wb")) == NULL ) 
                {
                        perror("file error\n");
                        exit(EXIT_FAILURE);
                }
                
        }

        //fileごとに書き込んだ要素数をカウント
        uint32_t fileWCount[289] = {0U};

        for(seed = SEEK_START; ; ++seed)
        {
                //進捗表示用
                if(seed % unit==0)
                {
                        printf("Creating...%d/%d\n", per, split);
                        ++per;
                }

                sfmt_init_gen_rand(&sfmt, seed);

                //416 frame advances when the game starts.
                for(int i=0; i<417; ++i)
                {
                        sfmt_genrand_uint64(&sfmt);
                }
                
                int fileIdx = 0;
                //頭2文字はファイル振り分け
                //1文字目
                uint64_t result = sfmt_genrand_uint64(&sfmt);
                fileIdx += result%17 * 17;
                //2文字目
                result = sfmt_genrand_uint64(&sfmt);
                fileIdx += result%17;
        
                //ファイル名に使った2文字のあとの残りの6文字を17進数と見てtmp6TickToUint32に格納
                uint32_t tmp6TickToUint32 = 0; //計算結果格納用
                uint32_t rn = 17*17*17*17*17; //for base=17, digit=6 calcuration
                for(int i=0; i<6; ++i)
                {
                        uint64_t result = sfmt_genrand_uint64(&sfmt);
                        //uint64toHex(result, str);
                        //printf("%s", inttoR17(result%17));
                        tmp6TickToUint32 += result % 17 * rn;
                        rn /= 17;
                }
                
                //TickSeed構造体に結果を格納
                TickSeed tmpTs;
                tmpTs.tick = tmp6TickToUint32;
                tmpTs.seed = seed;
                
                //ファイルにTickSeed構造体1つ書き込み
                const int fileOK = fwrite((void*)&tmpTs, sizeof(TickSeed), 1, fp[fileIdx]); 
                if(fileOK != 1) printf("fileWrite failed... %d\n", fileIdx);
                fileWCount[fileIdx] += fileOK;

                if(seed == SEEK_MAX) break;
        }

        //ファイルポインタの解放
        for(int i=0; i<289; ++i)
        {
                //char tmpStr[5];
                //uint32toR17Str(i, tmpStr, 2);
                //printf("%s.bin Written:%u\n", tmpStr, fileWCount[i]);
                fclose(fp[i]);
        }

        return 0;
}
