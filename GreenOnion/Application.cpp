#include "Application.h"
#include"boost/asio.hpp"
#include"LogSystem.h"
greenonion::system::Application::Application()
	:m_server(22)
{
	
}

void greenonion::system::Application::Initialize()
{
	LogSystem::Instance().InitSystem();
}

void greenonion::system::Application::StartApp()
{
	LogSystem::Instance().StartSystem();
	m_server.StartServer();
}

void greenonion::system::Application::UpdateApp()
{
	while(true)
	{

	}
}

void greenonion::system::Application::StopApp()
{
	m_server.StopServer();
}

void greenonion::system::Application::ExitApp()
{

}
