/*
* @Author: 1uci3n
* @Date:   2018-09-21 16:48:23
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-10-01 19:21:57
*/
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