#include<iostream>
#include <vector>
#include <map>

using namespace std;

class TannerGraph
{
private:
	void test();
	void init(vector<double> recivedValue);
	//vector<double> recivedValue;
	//map<int, int> searchCnbyVnMap;
	//map<int, int> searchVnbyCnMap;
	vector<double> Lj;
	//j->i's message
	vector<vector<int> > Lji;
	//i->j's message
	vector<vector<int> > Lij;

public:
	TannerGraph(vector<vector<int> > parityCheckMatrix)
	{
		for (int i = 0; i < parityCheckMatrix.size(); ++i){
			for (int j = 0; j < parityCheckMatrix[i].size(); ++j)
			{
				if(parityCheckMatrix[i][j] == 1){
					cout << i << " " << j << endl;
					//searchCnbyVnMap.insert(pair<int, int>(j, i));
					//searchVnbyCnMap.insert(pair<int, int>(i, j));
				}
			}
		}
	}
};

void TannerGraph::test(){
	cout << "ttttt" << endl;
}

void TannerGraph::init(vector<double> recivedValue){
	//Lj = 
}
