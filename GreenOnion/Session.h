#pragma once
#include "CommonHeader.h"
#include "Buffer.h"
#include <memory>

using namespace boost;

namespace greenonion::system::network
{
	class Session : public std::enable_shared_from_this<Session>
	{
	public:
		Session( boost::asio::io_context& context, asio::ip::tcp::socket socket);
		 ~Session();

	public:
		bool Connect();
		bool DisConnect();
	private:
		void RecvData();
		void RecvHandler(boost::system::error_code ec, size_t transferred);
		void SendData();
		void SendHandler(boost::system::error_code ec, size_t transferred);

	private:
		asio::ip::tcp::socket m_socket;
		boost::asio::io_context& m_context;

		asio::ip::tcp::endpoint m_endpoint;
		Buffer* read_buffer;
		Buffer* send_buffer;

	};
}

