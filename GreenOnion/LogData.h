#pragma once
#include <string>
#include <ctime>
#include <chrono>

namespace greenonion::system
{
	enum class LOGLEVEL
	{
		LOG_DEBUG,
		LOG_WARNING,
		LOG_ERROR,
	};

	class LogData
	{
	public:
		LogData() :m_logData(), m_logLevel(LOGLEVEL::LOG_DEBUG)
		{
			m_time = GetCurrentTime();
			m_logData.append(m_time);
			m_logData.append(" ");
		}
	
	private:
		LOGLEVEL m_logLevel;
		std::string m_logData;
		std::string m_time;
	public:
		template<typename T>
		friend LogData& operator <<(LogData& log, T arg)
		{
			log << arg;
			return log;
		}

		std::string to_string() const
		{
			return m_logData;
		}

	private:

		std::string GetCurrentTime() const
		{
			time_t now = time(0);
			struct tm tstruct;
			char buf[80];
			localtime_s(&tstruct, &now);
			strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
			std::string str_time(buf);
			return str_time;
		}

		friend LogData& operator <<(LogData& log, const LOGLEVEL level)
		{
			std::string str_level;
			switch (level)
			{
			case LOGLEVEL::LOG_DEBUG:
				str_level.append("[DEBUG] : ");
				break;

			case LOGLEVEL::LOG_WARNING:
				str_level.append("[WARNING] : ");
				break;

			case LOGLEVEL::LOG_ERROR:
				str_level.append("[ERROR] : ");
				break;
			}
			log << str_level;
			return log;
		}

		friend LogData& operator <<(LogData& log, const std::string& val)
		{
			log.m_logData.append(val);
			return  log;
		}

		friend  LogData& operator <<(LogData& log, const char* val)
		{
			log.m_logData.append(val);
			return  log;
		}

		friend  LogData& operator <<(LogData& log, bool val)
		{
			std::string val_string = std::to_string(val);
			log.m_logData.append(val_string);
			return  log;
		}

		friend  LogData& operator <<(LogData& log, uint8_t val)
		{
			std::string val_string = std::to_string(val);
			log.m_logData.append(val_string);
			return  log;
		}

		friend  LogData& operator <<(LogData& log, uint16_t val)
		{
			std::string val_string = std::to_string(val);
			log.m_logData.append(val_string);
			return  log;
		}

		friend  LogData& operator <<(LogData& log, uint32_t val)
		{
			std::string val_string = std::to_string(val);
			log.m_logData.append(val_string);
			return  log;
		}

		friend  LogData& operator <<(LogData& log, uint64_t val)
		{
			std::string val_string = std::to_string(val);
			log.m_logData.append(val_string);
			return  log;
		}

		friend  LogData& operator <<(LogData& log, int8_t val)
		{
			std::string val_string = std::to_string(val);
			log.m_logData.append(val_string);
			return  log;
		}

		friend  LogData& operator <<(LogData& log, int16_t val)
		{
			std::string val_string = std::to_string(val);
			log.m_logData.append(val_string);
			return  log;
		}

		friend  LogData& operator <<(LogData& log, int32_t val)
		{
			std::string val_string = std::to_string(val);
			log.m_logData.append(val_string);
			return  log;
		}

		friend  LogData& operator <<(LogData& log, int64_t val)
		{
			std::string val_string = std::to_string(val);
			log.m_logData.append(val_string);
			return  log;
		}

	};

}