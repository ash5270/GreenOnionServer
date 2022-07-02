#include "Session.h"
#include"SessionManager.h"

#include<boost/bind.hpp>
#include"Packet.h"
#include"LoginPacket.h"

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
	m_socket.async_receive(boost::asio::buffer(read_buffer->GetBuffer()+read_buffer->m_writeOffset, read_buffer->RemainSize()), 0,
		boost::bind(&Session::RecvHandler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void greenonion::system::network::Session::RecvHandler(boost::system::error_code ec, size_t transferred)
{
	if(!ec)
	{
		if(transferred<=0)
		{
			return;
		}
		else
		{
			read_buffer->m_writeOffset += transferred;
			read_buffer->m_size += transferred;
			using namespace network::packet;
			HeaderSerializer serializer;
			PacketHeader header;
			serializer.DeSerialize(read_buffer, header);
			LoginPacket* login_packet = new LoginPacket(transferred);



			GO_LOG(LOGLEVEL::LOG_DEBUG, "Receive success ", "header iD : ",(uint16_t)header.ID, "   header Size : ", header.Size);
		}
		RecvData();
	}else
	{
		DisConnect();
	}
}

//보내는 중이라면 그냥 버퍼에 쓰기만 하고 넘겨주기
//보내고 있지 않다면 바로 보내기
void greenonion::system::network::Session::Send(Buffer&& buffer)
{
	size_t size = 0;
	//현재 넣어던 주소 -> index //
	size=send_buffer->GetCurrentIndex();
	send_buffer->push_back(buffer.GetBuffer(), buffer.GetSize());
	if(!m_is_send)
	{
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
		//GO_LOG(LOGLEVEL::LOG_DEBUG, "transferred ", transferred , "currnet index : " , send_buffer->m_writeOffset.load(), " read index : ",send_buffer->m_readOffset.load() );
		send_buffer->skip_pop( transferred);
		if(send_buffer->m_size>0)
		{
			GO_LOG(LOGLEVEL::LOG_DEBUG, "buffer size", send_buffer->m_size.load());
			Send(send_buffer->m_readOffset, send_buffer->m_size);
			//여기가 문제 어떻게 마지막 까지 보낼까 고민해야할듯
		}
	}
	else
	{
		GO_LOG(LOGLEVEL::LOG_DEBUG, "transferred ", transferred, "currnet index", send_buffer->GetCurrentIndex());
	}
}
