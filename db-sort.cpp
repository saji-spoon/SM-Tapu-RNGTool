#include"db-sort.hpp"


void DBSort::operator()()
{       
	m_state = Processing;
	bool hasError = false;
	for (int i=0; i<289; ++i)
	{
		m_progress = 1.0*i/289.0;

		std::string filename = dbFilename(i);
		std::unique_ptr<FILE, decltype(&fclose)> frp(fopen(filename.c_str(), "rb"), fclose);
		if(!frp) 
		{
			hasError = true;
			continue;
		}
		

		char tmpFilename[30];
		strncpy(tmpFilename, filename.c_str(), 29);
		off_t size = fileSize(tmpFilename) / sizeof(TickSeed);

		//針、Seedの組み合わせ
		std::unique_ptr<TickSeed, decltype(&free)> ts((TickSeed*)malloc(sizeof(TickSeed)*size), free);
		uint32_t tsIdx = 0;


		tsIdx = fread((void*)ts.get(), sizeof(TickSeed), size, frp.get());
		      
		qsort(ts.get(), tsIdx, sizeof(TickSeed), tsComp);
		
		//close file
		frp.reset();
		
		std::unique_ptr<FILE, decltype(&fclose)> fwp(fopen(filename.c_str(), "wb"), fclose);
		if(!fwp) 
		{
			hasError = true;
			continue;
		}

		for (size_t i=0; i<tsIdx; ++i)
		{
			fwrite(&(ts.get()[i].seed), sizeof(uint32_t), 1, fwp.get()); 
		}
		

	}
	m_state = (hasError ? Error : Finished);


}


