#include <iostream> // input / output

int factorial(int N)
{
	int res = 1;
	for(int i = 1 ; i <= N ; i++)
		res *= i;

	return res;
}

int main(int argc, char* argv[])
{
	int result = factorial(4);
	std::cout << "result = " << result << std::endl;
}
