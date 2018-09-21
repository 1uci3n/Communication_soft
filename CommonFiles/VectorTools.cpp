#include "CommonFiles.h"

void printVector(vector<int> v){
	for (vector<int>::iterator i = v.begin(); i != v.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl;
}

void printVector(vector<char> v){
	for (vector<char>::iterator i = v.begin(); i != v.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl;
}

void printVector(vector<double> v){
	for (vector<double>::iterator i = v.begin(); i != v.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl;
}