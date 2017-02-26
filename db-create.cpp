#include"db-create.hpp"
#pragma warning(disable : 4996)

void DBCreator::operator()()
{
	try
	{	
	m_state = Processing;

	create();

	if(m_state==Error)
	{
		//If create() made Error, finish thread under (m_state == Error);
		return;
	}

	m_state = Finished;
	}
	catch(Thread_aborted& e)
	{
		m_state = Error;
		setErrString(std::string("Aborted."));
	}
}

void DBCreator::create()
{
        sfmt_t sfmt;

        const uint32_t SEEK_START = 0x00000000;         //出力開始Seed
        const uint32_t SEEK_MAX = 0xFFFFFFFFU;          //出力最大seed 
        uint32_t seed;
        
        //進捗表示用
        const uint32_t split = 0xFFFFU;
        const uint32_t unit = (SEEK_MAX - SEEK_START)/split;
        int per = 0;
        
        //針、Seedの組み合わせ保存ファイル(db-sortでソートの後、seedのみ保存することを想定)
        //fps[x] は ファイルhept(x).bin 例：fps[112]は6A.bin

	std::vector<std::unique_ptr<FILE, decltype(&fclose)>> fps;
        for(int i=0; i<289; ++i)
        {
		FILE* tmpFp = fopen(dbFilename(i).c_str(), "wb");		
                if(tmpFp == NULL) 
                {
                        setErrString(strerror(errno));
			m_state = Error;
			return;
                }
		else
		{
			fps.push_back(std::unique_ptr<FILE, decltype(&fclose)>(tmpFp, fclose));
		}
                
        }

        //fileごとに書き込んだ要素数をカウント
        uint32_t fileWCount[289] = {0U};

        for(seed = SEEK_START; ; ++seed)
        {
                //進捗表示用
                if(seed % unit==0)
                {
			//進捗を更新
			m_progress = 1.0*per/split;
                        //printf("Creating...%d/%d\n", per, split);
                        ++per;
                
			//Abortのチェック・発動
			check_abort();	
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
                        tmp6TickToUint32 += result % 17 * rn;
                        rn /= 17;
                }
                
                //TickSeed構造体に結果を格納
                TickSeed tmpTs;
                tmpTs.tick = tmp6TickToUint32;
                tmpTs.seed = seed;
                
                //ファイルにTickSeed構造体1つ書き込み
                const int fileOK = fwrite((void*)&tmpTs, sizeof(TickSeed), 1, fps[fileIdx].get()); 
                if(fileOK != 1) printf("fileWrite failed... %d\n", fileIdx);
                fileWCount[fileIdx] += fileOK;

                if(seed == SEEK_MAX) break;
        }
}

void DBCreator::abort()
{
	m_abortFlag = true;
}

void DBCreator::check_abort()
{
	if(m_abortFlag)
	{
		throw Thread_aborted();
	}
}
