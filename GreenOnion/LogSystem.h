#pragma once
#include <queue>
#include <thread>
#include "Log.h"
#include "LogData.h"
#include <mutex>

namespace greenonion::system
{
	#define GO_LOG(log_level,...) LogSystem::Instance().LogAppend(CreateLogData(log_level,##__VA_ARGS__))

	class LogSystem
	{
	private:
		LogSystem();


	private:
	
		std::queue<LogData> m_logQueue;

		//static value
		static LogSystem instance;

		//thread
		std::thread m_logThead;

		//mutex
		std::mutex m_mutex;
	public:
		LogSystem(const LogSystem& log) = delete;
		void operator=(const LogSystem&) = delete;

		static LogSystem& Instance()
		{
			return instance;
		}

		void LogAppend(const LogData& log)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_logQueue.push(log);
		}

	public:
		void InitSystem();
		void StartSystem();
		void UpdateSystem();

	};


	
}


