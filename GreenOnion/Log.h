#pragma once
#include "LogData.h"
namespace greenonion::system
{
	template<typename Arg1, typename... Args>
	LogData CreateLogData(LOGLEVEL level, const Arg1& arg, const Args&... args)
	{
		LogData log_data;
		log_data << level << arg;
		return CreateLogData(log_data, args...);;
	}

	template<typename Arg1>
	LogData CreateLogData(LOGLEVEL level, const Arg1& arg)
	{
		LogData log_data;
		log_data << level << arg;
		return log_data;
	}

	template<typename Arg1, typename... Args>
	LogData& CreateLogData( LogData& log_data, const Arg1& arg, const Args&... args)
	{
		log_data << arg;
		return CreateLogData(log_data, args...);
	}
	template<typename Arg1>
	LogData& CreateLogData( LogData& log_data, const Arg1& arg)
	{
		log_data << arg;
		return log_data;
	}
}

