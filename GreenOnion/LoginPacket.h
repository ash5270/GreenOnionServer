#pragma once
#include "Packet.h"
#include "Buffer.h"
#include "Serializer.h"
namespace  greenonion::system::network::packet
{
	struct LoginData
	{
		std::string ID;
		std::string Password;
	};

	class LoginSerializer : Serializer, ISerializer
	{
	public:
		bool Serialize(const network::packet::Packet* packet) override;
		bool DeSerialize(const network::packet::Packet* packet) override;
	};

	class LoginPacket : Packet
	{
	public:
		LoginPacket();
		LoginPacket(const size_t& size);

		~LoginPacket();
	public:
		Buffer* buffer;
		LoginData loginData;
	private:
		LoginSerializer m_loginSerializer;
	};
}


