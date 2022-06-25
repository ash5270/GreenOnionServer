#include "Server.h"
#include"Session.h"
#include <memory>
#include <boost/bind.hpp>

#include "LogSystem.h"


greenonion::system::network::Server::Server(UINT port) :
	m_acceptorThread(0), m_IoContext(1)
{
	GO_LOG(LOGLEVEL::LOG_DEBUG, "Server Start...");
	m_acceptor = new boost::asio::ip::tcp::acceptor(m_acceptorThread.GetContext(),
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
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
	}
	catch (std::exception ex)
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
	if (m_session_manager.GetSize() > 0)
	{
		Buffer buffer;
		x++;
		int zx = x;
		float z2 = 0.2f;
		float z3 = 0.5f;
		float z4 = 0.6f;
		buffer.push_back((uint8_t*)&zx, sizeof(x));
		buffer.push_back((uint8_t*)&z2, sizeof(z2));
		buffer.push_back((uint8_t*)&z3, sizeof(z3));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		buffer.push_back((uint8_t*)&z4, sizeof(z4));
		//100바이트
		//buffer.push_back(123);
		m_session_manager.SendAllSession(std::move(buffer));
	}

	//std::this_thread::sleep_for(std::chrono::microseconds(1));

	return true;
}

void greenonion::system::network::Server::WaitForClientConnection()
{
	m_acceptor->async_accept(std::bind(&Server::AcceptorHandler, this, std::placeholders::_1, std::placeholders::_2));
}

void greenonion::system::network::Server::AcceptorHandler(const boost::system::error_code& error, boost::asio::ip::tcp::socket socket)
{
	if (!error)
	{
		//GO_LOG(LOGLEVEL::LOG_DEBUG, "Connect to client");
		ClientConnect(std::move(socket));
	}
	else
	{
		GO_LOG(LOGLEVEL::LOG_ERROR, "Connect error");
	}
	WaitForClientConnection();
}

void greenonion::system::network::Server::ClientConnect(boost::asio::ip::tcp::socket&& socket)
{
	std::shared_ptr<Session> new_session = std::make_shared<Session>(m_IoContext.GetContext(), std::move(socket));
	if (new_session == nullptr)
		return;

	m_session_manager.AddSession(new_session);
	m_session_manager.BindRemoveFunc(new_session->remove_func);
	new_session->Connect();
}