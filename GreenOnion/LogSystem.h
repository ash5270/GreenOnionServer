#pragma once
#include <cstdint>
#include <string>
#include <queue>
#include <thread>
#include "Log.h"
#include "LogData.h"

namespace greenonion::system
{
	#define GO_LOG(log_level,...) //LogSystem::Instance().LogAppend(CreateLogData(log_level,##__VA_ARGS__))

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

	public:
		LogSystem(const LogSystem& log) = delete;
		void operator=(const LogSystem&) = delete;

		static LogSystem& Instance()
		{
			return instance;
		}

		void LogAppend(const LogData& log)
		{
			m_logQueue.push(log);
		}

	public:
		void InitSystem();
		void StartSystem();
		void UpdateSystem();

	};


	
}


