#include "Session.h"
#include"SessionManager.h"

#include<boost/bind.hpp>


greenonion::system::network::Session::Session( boost::asio::io_context& context, asio::ip::tcp::socket socket):
	m_context(context), m_socket(std::move(socket))
{
	//보통 uint16 최대값
	read_buffer = new greenonion::system::NetWorkBuffer(65535);
	send_buffer = new greenonion::system::NetWorkBuffer(65535);
	/*read_buffer = new greenonion::system::NetWorkBuffer(4096);
	send_buffer = new greenonion::system::NetWorkBuffer(4096);*/

	boost::asio::ip::tcp::no_delay option(true);
	m_socket.set_option(option);

	m_is_send = false;
}


greenonion::system::network::Session::~Session()
{

}

bool greenonion::system::network::Session::Connect()
{
	if(m_socket.is_open())
	{
		RecvData();
		return true;
	}
	
	return false;
}

void greenonion::system::network::Session::DisConnect()
{
	if(m_socket.is_open())
	{
		//GO_LOG(LOGLEVEL::LOG_ERROR, " test");
		boost::asio::post(m_context, [this]()
			{
				boost::system::error_code ec;
				m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
				m_socket.close(ec);
				
				if(ec)
				{
					GO_LOG(LOGLEVEL::LOG_ERROR, ec.message());
				}
				//여기다 안 쓰면 소멸자 먼저 호출 되어서 socket이 사라져 위에 함수에서 오류
				//여기 한번 고쳐야할듯
				if (remove_func != nullptr)
				{
					remove_func(shared_from_this());
				}
			});
	}
}

void greenonion::system::network::Session::RecvData()
{
	m_socket.async_receive(boost::asio::buffer(read_buffer->GetBuffer(), read_buffer->GetBufferSize()), 0,
		boost::bind(&Session::RecvHandler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void greenonion::system::network::Session::RecvHandler(boost::system::error_code ec, size_t transferred)
{
	if(!ec)
	{
		if(transferred<0)
		{
			return;
		}
		else
		{
			//GO_LOG(LOGLEVEL::LOG_DEBUG, "Receive success");
		}

		RecvData();
	}else
	{
		DisConnect();
	}
}


//보내는 중이라면 그냥 버퍼에 쓰기만 하고 넘겨주기
//보내고 있지 않다면 바로 보내기
//
//

void greenonion::system::network::Session::Send(Buffer&& buffer)
{
	size_t size = 0;
	//현재 넣어던 주소 -> index //
	send_buffer->GetCurrentIndex(size, buffer.GetSize());
	send_buffer->push_back(buffer.GetBuffer(), buffer.GetSize());
	//GO_LOG(LOGLEVEL::LOG_DEBUG, "buffer  size: ", (int)buffer.GetSize());
	//
	if(true)
	{
		//GO_LOG(LOGLEVEL::LOG_DEBUG, "Write offset : ", (int)send_buffer->GetWriteOffset());
		Send(size, buffer.GetSize());
		
	}else
	{
		
	}

	
}

void greenonion::system::network::Session::Send(const size_t& index, const size_t& size)
{
	m_is_send = true;
	m_context.post([this, index, size]()
		{
			SendData(index, size);
		});
}

void greenonion::system::network::Session::SendData()
{
	m_socket.async_send(asio::buffer(send_buffer->GetBuffer(), send_buffer->GetSize()),
		boost::bind(&Session::SendHandler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void greenonion::system::network::Session::SendData(const size_t& index, const size_t& size)
{
	m_socket.async_send(asio::buffer(send_buffer->GetBuffer()+index, size),
		boost::bind(&Session::SendHandler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void greenonion::system::network::Session::SendHandler(boost::system::error_code ec, size_t transferred)
{
	if(!ec)
	{
		m_is_send = false;
		size_t x;
		//버퍼
		GO_LOG(LOGLEVEL::LOG_DEBUG, "1 read offset : ", (int)send_buffer->GetReadOffset(), ", write offset : ", (int)send_buffer->GetWriteOffset(), ", send_size : ", send_buffer->GetSize());
		send_buffer->pop_size( transferred);
		GO_LOG(LOGLEVEL::LOG_DEBUG, "2 read offset : ", (int)send_buffer->GetReadOffset(), ", write offset : ", (int)send_buffer->GetWriteOffset(), ", send_size : ", send_buffer->GetSize());

		//GO_LOG(LOGLEVEL::LOG_DEBUG, "read offset : ", (int)send_buffer->GetReadOffset(), ", write offset : ", (int)send_buffer->GetWriteOffset(),", buffer size : ", send_buffer->GetSize());

		/*if (send_buffer->GetReadOffset() != send_buffer->GetWriteOffset())
		{
			if(send_buffer->GetReadOffset()< send_buffer->GetWriteOffset())
			{
				size_t size = send_buffer->GetWriteOffset() - send_buffer->GetReadOffset();
				SendData(send_buffer->GetReadOffset(), size);
				GO_LOG(LOGLEVEL::LOG_DEBUG, "read offset : ", (int)send_buffer->GetReadOffset(), ", write offset : ", (int)send_buffer->GetWriteOffset(), ", send_size : ", (uint32_t)size);

			}else
			{
				size_t size = send_buffer->m_lastOffset - send_buffer->GetReadOffset();
				SendData(send_buffer->GetReadOffset(), size);
				GO_LOG(LOGLEVEL::LOG_DEBUG, "  111read offset : ", (int)send_buffer->GetReadOffset(), ", write offset : ", (int)send_buffer->GetWriteOffset(), ", send_size : ", (uint32_t)size);

			}
			
		}*/
	}
	else
	{
		
	}
}
