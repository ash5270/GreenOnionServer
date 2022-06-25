#pragma once
#include "Buffer.h"

namespace greenonion::system
{
	class CricularBuffer : public Buffer
	{
	public:
		CricularBuffer() :Buffer(), m_writeOffset(0)
		{

		}

		CricularBuffer(const size_t& size) :Buffer(size), m_writeOffset(0)
		{

		}

		~CricularBuffer() override
		{

		}

	public:
		bool push_back(const uint8_t* data, const size_t& size) override
		{
			return Write(data, size);
		}

		bool pop(uint8_t* data, const size_t& size) override
		{
			return Read(data, size);
		}

		size_t GetWriteOffset() const
		{
			return m_writeOffset;
		}


	private:
		bool Write(const uint8_t* data, const size_t& size)
		{
			if (size < 0 || size + m_offset > m_capacity)
			{
				printf("size : %llu, write size : %llu, write : %llu, read : %llu\n", m_offset, size + m_offset, m_writeOffset, m_readOffset);
				return false;
			}
			//남아있는 사이즈 
			const size_t remain_size = m_capacity - m_writeOffset;
			//그냥 넣기
			if (remain_size >= size)
			{
				memcpy_s(m_buffer + m_writeOffset, size, data, size);
				m_writeOffset += size;
				if (m_writeOffset == m_capacity)
					m_writeOffset = 0;
			}
			else
			{
				//남은 뒤쪽에 넣어주고
				memcpy_s(m_buffer + m_writeOffset, remain_size, data, remain_size);
				//나머지는 앞쪽에 넣어줌
				const size_t back_remain_size = size - remain_size;
				memcpy_s(m_buffer, back_remain_size, data + remain_size, back_remain_size);
				m_writeOffset = back_remain_size;
			}
			m_offset += size;
			return true;
		}

		bool Read(uint8_t* data, const size_t& size)
		{
			if (size <= 0 || m_offset <= 0)
				return false;
			//그냥 읽기
			const size_t remain_size = m_capacity - m_readOffset;
			if (remain_size >= size)
			{
				memcpy_s(data, size, m_buffer + m_readOffset, size);
				m_readOffset += size;
				if (m_readOffset == m_capacity)
					m_readOffset = 0;
			}
			//넘어가는 데이터 구해오기
			else
			{
				memcpy_s(data, remain_size, m_buffer + m_readOffset, remain_size);
				const size_t back_remain_size = size - remain_size;
				memcpy_s(data + remain_size, back_remain_size, m_buffer, back_remain_size);
				m_readOffset = back_remain_size;
			}
			m_offset -= size;

			return true;
		}

	protected:
		//write 
		size_t m_writeOffset;
	};
}
