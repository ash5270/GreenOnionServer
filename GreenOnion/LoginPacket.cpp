#include "LoginPacket.h"

bool greenonion::system::network::packet::LoginSerializer::Serialize(const network::packet::Packet* packet)
{
	LoginPacket* login_packet = reinterpret_cast<LoginPacket*>(&packet);
	
	return false;
}

bool greenonion::system::network::packet::LoginSerializer::DeSerialize(const network::packet::Packet* packet)
{
	LoginPacket* login_packet = reinterpret_cast<LoginPacket*>(&packet);
	auto result= Read(login_packet->buffer, login_packet->loginData.ID);
	result = Read(login_packet->buffer, login_packet->loginData.Password);
	return result;
}

greenonion::system::network::packet::LoginPacket::LoginPacket()
{
	header.ID = PacketID::Login;
	header.Size = 0;
	buffer = new Buffer();
}

greenonion::system::network::packet::LoginPacket::LoginPacket(const size_t& size)
{
	header.ID = PacketID::Login;
	header.Size = 0;
	buffer = new Buffer(size);
}

greenonion::system::network::packet::LoginPacket::~LoginPacket()
{
	delete buffer;
}
