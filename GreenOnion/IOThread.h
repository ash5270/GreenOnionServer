#pragma once
#include "CommonHeader.h"

namespace greenonion::system
{
	class IOThread final
	{
		using IO_CONTEXT = boost::asio::io_context;
		using IO_GUARD = boost::asio::executor_work_guard<IO_CONTEXT::executor_type>;
	public:
		IOThread() = default;
		IOThread(uint8_t index);
		~IOThread();

	public:
		void Start();
		bool Join();
		void Stop();

		IO_CONTEXT& GetContext() { return m_ioContext; }

	private:
		IO_CONTEXT m_ioContext;;
		IO_GUARD m_ioGuard;
		std::thread m_ioThread;
		uint8_t m_index;
	};

}

