#include"db-create.hpp"
#include<iostream>
#include<thread>
#include<unistd.h>
/*
「検索用バイナリファイル出力」
起動後（416消費後）の8個の針の並びと初期Seedの組み合わせをファイルへ分割して書き込む。
針の並びの最初の2個がXXとなる針,初期SeedペアはXX.binというファイルに保存される。
残りの針の並び6個を17進数と見て32bit符号なし整数型にエンコードしTickSeed構造体にSeedとのペアで格納、バイナリファイルとして書き込む。
例：(針、Seed)=(0BEEFBAG, 0xB98AB4F3)について、TickSeed構造体に(tick=21124352, seed=3112875251)として格納し0B.binへバイナリで書き込み
*/

int main()
{
	try
	{
	DBCreator dbc;
	std::thread th(std::ref(dbc));

	th.detach();
	for(;;)
	{
		sleep(1);
		
		printf("%.2lf %%\n", 100.0*dbc.getProgress());

		if(dbc.getState()==DBCreator::Finished) 
		{
			break;
		}
		else if(dbc.getState()==DBCreator::Error)
		{
			std::cout << "Error:" << dbc.getErrString() << "\n";
			break;
		}
	}


	}
	catch(std::exception& ex)
	{
		std::cout << ex.what() << "\n";
	}

}
