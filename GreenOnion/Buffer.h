#pragma once
#include <cstdint>
#include <memory>

namespace greenonion::system
{
	class Buffer
	{
	public:
		//기본 생성자 default construct
		Buffer():
		m_buffer(new uint8_t[DEFAULT_SIZE]),m_capacity(DEFAULT_SIZE),m_offset(0)
		{
			Clear();
		}
		//size 만큰 생성
		Buffer(const size_t size):
		m_buffer(new uint8_t[size]), m_capacity(size), m_offset(0)
		{
			Clear();
		} 
		//복사 생성자
		Buffer(const Buffer& buffer):
		m_buffer(new uint8_t[buffer.m_capacity]), m_capacity(buffer.m_capacity),m_offset(buffer.m_offset)
		{
			memcpy_s(m_buffer, m_capacity, buffer.m_buffer, m_offset);
		}
		//포인트 생성자
		Buffer(uint8_t* buffer,const size_t size):
		m_buffer(buffer),m_capacity(size),m_offset(size)
		{
			
		}
		//이동생성자
		Buffer(Buffer&& buffer):
		m_buffer(buffer.m_buffer), m_capacity(buffer.m_capacity), m_offset(buffer.m_offset)
		{
			buffer.m_buffer = nullptr;
			buffer.m_offset = 0;
			buffer.m_capacity = 0;
		}
		//소멸자
		~Buffer()
		{
			try
			{
				if(m_buffer!=nullptr)
				{
					delete[] m_buffer;
					m_buffer = nullptr;
				}
			}catch (std::exception ex)
			{
				printf_s("buffer delete error : %s", ex.what());
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
		//write
		void push_back(const uint8_t* data, const size_t& size)
		{
			WriteData(data, size);
		}

		void push_back(const std::string& string)
		{
			//문자열 길이
			const uint16_t size_len =static_cast<uint16_t>(string.size());
			//문자열 길이를 받을 uint16_t의 사이즈
			const uint16_t size = sizeof(uint16_t);
			if(WriteData(size))
			{
				WriteData(string.c_str(), size);
			}
		}

		//write
		void push_back(const uint8_t& data)
		{
			WriteData(data);
		}

		void push_back(const uint16_t& data)
		{
			WriteData(data);
		}

		void push_back(const uint32_t& data)
		{
			WriteData(data);
		}

		void push_back(const uint64_t& data)
		{
			WriteData(data);
		}

		void push_back(const int8_t& data)
		{
			WriteData(data);
		}

		void push_back(const int16_t& data)
		{
			WriteData(data);
		}

		void push_back(const int32_t& data)
		{
			WriteData(data);
		}

		void push_back(const int64_t& data)
		{
			WriteData(data);
		}

		void push_back(const bool& data)
		{
			WriteData(data);
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

		size_t GetSize() const
		{
			return m_offset;
		}

	

	private:
		template<typename T>
		bool WriteData(const T& data)
		{
			size_t size = sizeof(T);
			const char* data_ptr = reinterpret_cast<const char*>(&data);
			if(m_offset+size> m_capacity)
				return false;
			memcpy_s(m_buffer + m_offset, size, data_ptr, size);
			m_offset += size;
			return true;
		}

		template<typename T>
		bool WriteData(const T* data,const size_t& size)
		{
			if(m_offset+size>m_capacity)
				return false;
			memcpy_s(m_buffer + m_offset, size, data, size);
			m_offset += size;
			return  true;
		}

	private:
		uint8_t* m_buffer;

		size_t m_capacity;
		size_t m_offset;
	};
} 
