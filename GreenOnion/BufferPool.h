#pragma once
#include "NetWorkBuffer.h"
#include<vector>
namespace greenonion::system
{
	class BufferPool 
	{
	public:
		enum class BUFFERTYPE
		{
			BUFFER,
			CRICULAR,
			NETWORK

		};
	public:
		BufferPool(BUFFERTYPE type, int pool_count);
		~BufferPool();

	private:
		void InitBaseBuffer();
		void InitCricularBuffer();
		void InitNetWorkBuffer();
		
	private:
		std::vector<std::shared_ptr<Buffer>> m_buffers;
		uint16_t m_pool_count;

	};
}
  