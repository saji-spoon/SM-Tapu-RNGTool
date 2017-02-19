#include"db-sort.hpp"
#include<iostream>
#include<thread>
#include<unistd.h>
/*
*/

int main()
{
	try
	{
	DBSort dbs;
	std::thread th(std::ref(dbs));

	th.detach();
	for(;;)
	{
		printf("%.2lf %%\n", 100.0*dbs.getProgress());

		if(dbs.getState()==DBSort::Finished) 
		{
			break;
		}
		else if(dbs.getState()==DBSort::Error)
		{
			std::cout << "Error:" << "\n";
			break;
		}
	}


	}
	catch(std::exception& ex)
	{
		std::cout << ex.what() << "\n";
	}

}
