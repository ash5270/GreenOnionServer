#pragma once
#include "CricularBuffer.h"
#include <mutex>
#include <atomic>



namespace greenonion::system
{
	class NetWorkBuffer 
	{
	public:
		NetWorkBuffer() : m_buffer(new uint8_t[1024]),m_offset(0),m_readOffset(0),m_capacity(1024),m_writeOffset(0)
		{
			m_is_full = false;
			m_lastOffset = 1024;
		}

		NetWorkBuffer(size_t size) : m_buffer(new uint8_t[size]), m_offset(0), m_readOffset(0), m_capacity(size), m_writeOffset(0), m_lastOffset(size)
		{
			m_is_full = false;
		}

		~NetWorkBuffer() 
		{

		}

	public:
		uint8_t* GetBuffer() 
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			return m_buffer;
		}

		int32_t GetBufferSize()
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			return m_capacity;
		}

		int32_t GetSize()
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			return m_offset;
		}

		int32_t GetReadOffset()
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			return m_readOffset;
		}

		int32_t GetWriteOffset()
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			return m_writeOffset;
		}


		bool push_back(const uint8_t* data, const size_t& size) 
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (size < 0 || size + m_offset > m_capacity )
			{
				//GO_LOG(LOGLEVEL::LOG_DEBUG, "m_offset : ", (int)m_offset);
				return false;
			}
			//남아있는 사이즈 
			const size_t remain_size = m_capacity - m_writeOffset;
			//그냥 넣기
			if (remain_size >= size)
			{
				memcpy_s(m_buffer + m_writeOffset, size, data, size);
				m_writeOffset += size;
				m_offset += size;
			}
			else
			{
				//뒤쪽에 남아있는 사이즈보다 들어온 사이즈가 클 경우
				if (m_readOffset > size)
				{
					m_lastOffset = m_writeOffset;
					memcpy_s(m_buffer, size, data, size);
					m_writeOffset = size;
				}
				else
				{
					return false;
				}
			}


			return true;
		}

		bool pop(uint8_t* data, const size_t& size) 
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			if (size <= 0 || m_offset <= 0)
				return false;
			//그냥 읽기
			const size_t remain_size = m_capacity - m_readOffset;
			if (remain_size >= size)
			{
				memcpy_s(data, size, m_buffer + m_readOffset, size);
				m_readOffset += size;
			}
			//넘어가는 데이터 구해오기
			else
			{
				//남아있는 사이즈보다 사이즈가 큰걸 읽을라고 할경우
				if (m_writeOffset > size)
				{
					memcpy_s(data, size, m_buffer, size);
					m_readOffset = size;
				}
				else
				{
					return false;
				}
			}
			m_offset -= size;
			if (m_offset < 0)
			{
				printf("sc");
			}
			return true;
		}

		bool pop_size(const size_t& size)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (size <= 0 || m_offset <= 0)
				return false;

			const size_t remain_size = m_capacity - m_readOffset;

			if(m_readOffset+size >= m_lastOffset)
			{
				m_readOffset = 0;
			}else
			{
				if (remain_size >= size)
				{
					m_readOffset += size;
				}
				else
				{
					m_readOffset = size;
				}
			}
			m_offset -= size;
			if (m_offset < 0)
			{
				printf("buffer size : %d ,read : %d ,write : %d , send_size : %llu \n",m_offset,m_readOffset,m_writeOffset,size);
			}
			return true;
		}

		bool GetCurrentIndex(size_t& data, const size_t& size) const
		{
			if (m_capacity < size + m_offset)
				return false;
			//인덱스만 들고 있어도 되니깐 인덱스만 가지고 있음
			data = m_writeOffset;
			return true;
		}

		void SetSize(size_t size)
		{
			
		}
		int32_t m_lastOffset;


	private:
		std::mutex m_mutex;
		bool m_is_full;

		uint8_t* m_buffer;


		int32_t m_capacity;
		int32_t m_writeOffset;
		int32_t m_readOffset;
		int32_t m_offset;

		//보낼만큼의 사이즈 
	};
}

