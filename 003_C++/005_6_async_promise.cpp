#include <iostream> // input / output
#include <thread>   // std::thread
#include <future>   // std::future, std::promise

int factorial(std::future<int>& f)
{
	int res = 1;
	
	std::cout << "New thread : waiting for a future to be ready..." << std::endl;

	//get OUTPUT
	int N = f.get();
	std::cout << "New thread : future received" << std::endl; 

	for(int i = 1 ; i <= N ; i++)
		res *= i;
	
	std::this_thread::sleep_for(std::chrono::seconds(5));

	return res; // return as future
}

int main(int argc, char* argv[])
{
	int result = 0;

	// INPUT
	std::promise<int> p;
	// OUTPUT
	std::future<int> f = p.get_future();

	std::cout << "Main thread : before async" << std::endl;
	
	// another OUTPUT
	std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f)); 

	std::cout << "Main thread : goining sleep" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "Main thread : after sleep, keep promise" << std::endl;
	
	//set IMNPUT
    p.set_value(4);	
	
	std::cout << "Main thread : get the results from async" << std::endl;
	result = fu.get();

	std::cout << "Main thread: result = " << result << std::endl;

	return 0;
}

