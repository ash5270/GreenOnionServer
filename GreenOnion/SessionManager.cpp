#include "SessionManager.h"
#include "Session.h"

greenonion::system::network::SessionManager::SessionManager()
{

}

greenonion::system::network::SessionManager::~SessionManager()
{

}

void greenonion::system::network::SessionManager::AddSession(const std::shared_ptr<Session>& session)
{
	m_sessions.push_back(session);
}

void greenonion::system::network::SessionManager::Remove(const std::shared_ptr<Session>& session)
{
	GO_LOG(LOGLEVEL::LOG_DEBUG, " Remve function");
	if(!m_sessions.remove(session))
	{
		GO_LOG(LOGLEVEL::LOG_ERROR, "Is not have a session");
	}
}

int greenonion::system::network::SessionManager::GetSize() const
{
	return m_sessions.size();
}

bool greenonion::system::network::SessionManager::IsEmpty() const
{
	return m_sessions.size() < 0 ? true : false;
}

void greenonion::system::network::SessionManager::SendAllSession(Buffer&& buffer)
{
	if(m_sessions.size()>0)
	{
		for (auto session : m_sessions)
		{
			session->Send(std::move(buffer));
		}
	}
}
