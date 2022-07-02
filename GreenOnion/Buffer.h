#pragma once
#include <cstdint>
#include <string>
#include <memory>
namespace greenonion::system
{
	class Buffer
	{
	public:
		//기본 생성자 default construct
		Buffer():
		m_buffer(new uint8_t[DEFAULT_SIZE]),m_capacity(DEFAULT_SIZE),m_offset(0),m_readOffset(0)
		{
			//printf_s("기본1 %p \n", m_buffer);
			Clear();
		}
		//size 만큰 생성
		Buffer(const size_t size):
		m_buffer(new uint8_t[size]), m_capacity(size), m_offset(0), m_readOffset(0)
		{
			//printf_s("기본2 %p \n", m_buffer);
			Clear();
		}
		//이동생성자
		Buffer(Buffer&& buffer) noexcept :
			m_buffer(buffer.m_buffer), m_capacity(buffer.m_capacity), m_offset(buffer.m_offset),m_readOffset(0)
		{
		//	printf_s("이동 %p \n", m_buffer);
			buffer.m_buffer = nullptr;
			buffer.m_offset = 0;
			buffer.m_capacity = 0;
		}
		//복사 생성자
		Buffer(const Buffer& buffer):
		m_buffer(new uint8_t[buffer.m_capacity]), m_capacity(buffer.m_capacity),m_offset(buffer.m_offset),m_readOffset(0)
		{
			//printf_s("복사 %p \n", m_buffer);
			memcpy_s(m_buffer, m_capacity, buffer.m_buffer, m_offset);
		}
		//포인트 생성자
		Buffer(uint8_t* buffer,const size_t size):
		m_buffer(buffer),m_capacity(size),m_offset(size),m_readOffset(0)
		{
			//printf_s("포인터 생성 %p \n", m_buffer);
		}
		
		//소멸자
		virtual ~Buffer()
		{
			try
			{
				if (m_buffer != nullptr)
				{
					//printf_s("소멸자1 %p \n", m_buffer);
					delete[] m_buffer;
					m_buffer = nullptr;
				}else
				{
					//printf_s("소멸자 try %p \n", m_buffer);
				}
			}catch (std::exception ex)
			{
				//printf_s("buffer delete error : %s", ex.what());
			}
		}


	public:
		Buffer& operator =(Buffer& buffer)
		{
			Buffer new_buffer(buffer);
			return new_buffer;
		}

		void operator +=(Buffer& buffer)
		{
			//new data
			size_t new_size = m_capacity + buffer.m_capacity;
			size_t new_offset = m_offset + buffer.m_offset;
			uint8_t* new_buffer = new uint8_t[new_size];
			//copy
			memcpy_s(new_buffer, m_capacity, m_buffer, m_capacity);
			memcpy_s(new_buffer + m_capacity, buffer.m_capacity, buffer.m_buffer, buffer.m_capacity);
			delete[] m_buffer;
			m_buffer = new_buffer;
			//move
			new_buffer = nullptr;
			m_offset = new_offset;
			m_capacity = new_size;
		}

		Buffer operator +(Buffer& buffer)
		{
			//new data
			size_t new_size = m_capacity + buffer.m_capacity;
			size_t new_offset = m_offset + buffer.m_offset;
			uint8_t* new_buffer = new uint8_t[new_size];
			//copy
			memcpy_s(new_buffer, m_capacity, m_buffer, m_capacity);
			memcpy_s(new_buffer + m_capacity, buffer.m_capacity, buffer.m_buffer, buffer.m_capacity);
			//new buffer
			Buffer return_buffer(new_buffer,new_size);
			return_buffer.m_offset = new_offset;
			return return_buffer;
		}

	public:
		constexpr static size_t DEFAULT_SIZE = 1024;
		void Clear()
		{
			memset(m_buffer, 0, m_capacity);
		}

		void Resize(size_t size)
		{
			//new buffer create
			uint8_t* new_buffer = new uint8_t[size];
			//new buffer clear
			memset(new_buffer, 0, size);
			//copy
			memcpy_s(new_buffer, size, m_buffer, size);
			//size fix 
			if (m_offset > size)
				m_offset = size;
			m_capacity = size;
			//delete
			delete[] m_buffer;
			m_buffer = new_buffer;
			new_buffer = nullptr;
		}

		void SetOffset(const size_t& offset)
		{
			this->m_offset = offset;
		}

		uint8_t* GetBuffer() const
		{
			return m_buffer;
		}

		size_t GetBufferSize() const
		{
			return m_capacity;
		}

		virtual int GetSize() const
		{
			return m_offset;
		}

		size_t GetReadOffset() const
		{
			return m_readOffset;
		}


	public:
		//write
		virtual bool push_back(const uint8_t* data, const size_t& size)
		{
			return WriteData(data, size);
		}
		//read
		virtual bool pop(uint8_t* data, const size_t& size)
		{
			return ReadData(data, size);
		}

	private:
		bool WriteData(const uint8_t* data,const size_t& size)
		{
			if(m_offset+size>m_capacity||size<=0)
				return false;
			memcpy_s(m_buffer + m_offset, size, data, size);
			m_offset += size;
			return  true;
		}

		bool ReadData(uint8_t* data, const size_t& size)
		{
			if (size <= 0|| m_offset<=0)
				return false;
			memcpy_s(data, size, m_buffer + m_readOffset, size);
			m_readOffset += size;
			m_offset -= size;
			return true;
		}
		

	protected:
		uint8_t* m_buffer;

		int32_t m_capacity;
		int32_t m_offset;
		int32_t m_readOffset;
	};
} 
