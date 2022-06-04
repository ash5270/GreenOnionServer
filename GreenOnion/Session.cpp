#include "Session.h"

greenonion::system::network::Session::Session( boost::asio::io_context& context, asio::ip::tcp::socket socket):
	m_context(context), m_socket(std::move(socket))
{

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
	
}

void greenonion::system::network::Session::RecvHandler(boost::system::error_code ec, size_t transferred)
{
}
