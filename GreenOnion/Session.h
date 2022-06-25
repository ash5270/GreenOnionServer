#pragma once
#include "CommonHeader.h"
#include "SessionManager.h"
#include "NetWorkBuffer.h"

#include <memory>
#include <atomic>
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
		void Send(const size_t& index,const size_t& size);
		//remove Func
		std::function<void(const std::shared_ptr<Session>&)> remove_func;
	private:
		void RecvData();
		void RecvHandler(boost::system::error_code ec, size_t transferred);
		void SendData();
		void SendData(const size_t& index, const size_t& size);
		void SendHandler(boost::system::error_code ec, size_t transferred);
		
	private:
		asio::ip::tcp::socket m_socket;
		boost::asio::io_context& m_context;

		asio::ip::tcp::endpoint m_endpoint;
		NetWorkBuffer* read_buffer;
		NetWorkBuffer* send_buffer;

	private:
		long read_count = 0;
		long send_count = 0;

		std::atomic_bool m_is_send;
	};
}

