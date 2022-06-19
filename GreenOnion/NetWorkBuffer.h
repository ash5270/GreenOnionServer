#pragma once
#include "Buffer.h"

namespace greenonion::system::network
{
	class NetWorkBuffer
	{
	public:
		//
		//버퍼를 write 를 해야 pointer 와 사이즈 돌려줘야함
		//그전에 돌려주면 다른 사용하는 곳과 겹칠듯
		//
		uint8_t* Data() const
		{
			//현재 버퍼 위치
			return m_buffer.GetBuffer()+m_buffer.GetSize();
		}
		size_t GetSize() const;

		bool Write(__out uint8_t& buffer, __out size_t& size, int data)
		{
			m_buffer.push_back(data);
		}


	private:
		Buffer m_buffer;
		uint8_t m_offset;

	};
}
