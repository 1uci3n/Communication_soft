/*
* @Author: 1uci3n
* @Date:   2018-05-22 12:31:47
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-09-09 17:35:04
*/
#include "LDPCCode.h"

/**
 * [calcuBIAWGNChannelLLR description]
 * @param  sigmaSquare [description]
 * @param  input x = 1 v = 0;x = -1 v = 1
 * @return       [description]
 */
double calcuBIAWGNChannelLLR(double sigmaSquare, double input){
	return (2 * input) / sigmaSquare;
}

map<int, int> lTotalChanger(map<int, double> lTotal){
	map<int, int> result;
	int key;
	double value;
	map<int, double>::iterator itForlTotal;
	itForlTotal = lTotal.begin();
	while(itForlTotal != lTotal.end())
	{
		key = itForlTotal->first;
		value = itForlTotal -> second;
		if(value < 0){
			result[key] = 1;
		} else {
			result[key] = 0;
		}
		itForlTotal++;
	}
	return result;
}

vector<int> transMapToVector(map<int, int> map){
	vector<int> result;
	for (int i = 0; i < map.size(); ++i)
	{
		result.insert(result.end(), map[i]);
	}
	return result;
}

vector<vector<int> > setHammingCheckMatrix(){
	vector<int> j(7);
	vector<vector<int> > matrix;
	j[0] = 1, j[1] = 0, j[2] = 1, j[3] = 0, j[4] = 1, j[5] = 0, j[6] = 1;
	matrix.insert(matrix.end(), j);
	j[0] = 1, j[1] = 1, j[2] = 1, j[3] = 0, j[4] = 0, j[5] = 1, j[6] = 1;
	matrix.insert(matrix.end(), j);
	j[0] = 0, j[1] = 0, j[2] = 0, j[3] = 1, j[4] = 1, j[5] = 1, j[6] = 1;
	matrix.insert(matrix.end(), j);
	return matrix;
}

vector<int> cutBlockForHamming(vector<int> longBlock){
	vector<int> shortBlock(4);
	shortBlock[0] = longBlock[2];
	shortBlock[1] = longBlock[4];
	shortBlock[2] = longBlock[5];
	shortBlock[3] = longBlock[6];
	return shortBlock;
}