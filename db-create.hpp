#pragma once
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

#include"threadSafeWorker.hpp"


class DBCreator : public threadSafeWorker
{
public:
	DBCreator()
	:threadSafeWorker(), m_errStr("o"), m_abortFlag(false) 
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




private:
	std::recursive_mutex m_mutex;
	struct Thread_aborted{};
	void create();
	void check_abort();

	std::string m_errStr;
	std::atomic_bool m_abortFlag;

};
