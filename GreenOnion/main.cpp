#include<iostream>
#include"Application.h"
#include"Server.h"

using namespace std;
using namespace greenonion::system;
int main()
{
	greenonion::system::Application* app;
	app = new greenonion::system::Application();

	app->Initialize();
	app->StartApp();
	app->UpdateApp();
	app->ExitApp();

	return 0;
}