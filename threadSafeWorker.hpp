#pragma once
//#include<unistd.h>
#include<atomic>
extern "C"
{
#include"SFMT/SFMT.h"
}

class ThreadSafeWorker 
{
public:
	enum State
	{
		None,
		Processing,
		Finished,
		Error
	};

	ThreadSafeWorker()
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

    ThreadSafeWorker(ThreadSafeWorker&& rv) noexcept
    {
        *this = std::move(rv);
    }

    ThreadSafeWorker& operator=(ThreadSafeWorker&& rv) 
    {
        if (this != &rv)
        {
            m_progress = rv.m_progress.load();
            m_state = rv.m_state.load();
        }

        return *this;
    }



protected:
	std::atomic<double> m_progress;
	std::atomic<State> m_state;
};
