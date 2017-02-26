#pragma once
//#include<unistd.h>
#include<atomic>
extern "C"
{
#include"SFMT/SFMT.h"
}

class threadSafeWorker 
{
public:
	enum State
	{
		None,
		Processing,
		Finished,
		Error
	};

	threadSafeWorker()
	:m_progress(0.0), m_state(None) 
	{}

	virtual void operator()() = 0;

	std::atomic<double>& getProgress()
	{
		return m_progress;
	}

	std::atomic<State>& getState()
	{
		return m_state;
	}

protected:
	std::atomic<double> m_progress;
	std::atomic<State> m_state;
};
