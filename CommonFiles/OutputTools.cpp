/*
* @Author: 1uci3n
* @Date:   2018-09-21 16:48:09
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-10-09 17:05:09
*/
#include "CommonFiles.h"

bool outputMap(map<double, double> map, vector<double> keySet, char filename[]){
	ofstream fout(filename);
	double key;
	for (int i = 0; i < keySet.size(); ++i)
	{
		key = keySet[i];
		fout << key << "\t" << map[key] << "\n";
	}
	fout.close();
	return true;
}

bool outputMap(map<double, vector<double> > map, vector<double> keySet, char filename[]){
	ofstream fout(filename);
	double key;
	for (int i = 0; i < keySet.size(); ++i)
	{
		key = keySet[i];
		fout << key << "\t";
		for (int j = 0; j < map[key].size(); ++j)
		{
			fout << map[key][j] << "\t";
		}
		fout << "\n";
	}
	fout.close();
	return true;
}

bool outputList(vector<vector <int> > list, char filename[]){
	ofstream fout(filename);
	int innerSize = list[0].size();
	for (int i = 0; i < list.size(); ++i)
	{
		for (int j = 0; j < innerSize; ++j)
		{
			fout << list[i][j] << " ";
		}
		fout << "\n";
	}
	fout.close();
	return true;
}

bool outputMap(map<double, double> map, vector<double> keySet){
	char filename[] = "temp.txt";
	return outputMap(map, keySet, filename);
}

bool outputMap(map<double, vector<double> > map, vector<double> keySet){
	char filename[] = "temp.txt";
	return outputMap(map, keySet, filename);
}

bool outputList(vector<vector <int> > list){
	char filename[] = "temp.txt";
	return outputList(list, filename);
}