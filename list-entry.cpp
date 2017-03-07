#include"list.hpp"

int main(int argc, char* argv[])
{
        if(argc < 2 || strlen(argv[1]) < 8)
        {
                printf("Usage: %s 1234FEDC\n", argv[0]);
                printf("Seed(32 bit) is required.\n");
                return 1;
        }

	uint32_t seed;

	std::stringstream ss;
	ss << argv[1];
	ss >> std::hex >> seed;

	auto rd = getRandDataList(seed, 1000);
	saveFile(rd);

	auto pkst = getPokeStatusList(rd, rd.size());
	saveFile(pkst);

		
        
        printf("Lists created. See ./lists/\n");



        return 0;
}
