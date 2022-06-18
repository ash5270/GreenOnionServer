#include "Session.h"
#include"SessionManager.h"
#include<boost/bind.hpp>

greenonion::system::network::Session::Session( boost::asio::io_context& context, asio::ip::tcp::socket socket):
	m_context(context), m_socket(std::move(socket))
{
	read_buffer = new greenonion::system::Buffer();
	send_buffer = new greenonion::system::Buffer();

	boost::asio::ip::tcp::no_delay option(true);
	m_socket.set_option(option);
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

void greenonion::system::network::Session::Send(Buffer&& buffer)
{
	send_buffer->push_back(buffer);
	//캡쳐 
	m_context.post([this, buffer]()
		{
			SendData();
		});
}

//void greenonion::system::network::Session::Send(const Buffer& buffer)
//{
// 	m_context.post([this, buffer]()
//		{
//			//SendData(std::move(buffer));
//		});
//}

void greenonion::system::network::Session::SendData()
{
	m_socket.async_send(asio::buffer(send_buffer->GetBuffer(), send_buffer->GetSize()),
		boost::bind(&Session::SendHandler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void greenonion::system::network::Session::SendHandler(boost::system::error_code ec, size_t transferred)
{
	if(!ec)
	{
		//GO_LOG(LOGLEVEL::LOG_DEBUG, "Send Success, transferred : ", transferred);
		send_buffer->Clear();
	}
	else
	{
		
	}
}
