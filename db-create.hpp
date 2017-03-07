#pragma once
#include<iostream>
#include<time.h>
#include<atomic>
#include<mutex>
#include<errno.h>
#include<memory>
#include<vector>
#include"util.hpp"
#include"tickSeed.hpp"
extern "C"
{
#include"SFMT/SFMT.h"
}

#include"ThreadSafeWorker.hpp"


class DBCreator : public ThreadSafeWorker
{
public:
	DBCreator()
	:ThreadSafeWorker(), m_errStr("o"), m_abortFlag(false) 
	{
	}

	void operator()()override;

	void abort();

    bool isAborted() 
    {
        return m_state == Error && m_abortFlag;
    }

	std::string getErrString()
	{
		std::lock_guard<std::recursive_mutex> lock(m_mutex);
		return m_errStr;
	
	}
	
	void setErrString(std::string str)
	{
		std::lock_guard<std::recursive_mutex> lock(m_mutex);
		m_errStr = str;
		
	}

    //m_mutex is not moved
    DBCreator(DBCreator && rv) noexcept 
    {
        *this = std::move(rv);
    }

    DBCreator& operator=(DBCreator&& rv) noexcept
    {
        if (this != &rv) 
        {
            m_errStr = std::move(rv.m_errStr);
            m_abortFlag = rv.m_abortFlag.load();
            ThreadSafeWorker::operator=(std::move(rv));

        }

        return *this;
    }




private:
	std::recursive_mutex m_mutex;
	struct Thread_aborted{};
	void create();
	void check_abort();

	std::string m_errStr;
	std::atomic_bool m_abortFlag;

};
