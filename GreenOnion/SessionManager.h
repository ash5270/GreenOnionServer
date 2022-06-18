#pragma once
#include <list>
#include <memory>
#include <functional>
#include "Buffer.h"

namespace greenonion::system::network
{
	//session관리 매니저 
	class SessionManager
	{
	public:
		SessionManager();
		~SessionManager();
	public:
		void AddSession(const std::shared_ptr<class Session>& session);
		void Remove(const std::shared_ptr<class Session>& session);

		int GetSize() const;
		bool IsEmpty() const;

		void SendAllSession(Buffer&& buffer);

		void BindRemoveFunc(std::function<void(const std::shared_ptr<class Session>&)>& func)
		{
			func = std::bind(&SessionManager::Remove, this, std::placeholders::_1);
		}

	private:
		std::list<std::shared_ptr<class Session>> m_sessions;
		
	};

}
