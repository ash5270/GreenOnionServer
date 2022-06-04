#pragma once
#include "Server.h"
namespace greenonion::system
{
	class Application
	{
	public:
		Application();
	public:
		void Initialize();
		void StartApp();
		void UpdateApp();
		void StopApp();
		void ExitApp();


	private:
		network::Server m_server;
	};
}

