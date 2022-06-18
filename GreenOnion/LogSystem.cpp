#include "LogSystem.h"
#include <chrono>
#include <iostream>

greenonion::system::LogSystem greenonion::system::LogSystem::instance;

greenonion::system::LogSystem::LogSystem()
{
}

void greenonion::system::LogSystem::InitSystem()
{
}

void greenonion::system::LogSystem::StartSystem()
{
	//m_logThead = std::thread(&LogSystem::UpdateSystem,this);
}

void greenonion::system::LogSystem::UpdateSystem()
{
	while(true)
	{
		if(!m_logQueue.empty())
		{
			LogData log_string = m_logQueue.front();
			m_logQueue.pop();

			std::cout << log_string.to_string() << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}
