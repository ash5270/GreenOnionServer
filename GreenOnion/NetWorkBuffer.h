#pragma once
#include "CricularBuffer.h"
#include <atomic>

namespace greenonion::system
{
	class NetWorkBuffer : public Buffer
	{
	public:
		NetWorkBuffer() :Buffer(), m_writeOffset(0), m_readOffset(0), m_waterMark(m_capacity),m_size(0)
		{

		}

		NetWorkBuffer(size_t size) : Buffer(size), m_writeOffset(0), m_readOffset(0), m_waterMark(m_capacity),m_size(0)
		{

		}

		~NetWorkBuffer() override
		{

		}

	public:

		int GetCurrentIndex()
		{
			return m_writeOffset;
		}

		bool push_back(const uint8_t* data, const size_t& size) override
		{
			//사이즈가 0이랑 같거나 작으면 리턴
			if (size <= 0)
				return false;
			const int remain_size = m_capacity - m_writeOffset;
			//뒤에 공간이 안나올때 
			if (remain_size < size)
			{
				//앞쪽에 데이터 확인후 집어 넣어주기
				if (m_readOffset > size)
				{
					//여기서 넣어줘야함
					m_waterMark.store(m_writeOffset);
					memcpy_s(m_buffer, size, data, size);
					m_writeOffset = size;
				}
				else
				{
					//아예 공간 자체가 없다.
					printf("over size \n");
					return false;
				}
			}
			//공간이 나올때 
			else
			{
				//여기서 데이터 넣어줌
				//여기서 read offset이랑도 비교해서 넣기 없다면 false
				if(m_readOffset> m_writeOffset)
				{
					const int read_sub_write = m_readOffset - m_writeOffset;
					if (read_sub_write < size)
					{
						printf("over size2 \n");
						return false;
					}
				}

				memcpy_s(m_buffer+m_writeOffset, size, data, size);
				m_writeOffset += size;
			}
			m_size += size;	
			return true;
		}

		bool pop(uint8_t* data, const size_t& size) override
		{
			if (m_size <= 0)
				return  false;

			if(m_readOffset <= m_writeOffset)
			{
				memcpy_s(data, size, m_buffer + m_readOffset, size);
				m_readOffset += size;
				m_size -= size;
				if(m_readOffset>=m_waterMark)
				{
					m_readOffset = 0;
					m_waterMark = m_capacity;
				}

				return true;
			}

			return  false;
		}

		void skip_pop(const size_t& size)
		{
			m_readOffset += size;
			m_size -= size;
			if (m_readOffset >= m_waterMark)
			{
				m_readOffset = 0;
				m_waterMark = m_capacity;
			}
		}

		int GetSize() const override 
		{
			return m_size.load();
		}

		int RemainSize()const
		{
			return m_capacity - m_size.load();
		}

	public:
		std::atomic_int32_t m_readOffset;
		std::atomic_int32_t m_writeOffset;
		std::atomic_int32_t m_waterMark;

		std::atomic_int32_t m_size;
		//예약을 하고 거기 위치에 있는 포인터에서 꺼내와 씀

	};
}

