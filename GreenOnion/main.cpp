#include<iostream>
#include"Application.h"
#include"Server.h"
#include"CricularBuffer.h"


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

	//network::CricularBuffer net_work_buffer(10);
	//int test_data_1 = 1233333223;
	//int test_data_2 = 4564443146;
	//int test_data_3 = 7895213256;

	//int test_read_1;

	//net_work_buffer.push_back((uint8_t*) & test_data_1, sizeof(test_data_1));

	//net_work_buffer.push_back((uint8_t*) & test_data_2, sizeof(test_data_1));

	//net_work_buffer.pop((uint8_t*)&test_read_1, sizeof(test_read_1));

	//net_work_buffer.push_back((uint8_t*)&test_data_3, sizeof(test_data_1));

	//net_work_buffer.push_back((uint8_t*)&test_data_1, sizeof(test_data_1));

	/*net_work_buffer.push_back(123);
	net_work_buffer.push_back(456);
	net_work_buffer.push_back(789);*/




	return 0;
}