#include<iostream>
#include<ctime>
#include<ratio>
#include<chrono>
int main()
{
	std::chrono::high_resolution_clock::time_point test  = std::chrono::high_resolution_clock::now();
	std::cout << test << '\n';
}
