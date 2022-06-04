#include "Server.h"
#include"Session.h"
#include <memory>
#include <boost/bind.hpp>


greenonion::system::network::Server::Server(UINT port):
	m_acceptorThread(0),m_IoContext(1)
{
	m_acceptor = new boost::asio::ip::tcp::acceptor(m_acceptorThread.GetContext(), boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
}

greenonion::system::network::Server::~Server()
{
	StopServer();
}

bool greenonion::system::network::Server::StartServer()
{
	try
	{
		WaitForClientConnection();
		m_acceptorThread.Start();
		m_IoContext.Start();
	}catch (std::exception ex)
	{
		return false;
	}

	return true;
}

bool greenonion::system::network::Server::StopServer()
{
	return true;
}

bool greenonion::system::network::Server::Update()
{
	return true;
}

void greenonion::system::network::Server::WaitForClientConnection()
{
	m_acceptor->async_accept(std::bind(&Server::AcceptorHandler, this, std::placeholders::_1, std::placeholders::_2));
}

void greenonion::system::network::Server::AcceptorHandler(const boost::system::error_code& error, boost::asio::ip::tcp::socket socket)
{
	if(!error)
	{
		printf_s("Connect to client");
		ClientConnect(std::move(socket));
	}else
	{
		printf_s("acceptor error ");
	}
	WaitForClientConnection();
}

void greenonion::system::network::Server::ClientConnect(boost::asio::ip::tcp::socket&& socket)
{
	std::shared_ptr<Session> new_session = std::make_shared<Session>(m_IoContext.GetContext(), std::move(socket));
	if(new_session==nullptr)
		return;

	m_sessionInfos.push_back(new_session);
}