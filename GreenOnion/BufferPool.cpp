#include "BufferPool.h"

greenonion::system::BufferPool::BufferPool(BUFFERTYPE type, int pool_count) : m_pool_count(pool_count)
{
	switch (type)
	{
	case BUFFERTYPE::BUFFER:
		InitBaseBuffer();
		break;

	case BUFFERTYPE::NETWORK:
		InitNetWorkBuffer();
		break;

	case BUFFERTYPE::CRICULAR:
		InitCricularBuffer();
		break;
	}
}

greenonion::system::BufferPool::~BufferPool()
{

}

void greenonion::system::BufferPool::InitBaseBuffer()
{
	for (int i = 0; i < m_pool_count; i++)
	{
		m_buffers.push_back(std::make_shared<Buffer>());
	}
}

void greenonion::system::BufferPool::InitCricularBuffer()
{
	for (int i = 0; i < m_pool_count; i++)
	{
		m_buffers.push_back(std::make_shared<CricularBuffer>());
	}
}

void greenonion::system::BufferPool::InitNetWorkBuffer()
{
	for (int i = 0; i < m_pool_count; i++)
	{
		//m_buffers.push_back(std::make_shared<NetWorkBuffer>());
	}
}
