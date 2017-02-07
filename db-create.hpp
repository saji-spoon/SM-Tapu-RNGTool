#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"util.hpp"
#include"tickSeed.hpp"
#include<iostream>
#include<mutex>
#include<unistd.h>
extern "C"
{
#include"SFMT/SFMT.h"
}

class DBCreater
{
public:
	enum State
	{
		None,
		Processing,
		Finished,
		Error
	};

	DBCreater()
	:m_progress(0.0), m_state(None)
	{}

	void setProgress(double p)
	{
		std::lock_guard<std::recursive_mutex> lock(m_mutexP);
		m_progress = p;
	}
	double getProgress()
	{
		std::lock_guard<std::recursive_mutex> lock(m_mutexP);
		return m_progress;
	}
	void setState(State s)
	{
		std::lock_guard<std::recursive_mutex> lock(m_mutexS);
		m_state = s; 
	}
	State getState()
	{
		std::lock_guard<std::recursive_mutex> lock(m_mutexS);
		return m_state;
	}

	void operator()();

	void reset()
	{
		std::lock_guard<std::recursive_mutex> lock1(m_mutexS);
		std::lock_guard<std::recursive_mutex> lock2(m_mutexP);
		m_progress = -1.0;
		m_state = None;
	}

	std::string m_errStr;
private:
	double m_progress;
	State m_state;
	std::recursive_mutex m_mutexP;
	std::recursive_mutex m_mutexS;
};
