#include "Session.h"
#include<boost/bind.hpp>

greenonion::system::network::Session::Session( boost::asio::io_context& context, asio::ip::tcp::socket socket):
	m_context(context), m_socket(std::move(socket))
{
	read_buffer = new greenonion::system::Buffer();
	send_buffer = new greenonion::system::Buffer();

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

bool greenonion::system::network::Session::DisConnect()
{
	return false;
}

void greenonion::system::network::Session::RecvData()
{
	m_socket.async_receive(boost::asio::buffer(read_buffer->GetBuffer(), read_buffer->GetBufferSize()), 0,
		boost::bind(&Session::RecvHandler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
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

		}
		RecvData();
	}else
	{
		DisConnect();
	}
}
