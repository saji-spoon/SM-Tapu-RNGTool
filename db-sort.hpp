#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string>
#include<iostream>
#include<memory>
#include"util.hpp"
#include"tickSeed.hpp"
#include"threadSafeWorker.hpp"

class DBSort : public ThreadSafeWorker
{
public:
	DBSort():ThreadSafeWorker()
	{
	}

	void operator()()override;

};
