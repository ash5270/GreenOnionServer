#pragma once
#include "CommonHeader.h"
#include "IOThread.h"
#include <list>


namespace greenonion::system::network
{
	class Server
	{
	public:
		Server(UINT port);
		~Server();

	public:
		bool StartServer();
		bool StopServer();
		bool Update();



	private:
		//클라이언트 대기
		void WaitForClientConnection();
		//클라이언트 연결시
		void ClientConnect(boost::asio::ip::tcp::socket&& socket);
		//acceptor 콜백함수
		void AcceptorHandler(const boost::system::error_code& error, boost::asio::ip::tcp::socket socket);


	private:
		std::list <std::shared_ptr<class Session>> m_sessionInfos;
		
		//acceptor 
		boost::asio::ip::tcp::acceptor* m_acceptor;
		//acceptor Thread
		IOThread m_acceptorThread;
		IOThread m_IoContext;

	};

}
