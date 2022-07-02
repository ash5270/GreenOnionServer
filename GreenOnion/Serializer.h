#pragma once
#include <cstdint>
#include "Buffer.h"

namespace greenonion::system
{
	class Serializer
	{
	public:
		virtual ~Serializer() = default;

		bool Write(Buffer* buffer, std::string& data)
		{
			uint16_t size = data.length();
			if (Write(buffer, size))
			{
				const auto ptr = (uint8_t*)(data.c_str());
				return buffer->push_back(ptr, size);
			}
			return false;
		}

		bool Write(Buffer* buffer, const uint8_t& data)
		{
			return  buffer->push_back(&data, sizeof(data));
		}

		bool Write(Buffer* buffer, uint16_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->push_back(ptr, sizeof(data));
		}

		bool Write(Buffer* buffer, uint32_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->push_back(ptr, sizeof(data));
		}

		bool Write(Buffer* buffer, uint64_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->push_back(ptr, sizeof(data));
		}

		bool Write(Buffer* buffer, int8_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->push_back(ptr, sizeof(data));
		}

		bool Write(Buffer* buffer, int16_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->push_back(ptr, sizeof(data));
		}

		bool Write(Buffer* buffer, int32_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->push_back(ptr, sizeof(data));
		}

		bool Write(Buffer* buffer, int64_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->push_back(ptr, sizeof(data));
		}

		bool Write(Buffer* buffer, float& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->push_back(ptr, sizeof(data));
		}

		bool Write(Buffer* buffer, double& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->push_back(ptr, sizeof(data));
		}

	public:
		//Read -- 
		bool Read(Buffer* buffer, std::string& data)
		{
			uint16_t size = 0;
			if (Read(buffer, size))
			{
				uint8_t* ptr = nullptr;
				const auto result = buffer->pop(ptr, size);
				data.append(reinterpret_cast<char*>(ptr), size);
				return result;
			}
			return false;
		}

		bool Read(Buffer* buffer, uint8_t& data)
		{
			return buffer->pop(&data, sizeof(data));
		}

		bool Read(Buffer* buffer, uint16_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->pop(ptr, sizeof(data));
		}

		bool Read(Buffer* buffer, uint32_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->pop(ptr, sizeof(data));
		}

		bool Read(Buffer* buffer, uint64_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->pop(ptr, sizeof(data));
		}

		bool Read(Buffer* buffer, int8_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->pop(ptr, sizeof(data));
		}

		bool Read(Buffer* buffer, int16_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->pop(ptr, sizeof(data));
		}

		bool Read(Buffer* buffer, int32_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->pop(ptr, sizeof(data));
		}

		bool Read(Buffer* buffer, int64_t& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->pop(ptr, sizeof(data));
		}

		bool Read(Buffer* buffer, float& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->pop(ptr, sizeof(data));
		}

		bool Read(Buffer* buffer, double& data)
		{
			const auto ptr = reinterpret_cast<uint8_t*>(&data);
			return buffer->pop(ptr, sizeof(data));
		}
	};

	namespace  network::packet
	{
		class Packet;
	}

	class ISerializer
	{
	public:
		virtual ~ISerializer() = default;
		virtual bool Serialize(const network::packet::Packet* Packet) = 0;
		virtual bool DeSerialize(const network::packet::Packet* Packet) = 0;
	};
}
