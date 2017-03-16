#include "db-search.hpp"

std::vector<TickSeed> searchDB(const std::vector<uint64_t>& ticks)
{
    assert(ticks.size() >= 8);

    std::string filename = "./db/";
    filename += numtoR17(ticks[0]);
    filename += numtoR17(ticks[1]);
    filename += ".bin";

    std::cout << filename << "\n";

    std::unique_ptr<FILE, decltype(&fclose)> fp(fopen(filename.c_str(), "rb"), fclose);
    if (!fp)
    {
        perror("file error(fp)");
        exit(EXIT_FAILURE);
    }

    off_t size = fileSize(filename.c_str()) / sizeof(uint32_t);

    //seedのみファイルから読み込む
    std::unique_ptr<uint32_t, decltype(&free)> sds((uint32_t*)malloc(sizeof(uint32_t)*size), free);
    if (!sds)
    {
        perror("memory error(sds)");
        exit(EXIT_FAILURE);
    }
    //計測
    clock_t start = clock();

    uint32_t readSize = fread((void*)sds.get(), sizeof(uint32_t), size, fp.get());

    std::cout << "readSize:" << readSize << "\n";

    std::vector<uint32_t> seeds(sds.get(), sds.get() + readSize);

    clock_t end = clock();

    printf("read:%lf[s]\n", 1.0*(end - start) / CLOCKS_PER_SEC);

    start = clock();

    std::vector<uint64_t> first8Ticks;

    std::copy(ticks.begin(), ticks.begin() + 8, std::back_inserter(first8Ticks));

    uint32_t key = tickToTickkey(first8Ticks);

    //search for seed matches input clockhands as key 
    auto it = std::lower_bound(seeds.begin(), seeds.end(), key, [](const uint32_t e, const uint32_t val) {return seedToTickkey(e)<val; });
    bool found = (seedToTickkey(*it) == key);

    end = clock();
    printf("search:%lf[s]\n\n", 1.0*(end - start) / CLOCKS_PER_SEC);

    std::vector<TickSeed> results(0);

    if (found)
    {
        for (; it != seeds.end(); ++it)
        {
            if (seedToTickkey(*it) != key) break;
            results.push_back({ seedToTickkey(*it), *it });
        }
    }

    return results;



}
