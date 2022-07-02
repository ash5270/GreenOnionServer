#pragma once
#include <cstdint>
#include "Serializer.h"
namespace greenonion::system::network::packet
{

	enum class PacketID : uint16_t
	{
		Login=2000,
	};

	

	struct PacketHeader
	{
		PacketID ID;
		uint16_t Size;
	};

	class HeaderSerializer : Serializer, ISerializer
	{
	public:
		bool Serialize(Buffer* buffer,const PacketHeader& header)
		{
			auto result=  Write(buffer, static_cast<uint16_t>(header.ID));
			result = Write(buffer, header.Size);
			return  result;
		}

		bool DeSerialize(Buffer* buffer, PacketHeader& header)
		{
			uint16_t id,size = 0;
			auto result = Read(buffer, id);
			result = Read(buffer, size);
			header.ID = static_cast<PacketID>(id);
			header.Size = size;
			return false;
		}

	public:
		bool Serialize(const network::packet::Packet* Packet) override
		{
			return false;
		}
		bool DeSerialize(const network::packet::Packet* Packet) override
		{
			return false;
		}
	};

	class Packet
	{
	public:
		PacketHeader header;
		HeaderSerializer header_serializer;
	};
	
}
