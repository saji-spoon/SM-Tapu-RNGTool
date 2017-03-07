#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string>
#include<iostream>
#include<memory>
#include"util.hpp"
#include"tickSeed.hpp"
#include"threadSafeWorker.hpp"

class DBSort : public threadSafeWorker
{
public:
	DBSort():threadSafeWorker()
	{
	}

	void operator()()override;

};
