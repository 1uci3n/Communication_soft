#include "CommonFiles.h"

bool outputMap(map<double, double> map, vector<double> keySet, char filename[]){
	ofstream fout(filename);
	double key;
	for (int i = 0; i < keySet.size(); ++i)
	{
		key = keySet[i];
		fout << key << "\t" << map[key] <<"\n";
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
		fout <<"\n";
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