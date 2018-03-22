#include <fstream>

bool outputMap(std::map<double, double> map, std::vector<double> keySet, char filename[]){
	std::ofstream fout(filename);
	double key;
	for (int i = 0; i < keySet.size(); ++i)
	{
		key = keySet[i];
		fout << key << "\t" << map[key] <<"\n";
	}
	fout.close();
	return true;
}

bool outputMap(std::map<double, std::vector<double> > map, std::vector<double> keySet, char filename[]){
	std::ofstream fout(filename);
	double key;
	for (int i = 0; i < keySet.size(); ++i)
	{
		key = keySet[i];
		fout << key << "\t" << map[key][0] << "\t" << map[key][1] <<"\n";
	}
	fout.close();
	return true;
}


bool outputMap(std::map<double, double> map, std::vector<double> keySet){
	char filename[] = "temp.txt";
	return outputMap(map, keySet, filename);
}

bool outputMap(std::map<double, std::vector<double> > map, std::vector<double> keySet){
	char filename[] = "temp.txt";
	return outputMap(map, keySet, filename);
}