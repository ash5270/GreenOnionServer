#pragma once
#include "CommonHeader.h"
#include "Buffer.h"
#include <memory>

#include "SessionManager.h"

using namespace boost;

namespace greenonion::system::network
{
	class Session : public std::enable_shared_from_this<Session>
	{
	public:
		Session(boost::asio::io_context& context, asio::ip::tcp::socket socket);
		 ~Session();

	public:
		bool Connect();
		void DisConnect();

		//move data
		void Send(Buffer&& buffer);
		//copy data
		/*void Send(const Buffer& buffer);*/
		//remove Func
		std::function<void(const std::shared_ptr<Session>&)> remove_func;
	private:
		void RecvData();
		void RecvHandler(boost::system::error_code ec, size_t transferred);
		void SendData(Buffer buffer);
		void SendHandler(boost::system::error_code ec, size_t transferred);
		
	private:
		asio::ip::tcp::socket m_socket;
		boost::asio::io_context& m_context;

		asio::ip::tcp::endpoint m_endpoint;
		Buffer* read_buffer; 
		Buffer* send_buffer;

	};
}

