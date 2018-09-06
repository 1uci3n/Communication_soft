#include "LDPCCode.h"

void printVector(std::vector<int> v){
	for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}

void printVector(std::vector<char> v){
	for (std::vector<char>::iterator i = v.begin(); i != v.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}

void printVector(std::vector<double> v){
	for (std::vector<double>::iterator i = v.begin(); i != v.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}