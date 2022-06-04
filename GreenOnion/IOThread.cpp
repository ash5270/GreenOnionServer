#include "IOThread.h"

greenonion::system::IOThread::IOThread(uint8_t index):m_ioContext(),
m_ioGuard(boost::asio::make_work_guard(m_ioContext)),
m_index(index)
{
}

greenonion::system::IOThread::~IOThread()
{
	Stop();
}

void greenonion::system::IOThread::Start()
{
	m_ioThread = std::thread([&]() { m_ioContext.run(); });
}

bool greenonion::system::IOThread::Join()
{
	if(m_ioThread.joinable()==true)
	{
		m_ioThread.join();
		return true;
	}

	return false;
}

void greenonion::system::IOThread::Stop()
{
	m_ioGuard.reset();
	m_ioContext.stop();
	Join();
}
