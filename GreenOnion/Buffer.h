#pragma once
#include <cstdint>
#include <memory>

namespace greenonion::system
{
	class Buffer
	{
	public:
		Buffer():
		m_buffer(new uint8_t[DEFAULT_SIZE]),m_capacity(DEFAULT_SIZE),m_offset(0)
		{
			Clear();
		}

		Buffer(const size_t size):
		m_buffer(new uint8_t[size]), m_capacity(size), m_offset(0)
		{
			 
		} 

		Buffer(const Buffer& buffer):
		m_buffer(new uint8_t[buffer.m_capacity]), m_capacity(buffer.m_capacity),m_offset(buffer.m_offset)
		{
			memcpy_s(m_buffer, m_capacity, buffer.m_buffer, m_offset);
		}

		Buffer(const Buffer&& buffer)
		{
			
		}

	public:
		constexpr static size_t DEFAULT_SIZE = 1024;
		void Clear()
		{
			memset(m_buffer, 0, m_capacity);
		}

	private:
		uint8_t* m_buffer;

		size_t m_capacity;
		size_t m_offset;
	};
}
