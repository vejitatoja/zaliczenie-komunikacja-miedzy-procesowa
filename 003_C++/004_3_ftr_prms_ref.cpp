#include <iostream> // input / output
#include <string>   // std::string
#include <future>   // std::future, std::promise
#include <thread>   // std::thread

void thFun(std::promise<std::string>& prms)
{
	std::this_thread::sleep_for(std::chrono::seconds(5));

	//set input (promise)
	prms.set_value("Hello world");
}

int main(int argc, char* argv[])
{
	//create promise (input) - shared state is alocated
	std::promise<std::string> prms;

	//obtain future from promise (output) - shared state is shared
	std::future<std::string> ftr = prms.get_future();

	//share the input(promise) with new thread
	//input is still available to this thread (now it's shared)
	std::thread th(&thFun, std::ref(prms));

	//get output (future)
	std::string str = ftr.get();

	std::cout << str << std::endl;
	th.join();
	return 0;
}

//g++ <name> -std++=c++11 -pthread
